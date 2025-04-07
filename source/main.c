#include<openmon.h>
int main(){
    om_initiate();
    //om_window* window = om_create_window();
    int running = 1;
    int inputs[3];
    om_instance* instance = om_create_instance();
    omi_load_map(instance,scene_test);
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
        omi_clear(instance);
        omi_draw_map(instance);
        omi_draw_player(instance);

        omi_update_window(instance);
        omi_get_inputs(inputs);
        if(inputs[2]==quit)
            running = 0;
        if(inputs[2]==1)
            if(omi_ask_dialog(instance,"YES NOPE",3,"HELLO.","DEMO TEXT.","DO YOU LIKE THIS\nDIALOG"))
                omi_ask_dialog(instance,NULL,1,"OH WELL.");
            else
                omi_ask_dialog(instance,NULL,1,"GREAT");
        else if(inputs[2]==-1)
            omi_open_inventory(instance);
        omi_move_player(instance,inputs);
        omi_vsync();
    }
    //om_destroy_inventory(inventory);
    om_destroy_map(instance->map);
    //om_destroy_player(player);
    //om_destroy_window(window);
    om_destroy_instance(instance);
    om_quit();
    return 0;
}
