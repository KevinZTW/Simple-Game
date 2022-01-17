//
// Created by Kevin Zhang on 2022/1/17.
//

#ifndef TOWERGAME_NEW_ITEM_H
#define TOWERGAME_NEW_ITEM_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <string>
#include "Object.h"

enum{HealthPack=0, PowerEnhance, SpecialA};

class Item:public Object{
public:
    Item(int id, int x, int y);
    ~Item();
    void Draw();
    int type;
    std::vector<ALLEGRO_BITMAP *>imgs;
private:

    int item_categories = 3;
};


#endif //TOWERGAME_NEW_ITEM_H
