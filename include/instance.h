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
#endif
