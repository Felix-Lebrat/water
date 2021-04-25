#ifndef POISSON_H
#define POISSON_H

#include "Texture.h"
#include "Window.h"

class Poisson
{
    public:
        Poisson(double vitesse_coeff,double amplitude_coeff,double longueur,double epaisseur);
        Color getPixel(Coord pos);
        void update();
        ~Poisson();
    private:
        Texture m_texture;
        double m_1_sur_rayon;
        Coord m_direction;
        Coord m_tete;
        double m_longueur;
        double m_epaisseur;
        double m_vitesse_bat;
        double m_vitesse_av;
        double m_vitesse_coeff;
        double m_amplitude_coeff;
};

#endif // POISSON_H
