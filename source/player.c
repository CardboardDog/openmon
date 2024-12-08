#include<player.h>
char frame = 0;
om_player* om_create_player(om_window* window){
    om_player* player = malloc(sizeof(om_player));
    for(int f=0;f<2;f++){
        player->frames[f] = SDL_CreateTexture(window->renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,5,5);
        SDL_SetRenderTarget(window->renderer,player->frames[f]);
        SDL_SetRenderDrawColor(window->renderer,om_pal_bg.r,om_pal_bg.g,om_pal_bg.b,255);
        SDL_RenderClear(window->renderer);
        SDL_SetRenderDrawColor(window->renderer,om_pal_fg.r,om_pal_fg.g,om_pal_fg.b,255);
        draw_tile(window,f+1,0,0);
    }
    SDL_SetRenderTarget(window->renderer,NULL);
    player->frame = 0;
    player->y=player->x=0;
    return player;
}
void om_draw_player(om_player* player, om_window* window){
    SDL_Rect pos;
    pos.x = player->x;
    pos.y = player->y;
    pos.w=pos.h=5;
    SDL_RenderCopy(window->renderer,player->frames[player->frame],NULL,&pos);
}
void om_destroy_player(om_player* player){
    if(player!=NULL){
        for(int f=0;f<2;f++)
            if(player->frames[f]!=NULL)
                SDL_DestroyTexture(player->frames[f]);
        free(player);
    }
}
void om_move_player(om_player* player, om_map* map, int x, int y){
    int check_a = om_check_map(map,player->x+x,player->y,(player->x/5)+x,(player->y)/5);
    int check_b = om_check_map(map,player->x+x,player->y,(player->x/5)+x,(player->y-5)/5);
    int check_c = om_check_map(map,player->x+x,player->y,(player->x/5)+x,(player->y+5)/5);
    if(
        !check_a|check_a==5&&
        !check_b|check_b==5&&
        !check_c|check_c==5)
        player->x+=x;
    check_a = om_check_map(map,player->x,player->y+y,player->x/5,(player->y/5)+y);
    check_b = om_check_map(map,player->x,player->y+y,(player->x-5)/5,(player->y/5)+y);
    check_c = om_check_map(map,player->x,player->y+y,(player->x+5)/5,(player->y/5)+y);
    if(
        !check_a|check_a==5&&
        !check_b|check_b==5&&
        !check_c|check_c==5)
        player->y+=y;
    if(x|y)
        player->frame=frame/3;
    else
        player->frame = 0;
    frame++;
    frame%=6;
}