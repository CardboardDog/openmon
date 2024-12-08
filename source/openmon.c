#include<openmon.h>
void om_initiate(){
    SDL_Init(SDL_INIT_EVERYTHING);
    om_setup_inputs();
    om_setup_vsync();
}
void om_quit(){
    SDL_Quit();
}