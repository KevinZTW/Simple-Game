#ifndef PEOPLE_H_INCLUDED
#define PEOPLE_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "algif5/src/algif.h"
#include <stdio.h>
#include <string.h>
#include "Monster.h"
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
  void Set_Run(int dir);
  void Set_Idle();
    void Set_Attack(std::vector<Monster*> &monsters);
  //execute the move
  void Move();
    void Attack(std::vector<Monster*> &monsters);
  // Update people position per frame
  // And detect if it reaches end point but not destroyed

 protected:
    int attack_dst = 30;
    int attack_pow = 1;
  int direction_count[4];
    int HealthPoint = 20;
    int speed = 2;
  char class_name[20];

 private:
  int direction;
  int attack_empower_duration = 5;
    int attack_empower_counter = 0;
  // end point
  int end_x, end_y;
  // animation counter
  int counter;
  // animation image of current direction
  int sprite_pos;
  int state = 1;
  // set of animation images
  std::vector<ALLEGRO_BITMAP*> moveImg;
  std::vector<ALGIF_ANIMATION*> imgs;

};

#endif  // PEOPLE_H_INCLUDED