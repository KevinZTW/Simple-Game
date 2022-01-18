#include "People.h"
#include <iostream>


#include <allegro5/allegro_image.h>
/* Take Monster.cpp as refernce */


const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};
const int img_num = 8;
// set counter frequency of drawing moving animation
const int draw_frequency = 10;


void People::Set_Attack(std::vector<Monster*> &monsters) {
    if(direction == LEFT) state = LeftAttack;
    else state = RightAttack;
    if (attack_empower_counter == attack_empower_duration-1)Attack(monsters);
    else attack_empower_counter = (attack_empower_counter+1) %attack_empower_duration;
}

void People::Attack(std::vector<Monster*> &monsters) {
    al_play_sample_instance(swing_sound);
    for(auto monster : monsters) {
        int monster_diff = monster->getX() - circle->x;
        if (monster_diff < attack_dst) monster->Hurt(attack_pow);
    }
}

void People::Set_Run(int dir) {
    action = true;
    direction = dir;

    if(direction == LEFT) state = LeftRun;
    else state = RightRun;
}
void People::Set_Idle(){
    action = false;
    if(direction == LEFT) state = LeftIdle;
    else state = RightIdle;
}
void People::Move(){
    al_play_sample_instance(walk_sound);
    if (direction == RIGHT) circle->x += speed;
    else if (direction == LEFT) circle->x -= speed;
};

void People::Hurt(int power){
        std::cout <<"hurt!"<<std::endl;
    al_play_sample_instance(hurt_sound);
    if (hurt_cool_down_counter == hurt_cool_down_duration - 1){
        std::cout <<"  trigger"<<std::endl;
        HealthPoint -=power;
        circle->x -= hurt_hit_back_dst;
        //todo add sound

        //todo add image effect

    }
        hurt_cool_down_counter = (hurt_cool_down_counter+1)%hurt_cool_down_duration;

}


People::People() {
  circle = new Circle;
    circle->x =  10;
    circle->y =  window_height - 100;
    circle->r = grid_width / 2;


    // default direction is right
    direction = RIGHT;

    //Under object might override this value
    for(int i = 0; i < img_num; i++){
        std::string gif_path ="./Hero2/"+std::to_string(i)+".gif";
        ALGIF_ANIMATION* img =  algif_load_animation(gif_path.c_str());
        imgs.push_back(img);
    }
    //load sound
    ALLEGRO_SAMPLE *sample;
    sample = al_load_sample("./Hero2/collect.ogg");
    collect_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(collect_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(collect_sound, al_get_default_mixer());

    sample = al_load_sample("./Hero2/hurt.ogg");
    hurt_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(hurt_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(hurt_sound, al_get_default_mixer());

    sample = al_load_sample("./Hero2/walk.ogg");
    walk_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(walk_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(walk_sound, al_get_default_mixer());

    sample = al_load_sample("./Hero2/swing.ogg");
    swing_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(swing_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(swing_sound, al_get_default_mixer());

    sample = al_load_sample("./Hero2/level.ogg");
    level_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(level_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(level_sound, al_get_default_mixer());

}

People::~People() {

 for (auto i : imgs) algif_destroy_animation(i);
 imgs.clear();
    al_destroy_sample_instance(collect_sound);
    al_destroy_sample_instance(hurt_sound);
    al_destroy_sample_instance(walk_sound);
    al_destroy_sample_instance(swing_sound);
    al_destroy_sample_instance(level_sound);
  delete circle;
}
void People::Level_Up() {
    al_play_sample_instance(level_sound);
    HealthPoint += 20;
    exp -= leveup_exp_req;
    leveup_exp_req *= 2;
    level += 1;
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

      if (img) {
          moveImg.push_back(img);
      }

    }
  }
}

void
People::Draw() {

//    al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79,79, 200));
    ALLEGRO_BITMAP *bitmap = algif_get_bitmap(imgs[state], al_get_time());
    al_draw_bitmap(bitmap, circle->x-100, circle->y-100, 0);

//    int w, h;
//    int offset = 0;
    // calculate the number of pictures before current direction
//    for (int i = 0; i < direction; i++) offset += direction_count[i];

//    if (!moveImg[offset + sprite_pos]) return;

    // get height and width of sprite bitmap
//    w = al_get_bitmap_width(moveImg[offset + sprite_pos]);
//    h = al_get_bitmap_height(moveImg[offset + sprite_pos]);

    // draw bitmap align grid edge
//    al_draw_bitmap(moveImg[offset + sprite_pos], circle->x ,
//                   circle->y, 0);

//    al_draw_bitmap(moveImg[offset + sprite_pos], circle->x - w / 2,
//                   circle->y - (h - grid_height / 2), 0);




}
