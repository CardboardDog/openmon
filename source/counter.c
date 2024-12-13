#include<counter.h>
void om_draw_digit(om_window* window, unsigned char c,int x, int y){
    SDL_SetRenderDrawColor(window->renderer,om_pal_fg.r,om_pal_fg.g,om_pal_fg.b,255);
    for(int x_p=0;x_p<3;x_p++)
        for(int y_p=0;y_p<4;y_p++)
            if(number_font[(c*3)+x_p+(y_p*33)])
                SDL_RenderDrawPoint(window->renderer,x+x_p,y+y_p);
}
om_counter* om_create_counter(om_window* window, unsigned int count){
    om_counter* text = malloc(sizeof(om_counter));
    text->texture = NULL;
    om_set_counter(window,text,count);
    return text;
}
void om_rebuild_counter(om_window* window, om_counter* counter){
    if(counter->texture!=NULL)
        SDL_DestroyTexture(counter->texture);
    unsigned int digit = counter->count;
    int length=0;
    while(digit){
        length+=1;
        digit/=10;
    }
    unsigned char* digits = malloc(length);
    digit = counter->count;
    int x=0;
    while(digit){
        digits[length-1-(x/4)] = (unsigned char)(digit%10);
        x+=4;
        digit/=10;
    }
    counter->width = length*4;
    counter->texture = SDL_CreateTexture(
        window->renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        counter->width,
        4
    );
    SDL_SetRenderTarget(window->renderer,counter->texture);
    SDL_SetRenderDrawBlendMode(window->renderer,SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(counter->texture,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(window->renderer,0,0,0,0);
    SDL_RenderClear(window->renderer);
    for(x=0;x<length;x++)
        om_draw_digit(window,digits[x],x*4,0);
    SDL_SetRenderTarget(window->renderer,NULL);
    free(digits);
}
void om_set_counter(om_window* window, om_counter* counter, unsigned int count){
    counter->count = count;
    om_rebuild_counter(window,counter);
}
void om_draw_counter(om_window* window, om_counter* counter, int x, int y){
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    pos.w = counter->width;
    pos.h = 4;
    SDL_RenderCopy(window->renderer,counter->texture,NULL,&pos);
}
void om_destroy_counter(om_counter* counter){
    if(counter!=NULL){
        if(counter->texture!=NULL)
            SDL_DestroyTexture(counter->texture);
        free(counter);
    }
}