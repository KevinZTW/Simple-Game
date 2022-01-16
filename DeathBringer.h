//
// Created by Kevin Zhang on 2022/1/16.
//

#ifndef TOWERGAME_NEW_DEATHWALKER_H
#define TOWERGAME_NEW_DEATHWALKER_H

#include <string>
#include "Monster.h"

class DeathBringer : public Monster{
public :
    DeathBringer(int x, int y, int r) : Monster("DeathBringer", x, y ,r){


    }

};


#endif //TOWERGAME_NEW_DEATHWALKER_H
