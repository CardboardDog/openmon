#include<dialog.h>
unsigned char om_ask_dialog(om_window* window, om_map* map, om_player* player, char* options, int count, ...){
    // todo: cleanup
    va_list list;
    va_start(list,count);
    om_text* text = om_create_text(window,"");
    int cont;
    SDL_Rect text_back;
    text_back.x = 1;
    text_back.y = 28;
    text_back.h = 11;
    text_back.w = 68;
    unsigned char selected;
    char* option_a,*option_b,*str_unsplit;
    om_text* text_a,*text_b;
    if(options!=NULL){
        str_unsplit = malloc(strlen(options));
        strcpy(str_unsplit,options);
        option_a = strtok(str_unsplit," ");
        option_b = strtok(NULL," ");
        text_a = om_create_text(window,option_a);
        text_b = om_create_text(window,option_b);
    }
    for(int i=0;i<count;i++){
        om_set_text(window,text,va_arg(list,char*));
        cont = 1;
        selected = 0;
        while(cont){
            om_clear(window);
            om_draw_map(map,window);
            om_draw_player(player,window);
            SDL_SetRenderDrawColor(window->renderer, om_pal_bg.r, om_pal_bg.g, om_pal_bg.b, 255);
            SDL_RenderFillRect(window->renderer,&text_back);
            SDL_SetRenderDrawColor(window->renderer, om_pal_fg.r, om_pal_fg.g, om_pal_fg.b, 255);
            SDL_RenderDrawRect(window->renderer,&text_back);
            if(options!=NULL && i+1==count){
                SDL_Rect select_back;
                select_back.x = 0;
                select_back.y = (!selected)?21:23;
                select_back.h = (!selected)?7:5;
                select_back.w = text_a->width+1;
                SDL_SetRenderDrawColor(window->renderer, om_pal_bg.r, om_pal_bg.g, om_pal_bg.b, 255);
                SDL_RenderFillRect(window->renderer,&select_back);
                select_back.x = 69-text_b->width;
                select_back.y = (selected)?21:23;
                select_back.h = (selected)?7:5;
                select_back.w = text_b->width+1;
                SDL_RenderFillRect(window->renderer,&select_back);
                SDL_SetRenderDrawColor(window->renderer, om_pal_fg.r, om_pal_fg.g, om_pal_fg.b, 255);
                om_draw_text(window,text_a,1,24);
                om_draw_text(window,text_b,70-text_b->width,24);
                SDL_Rect selector;
                selector.x = (!selected)?1:70-text_b->width;
                selector.y = 22;
                selector.w = (!selected)?text_a->width-1:text_b->width-1;
                selector.h = 1;
                // replace with SDL_RenderDrawLine later
                SDL_RenderDrawRect(window->renderer,&selector);
            }
            om_draw_text(window,text,3,30);
            om_update_window(window);
            om_vsync();
            SDL_Event event;
            while(SDL_PollEvent(&event)){
                if(event.type == SDL_KEYDOWN && event.key.repeat==0){
                    switch(event.key.keysym.sym){
                        case SDLK_z:
                            cont = 0;
                            break;
                        case SDLK_LEFT:
                        case SDLK_RIGHT:
                        case SDLK_UP:
                        case SDLK_DOWN:
                            selected=!selected;
                        default:
                            break;
                    };
                }else if(event.type==SDL_QUIT){
                    printf("warning: exited without memory cleanup\n");
                    exit(0);
                }
            }
        }
    }
    if(options!=NULL){
        free(str_unsplit);
        om_destroy_text(text_a);
        om_destroy_text(text_b);
    }
    om_destroy_text(text);
    return selected;
}