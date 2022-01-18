#include "Monster.h"
#include <iostream>
#include <string>
#include <random>
const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

const int img_num = 8;
Monster::Monster(std::string name, int x, int y, int r)
{

    this->step = 0;

    // default direction is right
    direction = RIGHT;

    circle = new Circle;
    circle->x = x;
    circle->y = y;
    circle->r = r;

//    circle->x = (path.front() % 15) * grid_width + grid_width/2;
//    circle->y = (path.front() / 15) * grid_height + grid_height/2;
//    circle->r = grid_width/2;



    class_name = name;
    std::cout << "load monster" << std::endl;
    for(int i = 0; i < img_num; i++){
        std::string gif_path ="./" + name + "/"+std::to_string(i)+".gif";
        ALGIF_ANIMATION* img =  algif_load_animation(gif_path.c_str());
        imgs.push_back(img);
    }
}

Monster::~Monster()
{

    //clean up gif animation
    for (auto i : imgs) algif_destroy_animation(i);
    imgs.clear();
    delete circle;
    al_destroy_sample_instance(attack_sound);
}
void Monster::Hurt(int power){
    al_play_sample_instance(attack_sound);
    Subtract_HP(power);
}
void Monster::UpdateState(int hero_x, int hero_y) {

    //attack animation duration, no further update
    if (attack_animation_counter < attack_animation_duration){
        attack_animation_counter++;
        return;
    }
    //no update if in cool down range
    int cool_down_duration = 5;
    int death_bringer_attack_img_offset_y = 65;
    int death_bringer_attack_img_offset_x = 95;
    int imp_attack_img_offset_y = 65;
    int imp_attack_img_offset_x = 95;

    //after attack recover
    if (state== LeftAttack || state== RightAttack){
        cool_down = true;
        if(class_name == "DeathBringer" && direction == LEFT) circle->x += death_bringer_attack_img_offset_x;
        if(class_name == "DeathBringer")circle->y += death_bringer_attack_img_offset_y;
        if(class_name == "Imp" ) circle->x += imp_attack_img_offset_x;
        if(class_name == "Imp")circle->y += imp_attack_img_offset_y;
        cool_down_counter = 0;
    }

    if (cool_down && cool_down_counter > cool_down_duration)cool_down = false;

    if (cool_down) {
        if (direction == LEFT) state = LeftIdle;
        else state = RightIdle;
        cool_down_counter++;
        return;
    }

    int edge = 20;




    int hero_diff = hero_x - circle->x;


    if (abs(hero_diff) < attack_dst){
        //attack!

        if(class_name == "DeathBringer")circle->y -= death_bringer_attack_img_offset_y;
        if(class_name == "DeathBringer" && direction == LEFT) circle->x -=death_bringer_attack_img_offset_x;
        if(class_name == "Imp" ) circle->x -= imp_attack_img_offset_x;
        if(class_name == "Imp")circle->y -= imp_attack_img_offset_y;
        attack_animation_counter = 0;
        if (hero_diff > 0) state= RightAttack, direction = RIGHT;
        else state = LeftAttack, direction = LEFT;

    }else if (abs(hero_diff) < chase_dst){
        //chase hero if close to it
        if (hero_diff > 0) state = RightRun, direction = RIGHT;
        else state = LeftRun, direction = LEFT;
    }else if (circle->x <edge || circle->x > window_width - edge){
        //if close to left/ right screen change move direction
        if (circle->x <edge) state = RightRun, direction = RIGHT;
        if (circle->x > window_width - edge) state = LeftRun, direction = LEFT;
    }else {
        //else random to idle/Movement state
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, 30); // define the range
        int rand_num = distr(gen);
        //30% to change state
        if (rand_num > 20) state = rand_num % 4;
    }
}
void Monster::Move(){
    if (state == RightRun) circle->x += 2;
    else if (state == LeftRun) circle->x -= 2;
};
bool
Monster::Subtract_HP(int harm_point)
{
    HealthPoint -= harm_point;

    return (HealthPoint <= 0);
}


//void
//Monster::Load_Move()
//{
//    char buffer[50];
//
//    for(int i=0; i < 4; i++)
//    {
//        for(int j=0; j<direction_count[i]; j++)
//        {
//            ALLEGRO_BITMAP *img;
//
//
//            sprintf(buffer, "./%s/%s_%d.png", class_name, direction_name[i], j);
//            img = al_load_bitmap(buffer);
//
//            if(img){
//                moveImg.push_back(img);
//            }
//
//        }
//    }
//}

void
Monster::Draw()
{
//    al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79,79, 200));
    ALLEGRO_BITMAP *bitmap = algif_get_bitmap(imgs[state], al_get_time());
    al_draw_bitmap(bitmap, circle->x, circle->y, 0);

    //    int w, h;
//    int offset = 0;

    // calculate the number of pictures before current direction
//    for(int i=0; i<direction; i++)
//        offset += direction_count[i];
//
//    if(!moveImg[offset + sprite_pos])
//        return;

    // get height and width of sprite bitmap
//    w = al_get_bitmap_width(moveImg[offset + sprite_pos]);
//    h = al_get_bitmap_height(moveImg[offset + sprite_pos]);


    // draw bitmap align grid edge
//    al_draw_bitmap(moveImg[offset + sprite_pos], circle->x - w/2, circle->y - (h - grid_height/2), 0);

    //al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79, 79, 200));
}
//
//bool
//Monster::Move()
//{
//    int target_grid_x, target_grid_y;
//
//    counter = (counter + 1) % draw_frequency;
//
//    if(counter == 0)
//        sprite_pos = (sprite_pos + 1) % direction_count[direction];
//
//    if(step + 1 < path.size())
//    {
//        // coordinate of next grid
//        target_grid_x = (path[step] % 15) * grid_width + grid_width/2;
//        target_grid_y = (path[step] / 15) * grid_height + grid_height/2;
//
//        if(circle->x == target_grid_x && circle->y == target_grid_y)
//        {
//            int cur_grid = path[step];
//            int next_grid = path[step+1];
//            int prev_direction = direction;
//
//            switch(direction)
//            {
//                case LEFT:
//                case RIGHT:
//                    if(next_grid == cur_grid - 15)
//                        direction = UP;
//                    else if(next_grid == cur_grid + 15)
//                        direction = DOWN;
//
//                    break;
//                case UP:
//                case DOWN:
//                    if(next_grid == cur_grid - 1)
//                        direction = LEFT;
//                    else if(next_grid == cur_grid + 1)
//                        direction = RIGHT;
//
//                    break;
//
//            }
//
//            step++;
//
//            if(prev_direction != direction)
//                sprite_pos = 0;
//
//            // reach final grid and set end point
//            if(step == path.size() - 1){
//                end_x = circle->x + axis_x[direction] * (2 * grid_width);
//                end_y = circle->y + axis_y[direction] * (2 * grid_height);
//            }
//        }
//    }
//
//    // when getting to end point, return true
//    if(circle->x == end_x && circle->y == end_y)
//        return true;
//
//    circle->x += speed * axis_x[direction];
//    circle->y += speed * axis_y[direction];
//
//    // if not reaching end point, return false
//    return false;
//}


