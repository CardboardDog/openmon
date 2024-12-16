#include<inventory.h>
char* item_names[3] = {
    "MON CASE",
    "MON TREAT",
    "FLOWER"
};
om_inventory* om_create_inventory(){
    om_inventory* inv = malloc(sizeof(om_inventory));
    for(int i=0;i<30;i++)
        inv->backpack[i]=NULL;
    for(int i=0;i<6;i++)
        inv->group[i]=om_create_active_mon();
    return inv;
}
void om_open_inventory(om_window* window, om_inventory* inv){
    int con = 1;
    om_text* labels[30];
    om_counter* counters[30];
    char selection = 0;
    char scroll = 0;
    for(int i=0;i<30;i++){
        if(inv->backpack[i]==NULL){
            labels[i] = NULL;
            counters[i] = NULL;
        }else{
            if(inv->backpack[i]->type==om_captured_mon){
                counters[i]=NULL;
                labels[i]=om_create_text(window,mon_list[inv->backpack[i]->mon].name);
            }else{
                counters[i]=om_create_counter(window,inv->backpack[i]->count);
                labels[i]=om_create_text(window,item_names[inv->backpack[i]->type]);
            }
        }
    }
    while(con){
        om_clear(window);
        int y=0;
        scroll = selection-3;
        if (scroll<0)
            scroll=0;
        scroll *= 5;
        for(int i=0;i<30;i++){
            if(labels[i]!=NULL){
                om_draw_text(window,labels[i],3,y-scroll);
            }
            if(counters[i]!=NULL){
                om_draw_counter(window,counters[i],70-counters[i]->width,y-scroll);
            }
            if(labels[i])
                y+=5;
        }
        if(selection>(y/5)-1)
            selection = 0;
        if(selection<0)
            selection = (y/5)-1;
        SDL_SetRenderDrawColor(window->renderer,om_pal_fg.r,om_pal_fg.g,om_pal_fg.b,255);
        SDL_RenderDrawLine(window->renderer,1,(selection*5)-scroll,1,(selection*5)+2-scroll);
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_KEYDOWN && event.key.repeat==0){
                switch(event.key.keysym.sym){
                    case SDLK_z:
                    case SDLK_x:
                        con = 0;
                        break;
                    case SDLK_DOWN:
                    case SDLK_LEFT:
                        selection++;
                        break;
                    case SDLK_RIGHT:
                    case SDLK_UP:
                        selection--;
                    default:
                        break;
                };
            }else if(event.type==SDL_QUIT){
                printf("warning: exited without memory cleanup\n");
                exit(0);
            }
        }
        om_update_window(window);
        om_vsync();
    }
    for(int i=0;i<30;i++){
        om_destroy_text(labels[i]); // this is safe because om_destroy_text will ignore NULL
        om_destroy_counter(counters[i]);
    }
}
unsigned char om_append_inventory(om_item* item, om_inventory* inv){
    unsigned char spot = 0;
    if(item->type!=om_captured_mon){ // captured mons cannot be stacked
        for(int s=0;s<30;s++){
            if((inv->backpack[s]!=NULL)&&(inv->backpack[s]->type==item->type)&&(inv->backpack[s]->count<99)){
                unsigned char missing = 99-inv->backpack[s]->count;
                if(missing>item->count)
                    missing = item->count;
                item->count-=missing;
                inv->backpack[s]->count+=missing;
                spot=s;
            }
            if(item->count==0){
                om_destroy_item(item);
                return spot;
            }
        }
    }
    if(item->count==0){
        om_destroy_item(item);
        return spot;
    }
    spot = om_empty_inventory(inv);
    if(spot==31){
        om_destroy_item(item);
        return 31;
    }
    inv->backpack[spot]=item;
    return spot;
}
void om_remove_inventory(unsigned char item, om_inventory* inv){
    om_destroy_item(inv->backpack[item]);
    inv->backpack[item] = NULL;
}
void om_swap_inventory(unsigned char item_a, unsigned char item_b, om_inventory* inv){
    om_item* point_a = inv->backpack[item_a],*point_b = inv->backpack[item_b];
    inv->backpack[item_a] = point_b;
    inv->backpack[item_b] = point_a;
}
unsigned char om_empty_inventory(om_inventory* inv){
    for(unsigned char s=0;s<30;s++)
        if(inv->backpack[s]==NULL)
            return s;
    return 31; // no slots are open
}
om_item* om_get_inventory(unsigned char item, om_inventory* inv){
    return inv->backpack[item];
}
void om_destroy_inventory(om_inventory* inv){
    for(int i=0;i<30;i++)
        om_destroy_item(inv->backpack[i]);
    for(int i=0;i<6;i++)
        om_destroy_active_mon(inv->group[i]);
}
om_item* om_create_item(){
    return malloc(sizeof(om_item));
}
void om_destroy_item(om_item* item){
    if(item!=NULL)
        free(item);
}
om_active_mon* om_create_active_mon(){
    om_active_mon* mon = malloc(sizeof(om_active_mon));
    mon->mon = 0;
    mon->level = 0;
    mon->active = 0;
    mon->health = 0;
    return mon;
}
void om_destroy_active_mon(om_active_mon* mon){
    if(mon!=NULL)
        free(mon);
}