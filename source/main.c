#include<openmon.h>
int main(){
    om_initiate();
    om_window* window = om_create_window();
    int running = 1;
    int inputs[3];
    om_map* map = om_load_map(scene_test,window);
    om_player* player = om_create_player(window);
    om_inventory* inventory = om_create_inventory();

    {
        om_item* item = om_create_item();
        item->type = om_captured_mon;
        item->mon = 1;
        item->count = 1;
        om_append_inventory(item,inventory);
        item = om_create_item();
        item->type = om_mon_case;
        item->mon = 1;
        item->count = 23;
        om_append_inventory(item,inventory);
        item = om_create_item();
        item->type = om_mon_case;
        item->mon = 1;
        item->count = 84;
        om_append_inventory(item,inventory);
    }

    om_open_inventory(window,player,map,inventory);

    om_counter* count = om_create_counter(window,0);


    player->y=player->x=5;
    while(running){
        om_clear(window);
        om_draw_map(map,window);
        om_draw_player(player,window);

        om_set_counter(window,count,count->count+1);
        om_draw_counter(window,count,5,5);

        om_update_window(window);
        om_get_inputs(inputs);
        if(inputs[2]==quit)
            running = 0;
        if(inputs[2]==1)
            if(om_ask_dialog(window,map,player,"YES NOPE",3,"HELLO.","DEMO TEXT.","DO YOU LIKE THIS\nDIALOG"))
                om_ask_dialog(window,map,player,NULL,1,"OH WELL.");
            else
                om_ask_dialog(window,map,player,NULL,1,"GREAT");
        om_move_player(player,map,inputs[0],inputs[1]);
        om_vsync();
    }
    om_destroy_inventory(inventory);
    om_destroy_map(map);
    om_destroy_player(player);
    om_destroy_window(window);
    om_quit();
    return 0;
}