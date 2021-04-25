#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "Window.h"

class Texture
{
    public:
        Texture(std::string file);
        int getheigth(){return m_surf->h;}
        int getwidth(){return m_surf->w;};
        ~Texture();

        Color getPixel(Coord coord);

    private:
        int m_width;
        int m_height;
        SDL_Surface *m_surf;
};

#endif // TEXTURE_H
