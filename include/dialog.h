#ifndef __dialog__
#define __dialog__
#include<stdarg.h>
#include<window.h>
#include<player.h>
#include<map.h>
#include<text.h>
#include<vsync.h>
unsigned char om_ask_dialog(om_window* window, om_map* map, om_player* player, char* options, int count, ...);
#endif