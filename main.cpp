#include <exception>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include <thread>
#include <sstream>
#include <vector>
#include <random>
#include <ctime>

#include "Window.h"
#include "Water.h"
#include "Poisson.h"

using namespace std;


int main( int argc, char * argv[])
{
    Window win(500,500,"win");

    vector<Poisson*> poisson;
    srand(time(0));
    for(int i=0;i<1;i++)
        poisson.push_back(new Poisson(2,4,0.2,0.05));

    bool continuer(true);

    thread th([&continuer,&poisson,&win]()
    {
        stringstream sstream;
        Texture text("terre.bmp");
        while(continuer)
        {

            for(int x=0;x<win.getwidth();x++)
            {
                for(int y=0;y<win.getheight();y++)
                {
                    Coord c(double(x)/double(win.getwidth()),double(y)/double(win.getheight()));
                    Color color;
                    for(int i=0;i<poisson.size();i++)
                    {
                        color=poisson[i]->getPixel(c);
                        if(color.g<200)
                            break;
                    }
                    if(color.g>=200)
                        win.setPixel(x,y,text.getPixel(c));
                    else
                        win.setPixel(x,y,color);

                }
            }
            win.update();
            for(int i=0;i<poisson.size();i++)
            {
                poisson[i]->update();
            }
        }

    });

    win.startLoop();

    continuer=false;
    th.join();

    return 0;
}
