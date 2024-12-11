#ifndef __inventory__
#define __inventory__
#include<mon.h>
#include<mon_list.h>
#include<window.h>
#include<map.h>
#include<player.h>
extern const char* item_names[3];
enum om_item_type{
    om_mon_case,
    om_mon_treat,
    om_flower,
    om_captured_mon
};
typedef enum om_mon_type om_item_type_f;
struct{
    unsigned char count;
    om_item_type_f type;
    unsigned char mon;
    unsigned char mon_level;
    unsigned int mon_health;
}typedef om_item;
struct{
    unsigned char mon;
    unsigned char level;
    unsigned int health;
    unsigned int active;
}typedef om_active_mon;
struct{
    om_item* backpack[30];
    om_active_mon* group[6];
}typedef om_inventory;
om_inventory* om_create_inventory();
void om_open_inventory(om_window* window, om_player* player, om_map* map, om_inventory* inv);
unsigned char om_append_inventory(om_item* item, om_inventory* inv);
void om_remove_inventory(unsigned char item, om_inventory* inv);
void om_swap_inventory(unsigned char item_a, unsigned char item_b, om_inventory* inv);
unsigned char om_empty_inventory(om_inventory* inv);
om_item* om_get_inventory(unsigned char item, om_inventory* inv);
void om_destroy_inventory(om_inventory* inv);
om_item* om_create_item();
void om_destroy_item(om_item* item);
om_active_mon* om_create_active_mon();
void om_destroy_active_mon(om_active_mon* mon);
#endif