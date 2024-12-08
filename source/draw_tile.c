#include<tiles.h>
void draw_tile(om_window* window,unsigned char n_tile, int n_x, int n_y){
    if(n_tile==0)
        return;
    unsigned char tile = n_tile-1;
    for(int x=0;x<5;x++)
        for(int y=0;y<5;y++)
            if(tiles[(tile*5)+x+(y*35)])
                SDL_RenderDrawPoint(window->renderer,n_x+x,n_y+y);
}