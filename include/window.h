#ifndef __window__
#define __window__
#include<SDL2/SDL.h>
#include<palette.h>
struct{
    SDL_Window* window;
    SDL_Renderer* renderer;
} typedef om_window;
om_window* om_create_window();
void om_destroy_window(om_window* window);
void om_update_window(om_window* window);
void om_clear(om_window* window);
#endif