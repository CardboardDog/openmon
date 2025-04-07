#ifndef __instance__
#define __instance__
#include<window.h>
#include<player.h>
#include<map.h>
#include<inventory.h>
struct{
	om_window* window;
	om_map* map;
	om_player* player;
	om_inventory* inventory;
} typedef om_instance;
om_instance* om_create_instance();
void om_destroy_instance(om_instance*);
#define omi_create_instance om_create_instance
#define omi_draw_map(instance) om_draw_map(instance->map, instance->window)
#define omi_draw_player(instance) om_draw_player(instance->player, instance->window)
#define omi_update_window(instance) om_update_window(instance->window)
#define omi_clear(instance) om_clear(instance->window)
#define omi_get_inputs(input) om_get_inputs(input)
#define omi_ask_dialog(instance, ...) om_ask_dialog(instance->window, instance->map, instance->player, __VA_ARGS__)
#define omi_move_player(instance, input) om_move_player(instance->player,instance->map,input[0],input[1])
#define omi_open_inventory(instance) om_open_inventory(instance->window,instance->inventory)
#define omi_vsync om_vsync
#define omi_load_map(instance,scene) instance->map = om_load_map(scene,instance->window)
#endif
