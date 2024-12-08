#ifndef __tiles__
#define __tiles__
#include<window.h>
#define om_tiles_len 175
extern unsigned char tiles[om_tiles_len];
void draw_tile(om_window* window, unsigned char n_tile, int n_x, int n_y);
#define om_get_tile(x, y) (x+(y*14))
#endif