#include "People.h"
#include <iostream>
#include <allegro5/allegro_image.h>
/* Take Monster.cpp as refernce */


const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

void People::Set_Move(int dir) {
    action = true;
    direction = dir;
}
void People::Set_Stop(){
    action = false;
}
void People::Move(){
    if (direction == RIGHT) circle->x += 1;
    else if (direction == LEFT) circle->x -= 1;

    counter = (counter + 1) % draw_frequency;

    if(counter == 0)
        sprite_pos = (sprite_pos + 1) % direction_count[direction];
};

People::People() {
  circle = new Circle;
    circle->x =  10;
    circle->y =  window_height/3;
    circle->r = grid_width/2;

    sprite_pos = 0;
    counter = 0;


    // default direction is right
    direction = RIGHT;

    //Under object might override this value
    direction_count[LEFT] = 1;
    direction_count[RIGHT] = 1;
    direction_count[UP] = 1;
    direction_count[DOWN] = 1;

    //the hero class would overide
//  strncpy(class_name, "Hero", 20);
}

People::~People() {
  for (unsigned int i = 0; i < moveImg.size(); i++) {
    ALLEGRO_BITMAP *img = moveImg[i];

    moveImg.erase(moveImg.begin() + i);

    i--;
    al_destroy_bitmap(img);
  }
  moveImg.clear();

  delete circle;
}
void People::Test() {
    std::cout <<"Hi, I am" <<class_name<< std::endl;
}
void
People::Load_Move() {
  char buffer[50];
  for (int i = 0; i < 4; i++) {

    for (int j = 0; j < direction_count[i]; j++) {

        ALLEGRO_BITMAP *img;

//        img = al_load_bitmap("./Hero/DOWN_1.png");


        sprintf(buffer, "./%s/%s_%d.png", class_name, direction_name[i], j);
        img = al_load_bitmap(buffer);
        std::cout << buffer << std::endl;

      if (img) {
          moveImg.push_back(img);
      }

    }
  }
}

void
People::Draw() {

    int w, h;
    int offset = 0;
    // calculate the number of pictures before current direction
    for (int i = 0; i < direction; i++) offset += direction_count[i];

//    if (!moveImg[offset + sprite_pos]) return;

    // get height and width of sprite bitmap
    w = al_get_bitmap_width(moveImg[offset + sprite_pos]);
    h = al_get_bitmap_height(moveImg[offset + sprite_pos]);

    // draw bitmap align grid edge
//    al_draw_bitmap(moveImg[offset + sprite_pos], circle->x ,
//                   circle->y, 0);

    al_draw_bitmap(moveImg[offset + sprite_pos], circle->x - w / 2,
                   circle->y - (h - grid_height / 2), 0);

//     al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79,
//     79, 200));


}
