//
// Created by Kevin Zhang on 2022/1/16.
//



#include <string>
#include <iostream>
#include "Monster.h"

class Knuckle : public Monster{
public :


    Knuckle(int x, int y, int r) : Monster("Knuckle", x, y ,r){
        ALLEGRO_SAMPLE *sample = al_load_sample("./Knuckle/donot.ogg");
        attack_sound = al_create_sample_instance(sample);
     al_set_sample_instance_playmode(attack_sound, ALLEGRO_PLAYMODE_ONCE);
     al_attach_sample_instance_to_mixer(attack_sound, al_get_default_mixer());

        sample = al_load_sample("./Knuckle/theway.ogg");
        crazy_sound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(crazy_sound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(crazy_sound, al_get_default_mixer());

            HealthPoint = 40;
            speed = 30;
            worth = 3000;
            score = 3000;
    }


    ~Knuckle(){
        al_destroy_sample_instance(attack_sound);
    }




};


