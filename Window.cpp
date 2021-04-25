#include "Window.h"
#include <iostream>

using namespace std;

Color operator+(Color const& a,Color const& b)
{
    return Color(min(int(a.r+b.r),255),min(int(a.g+b.g),255),min(int(a.b+b.b),255));
}

Color operator*(double const& a,Color const& b)
{
    return Color(min(int(a*b.r),255),min(int(a*b.g),255),min(int(a*b.b),255));
}

Coord operator+(Coord const& a,Coord const& b)
{
    return Coord(a.x+b.x,a.y+b.y,a.z+b.z);
}

Coord operator*(double const& a,Coord const& b)
{
    return Coord(a*b.x,a*b.y,a*b.z);
}

Coord operator-(Coord const& a,Coord const& b)
{
    return a+(-1)*b;
}

double scal(Coord const& a,Coord const& b)
{
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

double norm(Coord const& a)
{
    return sqrt(scal(a,a));
}

Coord vect(Coord const& a,Coord const& b)
{
    return Coord(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
}

Window::Window(int width,int height,string title):m_width(width),m_height(height)
{
    assert(SDL_Init(SDL_INIT_VIDEO)>=0);

    m_win=SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,m_width,m_height,SDL_WINDOW_SHOWN);
    assert(m_win!=0);

    m_surf=SDL_GetWindowSurface(m_win);
}

void Window::startLoop()
{
    while(true)
    {
        if(SDL_PollEvent(&m_event))
        {
            if(m_event.window.event==SDL_WINDOWEVENT_CLOSE||(m_event.type==SDL_KEYDOWN&&m_event.key.keysym.scancode==SDL_SCANCODE_ESCAPE))
                break;
        }
    }
}

Uint32* Window::getPixel(int x,int y)
{
    return (Uint32*)(m_surf->pixels+x*m_surf->format->BytesPerPixel+y*m_surf->pitch);
}

void Window::setPixel(int x,int y,Color color)
{
    *getPixel(x,y)=SDL_MapRGB(m_surf->format,color.r,color.g,color.b);
}

void Window::update()
{
    SDL_UpdateWindowSurface(m_win);
}

void Window::save(string file)
{
    SDL_SaveBMP(m_surf,file.c_str());
}

void Window::clean(Color color)
{
    SDL_FillRect(m_surf,NULL,SDL_MapRGB(m_surf->format,color.r,color.g,color.b));
}

void Window::segment(Coord a,Coord b,Color color)
{
    Coord vect;
    Coord dir(b.x-a.x,b.y-a.y);
    Coord pos=a;
    double norm(sqrt(dir.x*dir.x+dir.y*dir.y));
    dir.x/=norm;
    dir.y/=norm;
    while(norm>0.9)
    {
        vect.x=b.x-pos.x;
        vect.y=b.y-pos.y;

        norm=vect.x*vect.x+vect.y*vect.y;

        pos.x+=dir.x;
        pos.y+=dir.y;

        if(pos.x>=0&&pos.x<m_width&&pos.y>=0&&pos.y<m_height)
            setPixel(pos.x,pos.y,color);
    }
}

Window::~Window()
{
    SDL_DestroyWindow(m_win);
    SDL_Quit();
}
