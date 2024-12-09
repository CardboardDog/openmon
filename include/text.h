#ifndef __text__
#define __text__
#include<window.h>
#include<font.h>
struct{
    unsigned char* string;
    SDL_Texture* texture;
    size_t length;
    int width;
    int height;
} typedef om_text;
void om_draw_char(om_window* window, unsigned char c,int x, int y);
om_text* om_create_text(om_window* window, char* string);
void om_rebuild_text(om_window* window, om_text* text);
void om_set_text(om_window* window, om_text* text, char* string);
void om_draw_text(om_window* window, om_text* text, int x, int y);
void om_destroy_text(om_text* text);
#endif