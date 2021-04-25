#include "Poisson.h"
#include <cmath>
#include <iostream>
#include <random>
#include <ctime>

#define alea_vitesse 1.2

using namespace std;

Poisson::Poisson(double vitesse_coeff,double amplitude_coeff,double longueur,double epaisseur)
:m_texture("poisson.bmp"),m_1_sur_rayon(-3),m_longueur(longueur),m_epaisseur(epaisseur),
m_vitesse_bat(0.5),m_vitesse_av(0.001),m_vitesse_coeff(vitesse_coeff),m_amplitude_coeff(amplitude_coeff)
{
    m_direction=Coord(rand(),rand());
    m_direction=(2./norm(m_direction))*m_direction-Coord(1,1);
    m_direction=(1./norm(m_direction))*m_direction;
    m_tete=Coord(rand()%1000,rand()%1000);
    m_tete=(1./1000.)*m_tete;
}

Color Poisson::getPixel(Coord pos)
{
    pos.z=0;
    double rayon=(1./m_1_sur_rayon);
    Coord centre=m_tete+rayon*Coord(-m_direction.y,m_direction.x);
    Coord ct=rayon/(abs(rayon))*Coord(m_direction.y,-m_direction.x);
    Coord cp=pos-centre;
    double dist=norm(cp);
    cp=(1./dist)*cp;

    rayon=abs(rayon);

    if(dist>rayon+m_epaisseur/2.||dist<rayon-m_epaisseur/2.)
        return Color(0,255,0);

    double alpha=acos(scal(ct,cp));
    if(alpha<0||m_1_sur_rayon*vect(cp,ct).z<0||alpha>=m_longueur/rayon)
    {
        return Color(0,255,0);
    }

    return m_texture.getPixel(Coord(1-alpha*rayon/m_longueur,(m_1_sur_rayon>0)?((dist-rayon+m_epaisseur/2.)/m_epaisseur):(1-(dist-rayon+m_epaisseur/2.)/m_epaisseur)));

}

void Poisson::update()
{
    double amplitude(m_amplitude_coeff/(5*m_longueur));
    if(abs(m_vitesse_bat)<0.5*m_amplitude_coeff/3.)
        m_vitesse_bat=abs(m_vitesse_bat)/m_vitesse_bat*m_amplitude_coeff*0.5/3.;
    if(abs(m_vitesse_bat)>amplitude)
        m_vitesse_bat=abs(m_vitesse_bat)/m_vitesse_bat*3;

    if(m_1_sur_rayon>amplitude||(m_1_sur_rayon<-amplitude))
        m_vitesse_bat=-m_1_sur_rayon/abs(m_1_sur_rayon)*abs(m_vitesse_bat);
    m_1_sur_rayon+=m_vitesse_bat;
    if(abs(m_1_sur_rayon)<0.01)
        m_1_sur_rayon+=m_vitesse_bat;

    switch(rand()%2)
    {
    case 0:
        m_vitesse_bat*=alea_vitesse;
        break;
    case 1:
        m_vitesse_bat/=double(alea_vitesse);
        break;
    default:
        break;
    }

    m_direction=m_direction+5*m_longueur*0.5*(0.1*m_vitesse_bat+pow(m_vitesse_av+1,0.1)*0.015*m_1_sur_rayon)*Coord(-m_direction.y,m_direction.x);
    m_direction=(1./norm(m_direction))*m_direction;

    m_vitesse_av+=m_vitesse_coeff*m_longueur*0.05*(5*m_longueur*0.002*abs(m_vitesse_bat)-0.5*m_vitesse_av);

    m_tete=m_tete+m_vitesse_av*m_direction;

    if(m_tete.x<=0||m_tete.x>=1)
        m_direction.x*=-1;
        m_tete=m_tete+m_vitesse_av*m_direction;
    if(m_tete.y<=0||m_tete.y>=1)
        m_direction.y*=-1;
        m_tete=m_tete+m_vitesse_av*m_direction;
}

Poisson::~Poisson()
{
}
