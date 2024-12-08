#include<map.h>
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
int om_check_map(om_map* map, int x, int y, int tile_x, int tile_y){
    om_area block;
    om_area check;
    block.x = tile_x*5;
    block.y = tile_y*5;
    check.x = x;
    check.y = y;
    block.w=block.h=check.w=check.h=5;
    if(om_areas_overlap(&block,&check)){
        return (signed int)map->map[om_get_tile(tile_x,tile_y)];
    }
    return 0;
}