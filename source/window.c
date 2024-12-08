#include<window.h>
om_window* om_create_window(){
    om_window* window = malloc(sizeof(om_window));
    window->window = SDL_CreateWindow("Open Mon",0,0,70*5,40*5,SDL_WINDOW_RESIZABLE);
    window->renderer = SDL_CreateRenderer(window->window,-1,SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(window->renderer,70,40);
    return window;
}
void om_destroy_window(om_window* window){
    if(window!=NULL){
        SDL_DestroyWindow(window->window);
        SDL_DestroyRenderer(window->renderer);
        free(window);
    }
}
void om_clear(om_window* window){
    SDL_SetRenderDrawColor(window->renderer,om_pal_bg.r,om_pal_bg.g,om_pal_bg.b,255);
    SDL_RenderClear(window->renderer);
}
void om_update_window(om_window* window){
    SDL_RenderPresent(window->renderer);
}