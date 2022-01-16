#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <string>
#include "algif5/src/algif.h"
#include <vector>

#include "Circle.h"
#include "Object.h"
#include "global.h"


class Monster : public Object {
public:
    Monster(std::string name, int x, int y, int r);
  virtual ~Monster();

  // Draw image per frame
  // override virtual function "Object::Draw"
  void Draw();

  void UpdateState(int hero_x, int hero_y);

    // Update monster position per frame
    void Move();

  // Load bitmaps of animation image into container "moveImg"
  void Load_Move();



  // functions that return information of monster
  int getDir() { return direction; }
  int getWorth() { return worth; }
  int getScore() { return score; }

  bool Subtract_HP(int);

 protected:
  int direction_count[4];
  int HealthPoint = 20;
  int speed = 1;
  int worth = 10;
  int score = 100;
  std::string class_name;
//  char class_name[20];

 private:
  // direction and index for "path"
  unsigned int step;
  int direction;
  int chase_dst = 200;
  // end point
  int end_x, end_y;
  // animation counter
  int counter;
  // animation image of current direction
  int sprite_pos;

  // set of animation images
  std::vector<ALLEGRO_BITMAP*> moveImg;
  // monster state, LeftIdle....
  int state = 1;
  std::vector<ALGIF_ANIMATION*> imgs;
  // path on map
  std::vector<int> path;
};

#endif  // MONSTER_H_INCLUDED
