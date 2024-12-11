#include<inventory.h>
const char* item_names[3] = {
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
void om_open_inventory(om_window* window, om_player* player, om_map* map, om_inventory* inv){
    for(unsigned char i=0;i<30;i++){
        if(inv->backpack[i]!=NULL){
            if(inv->backpack[i]->type==om_captured_mon)
                printf("%s\n",mon_list[inv->backpack[i]->mon].name);
            else
                printf("%s,%i\n",item_names[inv->backpack[i]->type],inv->backpack[i]->count);
        }
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