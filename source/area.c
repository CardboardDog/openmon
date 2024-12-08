#include<area.h>
unsigned char om_areas_overlap(om_area* area_a, om_area* area_b){
    return (
        area_a->x < area_b->x+area_b->w &&
        area_a->x+area_a->w > area_b->x &&
        area_a->y < area_b->y+area_b->h &&
        area_a->y+area_a->h > area_b->y
    );
}