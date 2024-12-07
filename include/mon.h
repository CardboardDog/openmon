#ifndef __mon__
#define __mon__
enum om_mon_type{
    om_fire,
    om_water,
    om_earth,
    om_metal,
    om_poison,
};
typedef enum om_mon_type om_mon_type_f;
struct{
    char pixels[256];
    om_mon_type_f type;
    char* name;
    unsigned int health;
    unsigned char id;
    unsigned char attack_damage[3];
    char* attack_names[3];
    unsigned char attack_energy[3];
} typedef mon;
#endif