#ifndef PEOPLE_H_INCLUDED
#define PEOPLE_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <string.h>

#include <vector>

#include "Circle.h"
#include "Object.h"
#include "global.h"

/*
Take Monster.h as referecne to create new object
*/
//enum { LEFT = 0, RIGHT, UP, DOWN_0.png };

class People : public Object {
 public:
  People();

  bool action = false;
  virtual ~People();

  // Draw image per frame
  // override virtual function "Object::Draw"
  void Draw();
  void Test();
  // Load bitmaps of animation image into container "moveImg"
  void Load_Move();

  //init the direction hero to move
  void Set_Move(int dir);
  void Set_Stop();
  //execute the move
  void Move();
  // Update people position per frame
  // And detect if it reaches end point but not destroyed

 protected:
  int direction_count[4];
    int HealthPoint = 20;
    int speed = 1;
    int worth = 10;
    int score = 100;
  char class_name[20];

 private:
  int direction;
  // end point
  int end_x, end_y;
  // animation counter
  int counter;
  // animation image of current direction
  int sprite_pos;

  // set of animation images
  std::vector<ALLEGRO_BITMAP*> moveImg;

};

#endif  // PEOPLE_H_INCLUDED