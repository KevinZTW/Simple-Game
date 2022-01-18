//
// Created by Kevin Zhang on 2022/1/16.
//



#include <string>
#include <iostream>
#include "Monster.h"

class Knuckle : public Monster{
public :
    Knuckle(int x, int y, int r) : Monster("Knuckle", x, y ,r){
        ALLEGRO_SAMPLE *sample = al_load_sample("./DeathBringer/attack.ogg");
        attack_sound = al_create_sample_instance(sample);
     al_set_sample_instance_playmode(attack_sound, ALLEGRO_PLAYMODE_ONCE);
     al_attach_sample_instance_to_mixer(attack_sound, al_get_default_mixer());
    }


    ~Knuckle(){
        al_destroy_sample_instance(attack_sound);
    }



};


