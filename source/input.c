#include<input.h>
const unsigned char* keys;
const int quit = 0xDEAD;
void om_setup_inputs(){
    keys = SDL_GetKeyboardState(NULL);
}
void om_get_inputs(int* inputs){
    SDL_Event event;
    int zx = 0;
    while(SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT){
            inputs[2] = quit;
            return;
        }else if(event.type==SDL_KEYDOWN&&event.key.repeat==0)
            zx += (event.key.keysym.sym==SDLK_z)-(event.key.keysym.sym==SDLK_x);
    }
    inputs[0]=keys[SDL_SCANCODE_RIGHT]-keys[SDL_SCANCODE_LEFT];
    inputs[1]=keys[SDL_SCANCODE_DOWN]-keys[SDL_SCANCODE_UP];
    if(inputs[2]!=quit);
        inputs[2]=zx;
}