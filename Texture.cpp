#include "Texture.h"
#include <cassert>

using namespace std;

Texture::Texture(string file)
{
    m_surf=SDL_LoadBMP(file.c_str());
}

Color Texture::getPixel(Coord coord)
{
    int x=coord.x*m_surf->w;
    int y=(1-coord.y)*m_surf->h;
    if(x>=m_surf->w)
        x=m_surf->w-1;
    if(x<0)
        x=0;
    if(y>=m_surf->h)
        y=m_surf->h-1;
    if(y<0)
        y=0;
    Uint8 r,g,b;


    SDL_GetRGB(*((Uint32*)(m_surf->pixels+x*m_surf->format->BytesPerPixel+y*m_surf->pitch)),m_surf->format,&r,&g,&b);

    return Color(r,g,b);
}

Texture::~Texture()
{
    SDL_FreeSurface(m_surf);
}
