#include<instance.h>
om_instance* om_create_instance(){
	om_instance* instance = malloc(sizeof(om_instance));
	instance->window = om_create_window();
	instance->inventory = om_create_inventory();
	instance->player = om_create_player(instance->window);
	return instance;
}
void om_destroy_instance(om_instance* instance){
	om_destroy_inventory(instance->inventory);
	om_destroy_player(instance->player);
	om_destroy_window(instance->window);
}
