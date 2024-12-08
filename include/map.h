#ifndef __map__
#define __map__
#include<SDL2/SDL.h>
#include<tiles.h>
#include<window.h>
#include<area.h>
#include<palette.h>
struct{
    unsigned char* map;
    SDL_Texture* texture;
} typedef om_map;
om_map* om_load_map(unsigned char* map, om_window* window);
void om_rebuild_map(om_map* map, om_window* window);
void om_draw_map(om_map* map, om_window* window);
void om_change_map(om_map* map, unsigned char* data, om_window* window);
void om_destroy_map(om_map* map);
int om_check_map(om_map* map, int x, int y, int tile_x, int tile_y);
#endif