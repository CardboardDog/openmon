#include<map.h>
void draw_tile(om_window* window,unsigned char n_tile, int n_x, int n_y){
    if(n_tile==0)
        return;
    unsigned char tile = n_tile-1;
    for(int x=0;x<5;x++)
        for(int y=0;y<5;y++)
            if(tiles[(tile*5)+x+(y*35)])
                SDL_RenderDrawPoint(window->renderer,n_x+x,n_y+y);
}
om_map* om_load_map(unsigned char* map, om_window* window){
    om_map* map_out = malloc(sizeof(om_map));
    map_out->map = map;
    om_rebuild_map(map_out,window);
    return map_out;
}
void om_rebuild_map(om_map* map, om_window* window){
    if(map->texture!=NULL)
        SDL_DestroyTexture(map->texture);
    map->texture = SDL_CreateTexture(window->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,70,40);
    SDL_SetRenderTarget(window->renderer,map->texture);
    SDL_SetRenderDrawColor(window->renderer,om_pal_bg.r,om_pal_bg.g,om_pal_bg.b,255);
    SDL_RenderClear(window->renderer);
    SDL_SetRenderDrawColor(window->renderer,om_pal_fg.r,om_pal_fg.g,om_pal_fg.b,255);
    for(int x=0;x<14;x++)
        for(int y=0;y<8;y++)
            draw_tile(window,map->map[x+(y*14)],x*5,y*5);
    SDL_SetRenderTarget(window->renderer,NULL);
}
void om_draw_map(om_map* map, om_window* window){
    SDL_RenderCopy(window->renderer,map->texture,NULL,NULL);
}
void om_change_map(om_map* map, unsigned char* data, om_window* window){
    map->map = data;
    om_rebuild_map(map,window);
}
void om_destroy_map(om_map* map){
    if(map->texture!=NULL)
        SDL_DestroyTexture(map->texture);
    free(map);
}