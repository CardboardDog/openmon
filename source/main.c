#include<openmon.h>
int main(){
    om_initiate();
    //om_window* window = om_create_window();
    int running = 1;
    int inputs[3];
    om_instance* instance = om_create_instance();
    instance->map = om_load_map(scene_test,instance->window);
    //om_player* player = om_create_player(window);
    //om_inventory* inventory = om_create_inventory();

    /*{
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
        item = om_create_item();
        item->type = om_mon_treat;
        item->mon = 1;
        item->count = 1;
        om_append_inventory(item,inventory);
        item = om_create_item();
        item->type = om_flower;
        item->mon = 1;
        item->count = 31;
        om_append_inventory(item,inventory);
        item = om_create_item();
        item->type = om_captured_mon;
        item->mon = 0;
        item->count = 1;
        om_append_inventory(item,inventory);
    }*/

    instance->player->y=instance->player->x=5;
    while(running){
        om_clear(instance->window);
        om_draw_map(instance->map,instance->window);
        om_draw_player(instance->player,instance->window);

        om_update_window(instance->window);
        om_get_inputs(inputs);
        if(inputs[2]==quit)
            running = 0;
        if(inputs[2]==1)
            if(om_ask_dialog(instance->window,instance->map,instance->player,"YES NOPE",3,"HELLO.","DEMO TEXT.","DO YOU LIKE THIS\nDIALOG"))
                om_ask_dialog(instance->window,instance->map,instance->player,NULL,1,"OH WELL.");
            else
                om_ask_dialog(instance->window,instance->map,instance->player,NULL,1,"GREAT");
        else if(inputs[2]==-1)
            om_open_inventory(instance->window,instance->inventory);
        om_move_player(instance->player,instance->map,inputs[0],inputs[1]);
        om_vsync();
    }
    //om_destroy_inventory(inventory);
    om_destroy_map(instance->map);
    //om_destroy_player(player);
    //om_destroy_window(window);
    om_destroy_instance(instance);
    om_quit();
    return 0;
}
