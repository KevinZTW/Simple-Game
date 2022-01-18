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
  void Hurt(int power);
  void reset_position(int type){
      if (type ==0){
          circle->x =  10;

      }else {
          circle->x =  window_width - 10;
      }

  }
  int getHealth(){return HealthPoint;}
  int AddHealth(int power){HealthPoint+= power;}
  void AddPower(){attack_pow+=1;}
  void AddExp(){exp += leveup_exp_req;}
  void Level_Up();
    //sound
    ALLEGRO_SAMPLE_INSTANCE *swing_sound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *hurt_sound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *level_sound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *collect_sound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *walk_sound = NULL;

    int level = 1;
    int score = 0;
    int exp = 0;
    int leveup_exp_req = 10;
 protected:
    int attack_dst = 40;
    int attack_pow = 1;
  int direction_count[4];
    int HealthPoint = 40;
    int hurt_cool_down_duration = 5;
    int hurt_cool_down_counter = hurt_cool_down_duration-2;
    int hurt_hit_back_dst = 80;
    int speed = 4;
  char class_name[20];

 private:
  int direction;
  int attack_empower_duration = 3;
  int attack_empower_counter = 0;

  int state = 1;
  // set of animation images
  std::vector<ALLEGRO_BITMAP*> moveImg;
  std::vector<ALGIF_ANIMATION*> imgs;


};

#endif  // PEOPLE_H_INCLUDED