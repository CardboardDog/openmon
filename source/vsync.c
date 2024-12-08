#include<vsync.h>
unsigned int last;
void om_setup_vsync(){
    last = SDL_GetTicks();
}
void om_vsync(){
    unsigned int now = SDL_GetTicks();
    if(now-last<16)
        SDL_Delay(16-(now-last));
    last = SDL_GetTicks();
}