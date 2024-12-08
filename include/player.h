#ifndef __player__
#define __player__
#include<window.h>
#include<tiles.h>
#include<scenes.h>
#include<map.h>
struct{
    int y;
    int x;
    unsigned char frame;
    SDL_Texture* frames[2];
} typedef om_player;
om_player* om_create_player(om_window* window);
void om_draw_player(om_player* player, om_window* window);
void om_destroy_player(om_player* player);
void om_move_player(om_player* player, om_map* map, int x, int y);
#endif