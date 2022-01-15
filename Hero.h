//#ifndef CLAW_H_INCLUDED
//#define CLAW_H_INCLUDED

#include "People.h"
#include <iostream>
class Hero : public People
{
public:
    Hero() : People()
    {
        direction_count[LEFT] = 4;
        direction_count[RIGHT] = 5;
        direction_count[UP] = 4;
        direction_count[DOWN] = 4;

        circle->x =  10;
        circle->y =  window_height - 50;
        circle->r = grid_width/2;

        HealthPoint = 20;
        speed = 1;
        score = 50;

        strncpy(class_name, "Hero2", 20);
        std::cout << "hero construct" << std::endl;
        Load_Move();
    }

};


//#endif // CLAW_H_INCLUDED
