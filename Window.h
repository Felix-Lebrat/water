#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include <cassert>
#include <random>
#include <ctime>
#include <thread>

struct Color
{
    Color(){};
    Color(unsigned char r,unsigned char g,unsigned char b):r(r),g(g),b(b){};
    void add(int n);
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

Color operator+(Color const& a,Color const& b);

Color operator*(double const& a,Color const& b);

struct Coord
{
        Coord(){};
        Coord(double x,double y,double z=0):x(x),y(y),z(z){};
        static Coord calc(Coord a,Coord b);

        double x;
        double y;
        double z;
};

Coord operator+(Coord const& a,Coord const& b);
Coord operator*(double const& a,Coord const& b);
Coord operator-(Coord const& a,Coord const& b);
double scal(Coord const& a,Coord const& b);
double norm(Coord const& a);
Coord vect(Coord const& a,Coord const& b);

class Window
{
    public:
        Window(int width,int height,std::string title);
        ~Window();

        void startLoop();
        Uint32* getPixel(int x,int y);
        void setPixel(int x,int y,Color color);
        void update();
		void save(std::string file);
        void clean(Color color);
        void segment(Coord a,Coord b,Color color);

        int getwidth() { return m_width; }
        int getheight() { return m_height; }

    private:
        int m_width;
        int m_height;
        SDL_Window *m_win;
        SDL_Surface *m_surf;
        SDL_Event m_event;
};

#endif // WINDOW_H
