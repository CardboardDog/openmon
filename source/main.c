#include<openmon.h>
int main(){
    om_initiate();
    om_window* window = om_create_window();
    int running = 1;
    int inputs[3];
    while(running){
        om_clear(window);
        om_update_window(window);

        om_get_inputs(inputs);
        if(inputs[2]==quit)
            running = 0;
    }
    om_destroy_window(window);
    om_quit();
    return 0;
}