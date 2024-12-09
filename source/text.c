#include<text.h>
void om_draw_char(om_window* window, unsigned char c,int x, int y){
    if(c==' ')
        return;
    unsigned char tile = ((c=='.')?91:c)-65;
    SDL_SetRenderDrawColor(window->renderer,om_pal_fg.r,om_pal_fg.g,om_pal_fg.b,255);
    for(int x_p=0;x_p<3;x_p++)
        for(int y_p=0;y_p<3;y_p++)
            if(tiny_font[(tile*3)+x_p+(y_p*81)])
                SDL_RenderDrawPoint(window->renderer,x+x_p,y+y_p);
}
om_text* om_create_text(om_window* window, char* string){
    om_text* text = malloc(sizeof(om_text));
    om_set_text(window,text,string);
    return text;
}
void om_rebuild_text(om_window* window, om_text* text){
    int lines = 1;
    int width = 0;
    int most_width = 0;
    for(int i=0;i<text->length;i++){
        if(most_width<width)
            most_width=width;
        if(text->string[i]=='\n'){
            lines++;
            width = 0;
        }else
            width++;
    }
    if(most_width<width)
            most_width=width;
    if(text->texture!=NULL)
        SDL_DestroyTexture(text->texture);
    text->width = most_width*4;
    text->height = 4*lines;
    text->texture = SDL_CreateTexture(
        window->renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        text->width,
        text->height
    );
    SDL_SetRenderTarget(window->renderer,text->texture);
    SDL_SetRenderDrawBlendMode(window->renderer,SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(text->texture,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(window->renderer,0,0,0,0);
    SDL_RenderClear(window->renderer);
    int x=0,y=0;
    for(int i=0;i<text->length;i++){
        if(text->string[i]=='\n'){
            x=0;
            y+=4;
        }else{
            om_draw_char(window,text->string[i],x,y);
            x+=4;
        }
    }
    SDL_SetRenderTarget(window->renderer,NULL);
}
void om_set_text(om_window* window, om_text* text, char* string){
    text->string = string;
    text->length = strlen(string);
    om_rebuild_text(window,text);
}
void om_draw_text(om_window* window, om_text* text, int x, int y){
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    pos.w = text->width;
    pos.h = text->height;
    SDL_RenderCopy(window->renderer,text->texture,NULL,&pos);
}
void om_destroy_text(om_text* text){
    if(text->texture!=NULL){
        if(text->texture!=NULL)
            SDL_DestroyTexture(text->texture);
        free(text);
    }
}