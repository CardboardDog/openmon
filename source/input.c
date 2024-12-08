#include<input.h>
const unsigned char* keys;
const int quit = 0xDEAD;
void om_setup_inputs(){
    keys = SDL_GetKeyboardState(NULL);
}
void om_get_inputs(int* inputs){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type==SDL_QUIT){
            inputs[2] = quit;
            return;
        }
    }
    inputs[0]=keys[SDL_SCANCODE_RIGHT]-keys[SDL_SCANCODE_LEFT];
    inputs[1]=keys[SDL_SCANCODE_DOWN]-keys[SDL_SCANCODE_UP];
    if(inputs[2]!=quit);
        inputs[2]=keys[SDL_SCANCODE_Z]-keys[SDL_SCANCODE_X];
}