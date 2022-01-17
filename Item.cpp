#include "Item.h"


Item::Item(int id, int x, int y){
    type = id;
    circle = new Circle;
    circle->x =  x;
    circle->y =  y;
    circle->r = 10;


    ALLEGRO_BITMAP * img;
    for (int i = 0; i < item_categories; i++){
        std::string path= "./Item/" + std::to_string(i) + ".png";
        img = al_load_bitmap(path.c_str());
        imgs.push_back(img);
    }
}
Item::~Item() {
    for (auto i : imgs)al_destroy_bitmap(i);
}

void Item::Draw() {
    al_draw_bitmap(imgs[type], circle->x, circle->y, 0);
}