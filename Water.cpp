#include "Water.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <random>
#include <ctime>

using namespace std;

Water::Water(Window* win,Coord light)
:m_win(win),m_light(light),m_temps(0),m_ciel("ciel.bmp"),m_terre("terre.bmp")
{
    Coord c(m_win->getwidth()/2,m_win->getheight()/2);
    m_light=c+10*(m_light+(-1)*c);
    srand(time(0));
    for(int i=0;i<10;i++)
        m_poissons.push_back(new Poisson(0.5,4,0.15,0.035));
}

double height(Coord pos,int tps)
{
    double t=0.5*double(tps);
    return -1+0.1*sin(1.5*(t-norm(Coord(-250,250)-pos)/10.))+0.25*sin(0.6*(t-norm(pos)/10.))+0.7*sin(0.75*(t-norm(Coord(500,0)-pos)/10.));
}

void Water::update()
{
    double heights[m_win->getwidth()+1][m_win->getheight()+1];


    double max_height(height(Coord(0,0),m_temps));
    for(int x=0;x<m_win->getwidth()+1;x++)
    {
        for(int y=0;y<m_win->getheight()+1;y++)
        {
            heights[x][y]=height(Coord(x,y),m_temps);
            if(heights[x][y]>max_height)
                max_height=heights[x][y];
        }
    }




    bool eclaire;
    double ecart;
    double pas;
    double coeff;
    double n1(1),n2(1.5);
    double cos_theta1,sin_theta1,cos_theta2,sin_theta2;
    double profondeur(1);
    double coeff_reflection(0.7);
    Coord e_x,e_y;
    Coord reflect,refract;
    Coord c;
    Coord normal;
    Color fond;
    m_win->clean(Color(0,0,0));

    for(int x=0;x<m_win->getwidth();x++)
    {
        for(int y=0;y<m_win->getheight();y++)
        {
            e_x=Coord(1,0,heights[x+1][y]-heights[x][y]);
            e_x=(1./norm(e_x))*e_x;

            e_y=Coord(0,1,heights[x][y+1]-heights[x][y]);
            e_y=(1./norm(e_y))*e_y;

            reflect=Coord(2*double(x)/double(m_win->getwidth())-1,2*double(y)/double(m_win->getheight())-1,heights[x][y]);
            reflect=reflect-2*scal(reflect,e_x)*e_x;
            reflect=reflect-2*scal(reflect,e_y)*e_y;

            reflect=(1./norm(reflect))*reflect;
            Color color=m_ciel.getPixel(Coord((reflect.x+1.)/2.,(reflect.y+1.)/2.));

            reflect.z=abs(reflect.z);
            c=m_light-Coord(x,y,heights[x][y]);
            c=(1./norm(c))*c;
            coeff=abs(scal(reflect,c));

            normal=vect(e_x,e_y);
            refract=Coord(0,0,-1);

            sin_theta1=norm(vect(refract,normal));

            if(sin_theta1>0.01)
            {
                cos_theta1=abs(scal(refract,normal));

                Coord y=(1/sin_theta1)*(refract+(cos_theta1*normal));
                Coord x=-1*normal;



                sin_theta2=n1*sin_theta1/n2;
                cos_theta2=sqrt(1-pow(sin_theta2,2));

                refract=(cos_theta2*x)+(sin_theta2*y);
            }

            assert(refract.z!=0);
            refract=(1./refract.z)*refract;
            refract.z=profondeur;
            refract=(0.5/norm(refract))*refract+0.5*Coord(2*double(x)/double(m_win->getwidth())-1,2*double(y)/double(m_win->getheight())-1);
            refract=0.5*(refract+Coord(1,1));

            for(int i=0;i<m_poissons.size();i++)
            {
                fond=m_poissons[i]->getPixel(refract);
                if(fond.g<150)
                    break;
            }

            if(fond.g>=150)
            {
                fond=m_terre.getPixel(refract);
            }

            color=coeff_reflection*color+0.5*pow(coeff,7)*Color(255,255,255)+(1-coeff_reflection)*(fond+0.2*Color(0,115,76));


            m_win->setPixel(x,y,color);


        }
    }
    for(int i=0;i<m_poissons.size();i++)
        m_poissons[i]->update();
    m_win->update();

    m_temps++;
}

Water::~Water()
{
}
