#ifndef __counter__
#define __counter__
#include<window.h>
#include<font.h>
struct{
    SDL_Texture* texture;
    unsigned int count;
    int width;
} typedef om_counter;
void om_draw_digit(om_window* window, unsigned char c,int x, int y);
om_counter* om_create_counter(om_window* window, unsigned int count);
void om_rebuild_counter(om_window* window, om_counter* counter);
void om_set_counter(om_window* window, om_counter* counter, unsigned int count);
void om_draw_counter(om_window* window, om_counter* counter, int x, int y);
void om_destroy_counter(om_counter* counter);
#endif