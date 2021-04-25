#ifndef WATER_H
#define WATER_H

#include "Window.h"
#include "Texture.h"
#include "Poisson.h"

#include <cmath>
#include <vector>


class Water
{
    public:
        Water(Window* win,Coord light);
        void update();
        virtual ~Water();
    private:
        Window* m_win;
        int m_temps;
        Coord m_light;
        Texture m_ciel;
        Texture m_terre;
        std::vector<Poisson*> m_poissons;
};

#endif // WATER_H
