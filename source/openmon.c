#include<openmon.h>
void om_initiate(){
    SDL_Init(SDL_INIT_EVERYTHING);
    om_setup_inputs();
}
void om_quit(){
    SDL_Quit();
}