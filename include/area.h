#ifndef __area__
#define __area__
struct{
    int x;
    int y;
    int w;
    int h;
}typedef om_area;
unsigned char om_areas_overlap(om_area* area_a, om_area* area_b);
#endif