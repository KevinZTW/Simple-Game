#include "GameWindow.h"

#include <iostream>
#include <fstream>
#include "People.h"
#include "global.h"
#include "Item.h"

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

float Attack::volume = 1.0;

void set_attack_volume(float volume) { Attack::volume = volume; }

bool compare(Tower *t1, Tower *t2) { return (t1->getY() <= t2->getY()); }

void GameWindow::game_init() {
  char buffer[50];

  icon = al_load_bitmap("./icon.png");
  background = al_load_bitmap("./src/Background.png");

//  for (int i = 0; i < Num_TowerType; i++) {
//    sprintf(buffer, "./Tower/%s.png", TowerClass[i]);
//    tower[i] = al_load_bitmap(buffer);
//  }

  al_set_display_icon(display, icon);
  al_reserve_samples(5);

  sample = al_load_sample("growl.wav");
  startSound = al_create_sample_instance(sample);
  al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
  al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

  sample = al_load_sample("BackgroundMusic.ogg");
  backgroundSound = al_create_sample_instance(sample);
  al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
  al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());

  level = new LEVEL(1);
  hero = new People;
  menu = new Menu(hero);

}

bool GameWindow::mouse_hover(int startx, int starty, int width, int height) {
  if (mouse_x >= startx && mouse_x <= startx + width)
    if (mouse_y >= starty && mouse_y <= starty + height) return true;

  return false;
}

bool GameWindow::isOnRoad() {
  int startx, starty;
  int widthOfTower;

  widthOfTower = TowerWidth[selectedTower];

  for (int i = 0; i < NumOfGrid; i++) {
    startx = (i % 15) * 40;
    starty = (i / 15) * 40;

    if (level->isRoad(i)) {
      if ((mouse_x + (widthOfTower / 2) < startx) ||
          (mouse_x - (widthOfTower / 2) > startx + grid_width))
        continue;
      else if ((mouse_y + (widthOfTower / 2) < starty) ||
               (mouse_y > starty + grid_height))
        continue;
      else
        return true;
    }
  }
  return false;
}

Tower *GameWindow::create_tower(int type) {
  Tower *t = NULL;

  if (isOnRoad()) return t;

  switch (type) {
    case ARCANE:
      t = new Arcane(mouse_x, mouse_y);
      break;
    case ARCHER:
      t = new Archer(mouse_x, mouse_y);
      break;
    case CANON:
      t = new Canon(mouse_x, mouse_y);
      break;
    case POISON:
      t = new Poison(mouse_x, mouse_y);
      break;
    case STORM:
      t = new Storm(mouse_x, mouse_y);
      break;
    default:
      break;
  }

  menu->Change_Coin(menu->getTowerCoin(type));

  return t;
}
void GameWindow::change_scene(){
    //clean up
    al_destroy_bitmap(background);
    monsterList.clear();

    std::string background_path = "./src/" + std::to_string(scene) + ".png";
    std::string config_path = "./MonsterConfig/scene" + std::to_string(scene)+".txt";
    background = al_load_bitmap(background_path.c_str());
    init_scene_monster(config_path);


}

void GameWindow::more_monster(){
    std::cout << "more!!" <<std::endl;
//    Monster * m = NULL;
//    m = new Slime(100, 1000, 10);
//    monsterList.push_back(m);
//    m = new Slime(720, 1000, 10);
//    monsterList.push_back(m);
//    m = new Slime(400, 1000, 10);
//    monsterList.push_back(m);
//    m = new Imp(50, 1000, 10);
//    monsterList.push_back(m);
//    m = new DeathBringer(600, 1000, 10);
//    monsterList.push_back(m);
}

bool GameWindow::init_scene_monster(const std::string &config_path){
    //open monster config file
    std::ifstream config_in;
    config_in.open(config_path, std::ios::in);
    int monster_num;

    config_in >> monster_num;
    Monster * m = NULL;
    for (int i = 0; i < monster_num; i++){
        std::string monster_type;
        int x, y, r;
        config_in >> monster_type >> x >> y >> r;
        if (monster_type == "DeathBringer"){
            std::cout <<"add death bringer" << x << y << r<<std::endl;
            m = new DeathBringer(x, y, r);
        }else if (monster_type == "Imp"){
            m = new Imp(x, y, r);
        }else if (monster_type == "Slime"){
            m = new Slime(x, y, r);
        }else if (monster_type == "Knuckle"){
            m = new Knuckle(x, y, r);
        }
        monsterList.push_back(m);
    }


    return true;
}

Monster *GameWindow::create_monster() {
  Monster *m = NULL;

  if (level->MonsterNum[WOLF]) {
    level->MonsterNum[WOLF]--;
//    m = new Wolf(level->ReturnPath());
  } else if (level->MonsterNum[WOLFKNIGHT]) {
    level->MonsterNum[WOLFKNIGHT]--;
  } else if (level->MonsterNum[DEMONNIJIA]) {
    level->MonsterNum[DEMONNIJIA]--;

  } else if (level->MonsterNum[CAVEMAN]) {
    level->MonsterNum[CAVEMAN]--;
  } else {
    al_stop_timer(monster_pro);
  }

  return m;
}

void GameWindow::game_play() {
  int msg;

  srand(time(NULL));

  msg = -1;
  game_reset();
  game_begin();


  while (msg != GAME_EXIT) {
    msg = game_run();
  }

}

void GameWindow::show_err_msg(int msg) {
  if (msg == GAME_TERMINATE)
    fprintf(stderr, "Game Terminated...");
  else
    fprintf(stderr, "unexpected msg: %d", msg);

  game_destroy();
  exit(9);
}

GameWindow::GameWindow() {
  // al_init 助教說用來初始化 allego 各種設定
  if (!al_init()) show_err_msg(-1);

  printf("Game Initializing...\n");

  display = al_create_display(window_width, window_height);
  //可以用 al_set_window...調整視窗置放的地方

  event_queue = al_create_event_queue();
  video_event_queue = al_create_event_queue();
    video_timer = al_create_timer(1.0 / 120);
  timer = al_create_timer(1.0 / FPS);
  monster_pro = al_create_timer(1.0 / FPS);

  /*
  below is for practice only
  al_clear_to_color(al_map_rgb(255, 255, 0));  //設一個顏色，會進到 buffer
  al_flip_display();                           //從 buffer 渲染到畫面上
  // al_reset(5); 可以停五秒鐘

  */
  if (timer == NULL || monster_pro == NULL) show_err_msg(-1);

  if (display == NULL || event_queue == NULL) show_err_msg(-1);

  al_init_primitives_addon();
  al_init_font_addon();    // initialize the font addon
  al_init_ttf_addon();     // initialize the ttf (True Type Font) addon
  al_init_image_addon();   // initialize the image addon
  al_init_acodec_addon();  // initialize acodec addon
  al_init_video_addon(); // init video add on

  al_install_keyboard();  // install keyboard event
  al_install_mouse();     // install mouse event
  al_install_audio();     // install audio event
  video = al_open_video("./src/0.ogm");

  ALLEGRO_EVENT_SOURCE  *temp = al_get_video_event_source(video);
  al_register_event_source(video_event_queue, temp);


  font = al_load_ttf_font("Caviar_Dreams_Bold.ttf", 12, 0);  // load small font
  Medium_font =
      al_load_ttf_font("Caviar_Dreams_Bold.ttf", 24, 0);  // load medium font
  Large_font =
      al_load_ttf_font("Caviar_Dreams_Bold.ttf", 36, 0);  // load large font

  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_mouse_event_source());

  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  al_register_event_source(event_queue, al_get_timer_event_source(monster_pro));

    al_register_event_source(video_event_queue, al_get_timer_event_source(video_timer));

}

void GameWindow::video_display(ALLEGRO_VIDEO *video){
            ALLEGRO_BITMAP *frame = al_get_video_frame(video);
    if(!frame)return ;
        al_draw_scaled_bitmap(frame,
                              0,0,
                              al_get_bitmap_width(frame),
                                al_get_bitmap_height(frame),
                               0,0,
                                al_get_display_width(display),
                              al_get_display_height(display), 0);

        al_flip_display();
}

void GameWindow::play_video() {


    al_start_timer(video_timer);

    al_reserve_samples(1);
    al_start_video(video, al_get_default_mixer());
    while(1){
        std::cout <<"flip"<<std::endl;
        al_wait_for_event(video_event_queue, &event);
        if(event.type == ALLEGRO_EVENT_TIMER){
            video_display(video);
        }else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_close_video(video);
            break;
        }else if (event.type == ALLEGRO_EVENT_VIDEO_FINISHED){
            break;
        }

    }
}

void GameWindow::init_start_menu(){
    start_menu_background[0] = al_load_bitmap("./src/start/0.png");
    start_menu_background[1] = al_load_bitmap("./src/start/1.png");
}
void GameWindow::init_end_menu(){
    end_menu_background[0] = al_load_bitmap("./src/end/0.png");
    end_menu_background[1] = al_load_bitmap("./src/end/1.png");
}

void GameWindow::run_start_menu(){
    if (!al_is_event_queue_empty(event_queue)) {
        process_menu_event();
    }
    al_draw_bitmap(start_menu_background[start_menu_select], 0, 0, 0);
    al_flip_display();
}

void GameWindow::run_end_menu(){
    if (!al_is_event_queue_empty(event_queue)) {
        process_menu_event();
    }
    al_draw_bitmap(end_menu_background[end_menu_select], 0, 0, 0);
    al_flip_display();
}

void GameWindow::screen_cleanup(){
    al_destroy_bitmap(background);
}

void GameWindow::game_begin() {
  printf(">>> Start Level[%d]\n", level->getLevel());
  //必須先 load 不然等等 draw running map ....
  init_scene_monster(monster_config_path);
  draw_running_map();

//  al_play_sample_instance(startSound);
//  while (al_get_sample_instance_playing(startSound))
//    ;
  al_play_sample_instance(backgroundSound);

    al_start_timer(timer);
  al_start_timer(monster_pro);
}

int GameWindow::game_run() {
  int error = GAME_CONTINUE;

  if (!al_is_event_queue_empty(event_queue)) {
    error = process_event();
  }
  return error;
}

int GameWindow::game_update() {

    //update hero  action
    if(hero->action){
        hero->Move();
    }
    int hero_hurt_by_dst = false;
    for (auto it = monsterList.begin(); it !=monsterList.end();it++){
        int dst = abs((*it)->getX() -  hero->getX());
        if (dst < 10)hero_hurt_by_dst = true;
    }

    if (hero_hurt_by_dst) {
        hero->Hurt(5);
    }

    if (hero->getHealth() <= 0)return GAME_EXIT;
    //reach
    if (hero->getX() >window_width - 10){
        scene++;

        change_scene();
        hero->reset_position(0);
    } else if (hero->getX() < 10 && scene>0){
        scene--;
        change_scene();
        hero->reset_position(1);
    }

    //====Monster========
    //kill monster if no HP
    int more = false;
    for (auto it = monsterList.begin(); it !=monsterList.end();){
        if ((*it)->getWorth() == 3000){
            //kunckle!
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 gen(rd()); // seed the generator
            std::uniform_int_distribution<> distr(0, 80); // define the range
            int rand_num = distr(gen);
            if (rand_num < 2){
                al_play_sample_instance((*it)->crazy_sound);
                more = true;


            }
        }
        if ((*it)->getHealth() < 1) {

            //random item


            //else random to idle/Movement state
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 gen(rd()); // seed the generator
            std::uniform_int_distribution<> distr(0, 6); // define the range
            int rand_num = distr(gen);
            if (rand_num < 3){
                Item * item = new Item(rand_num, (*it)->getX(), window_height - 100);
                itemList.push_back(item);
            }
            hero->exp += (*it)->getWorth();
            if(hero->exp > hero->leveup_exp_req){

                hero->Level_Up();

            }
            monsterList.erase(it);
        }else  ++it;
    }


    if (more){
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, 1000); // define the range
        int rand_num = distr(gen);

        Monster * m = new Slime(rand_num, 1000, 10);
        monsterList.push_back(m);
    }
    //update monster action
    //current move left or move right
    for (auto monster : monsterList) monster->Move();

    //update monster state
    if (monster_state_update_counter == 0){
        for (auto monster : monsterList) monster->UpdateState(hero->getX(), hero->getY());
    }
    //update counter
    monster_state_update_counter = (monster_state_update_counter + 1) % monster_state_update_frequency;

  return GAME_CONTINUE;
}

void GameWindow::game_reset() {
  // reset game and begin
  for (auto &&child : towerSet) {
    delete child;
  }

  monsterList.clear();
  itemList.clear();


  redraw = false;


  // stop sample instance
  al_stop_sample_instance(backgroundSound);
  al_stop_sample_instance(startSound);
  // stop timer
  al_stop_timer(timer);
  al_stop_timer(monster_pro);
}

void GameWindow::game_destroy() {
  game_reset();

  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
    al_destroy_event_queue(video_event_queue);
  al_destroy_font(font);
  al_destroy_font(Medium_font);
  al_destroy_font(Large_font);

  al_destroy_timer(timer);
  al_destroy_timer(monster_pro);
    al_destroy_timer(video_timer);

  for (int i = 0; i < 5; i++) al_destroy_bitmap(tower[i]);

  al_destroy_bitmap(icon);
  al_destroy_bitmap(background);

  al_destroy_sample(sample);
  al_destroy_sample_instance(startSound);
  al_destroy_sample_instance(backgroundSound);

  delete level;
  delete menu;
}
int GameWindow::process_menu_event(){
    al_wait_for_event(event_queue, &event);
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (event.keyboard.keycode) {

            case ALLEGRO_KEY_UP:
                if (gameState==Start) {
                    if (start_menu_select > 0)start_menu_select--;
                }else {
                    if (end_menu_select > 0)end_menu_select--;
                };
                break;
            case ALLEGRO_KEY_DOWN:
                if (gameState==Start) {
                    if (start_menu_select < 1)start_menu_select++;
                }else {
                    if (end_menu_select < 1)end_menu_select++;
                }
                break;
            case ALLEGRO_KEY_ENTER:
                if (gameState==Start){
                    if (start_menu_select == 0) gameState = Game;
                    if (start_menu_select == 1) exit(0);
                }else if (gameState==End){
                    if (end_menu_select == 0) gameState = Game;
                    if (end_menu_select == 1) exit(0);
                }

                break;
            case ALLEGRO_KEY_M:
                mute = !mute;
                if (mute)
                    al_stop_sample_instance(backgroundSound);
                else
                    al_play_sample_instance(backgroundSound);
                break;
        }
    }
}
int GameWindow::process_event() {
  int i;
  int instruction = GAME_CONTINUE;

  // offset for pause window
  int offsetX = field_width / 2 - 200;
  int offsetY = field_height / 2 - 200;

  al_wait_for_event(event_queue, &event);
  redraw = false;

  // allergo timer event
//  std::cout << "process event" << event.type << std::endl;

  if (event.type == ALLEGRO_EVENT_TIMER) {


    if (event.timer.source == timer) {
      redraw = true;

      if (Coin_Inc_Count == 0) menu->Change_Coin(Coin_Time_Gain);

      Coin_Inc_Count = (Coin_Inc_Count + 1) % CoinSpeed;

      //legacy code
//      if (monsterSet.size() == 0 && !al_get_timer_started(monster_pro)) {
//        al_stop_timer(timer);
//        return GAME_EXIT;
//      }

    } else {
//      if (Monster_Pro_Count == 0) {
//        Monster *m = create_monster();
//
//        if (m != NULL) monsterSet.push_back(m);
//      }
//      Monster_Pro_Count = (Monster_Pro_Count + 1) % level->getMonsterSpeed();
    }
  } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
    return GAME_EXIT;
      // key down event!
  } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
    switch (event.keyboard.keycode) {


        case ALLEGRO_KEY_RIGHT:
            std::cout << "right down" << std::endl;
            hero->Set_Run(RIGHT);
            break;

        case ALLEGRO_KEY_LEFT:
            std::cout << "left down" << std::endl;
            hero->Set_Run(LEFT);
            //todo
            break;
        case ALLEGRO_KEY_A:
            std::cout << "a down" << std::endl;
            hero->Set_Attack(monsterList);
            break;
        case ALLEGRO_KEY_Z:
            std::cout << "z down" << std::endl;
            for (auto it = itemList.begin(); it != itemList.end();) {
                int diff = abs((*it)->getX() - hero->getX());
                if (diff < 50) {
                    //collect item
                    al_play_sample_instance(hero->collect_sound);
                    if ((*it)->type==HealthPack) hero->AddHealth(20);
                    itemList.erase(it);
                } else {
                    it++;
                }
            }
            break;
        case ALLEGRO_KEY_UP:
            //hero.jump();
            break;
        case ALLEGRO_KEY_P:
        /*TODO: handle pause event here*/
        // notice that there are two timer, we need to stop both of them
        if (al_get_timer_started(timer))
          al_stop_timer(timer);
        else
          al_start_timer(timer);

        if (al_get_timer_started(monster_pro))
          al_stop_timer(monster_pro);
        else
          al_start_timer(monster_pro);
        break;
      case ALLEGRO_KEY_M:
        mute = !mute;
        if (mute)
          al_stop_sample_instance(backgroundSound);
        else
          al_play_sample_instance(backgroundSound);
        break;
    }
  } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
      switch (event.keyboard.keycode) {
          case ALLEGRO_KEY_RIGHT:
              std::cout << "right up" << std::endl;
              hero->Set_Idle();
              break;
          case ALLEGRO_KEY_LEFT:
              std::cout << "left up" << std::endl;
              hero->Set_Idle();
              break;
          case ALLEGRO_KEY_A:
              std::cout << "a up" << std::endl;
              hero->Set_Idle();
              break;
      }
  } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
    if (event.mouse.button == 1) {
      if (selectedTower != -1 && mouse_hover(0, 0, field_width, field_height)) {
        Tower *t = create_tower(selectedTower);

        if (t == NULL)
          printf("Wrong place\n");
        else {
          towerSet.push_back(t);
          towerSet.sort(compare);
        }
      } else if (selectedTower == -1) {
        std::list<Tower *>::iterator it = towerSet.begin();
        if (lastClicked != -1) {
          std::advance(it, lastClicked);
          (*it)->ToggleClicked();
        }
        for (i = 0, it = towerSet.begin(); it != towerSet.end(); it++, i++) {
          Circle *circle = (*it)->getCircle();
          int t_width = (*it)->getWidth();

          if (mouse_hover(circle->x - t_width / 2, circle->y, t_width,
                          t_width / 2)) {
            (*it)->ToggleClicked();
            lastClicked = i;
            break;
          } else {
            lastClicked = -1;
          }
        }
      }
      // check if user wants to create some kind of tower
      // if so, show tower image attached to cursor
      selectedTower = menu->MouseIn(mouse_x, mouse_y);
    }
  } else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
    mouse_x = event.mouse.x;
    mouse_y = event.mouse.y;

    menu->MouseIn(mouse_x, mouse_y);
  }

  if (redraw) {
    // update each object in game
    instruction = game_update();

    // Re-draw map
    draw_running_map();
    redraw = false;
  }

  return instruction;
}

void GameWindow::draw_running_map() {


  al_clear_to_color(al_map_rgb(100, 100, 100));
  //draw background
  al_draw_bitmap(background, 0, 0, 0);
    menu->Draw();
    hero->Draw();

    for (auto monster : monsterList) monster->Draw();
    for (auto item : itemList)item->Draw();
    al_flip_display();

    //unsigned int i, j;
    //can't see what this for.. seems to be the frame for tower selection
//  for (i = 0; i < field_height / 40; i++) {
//    for (j = 0; j < field_width / 40; j++) {
//      char buffer[50];
//      sprintf(buffer, "%d", i * 15 + j);
//      if (level->isRoad(i * 15 + j)) {
//        al_draw_filled_rectangle(j * 40, i * 40, j * 40 + 40, i * 40 + 40,
//                                 al_map_rgb(255, 244, 173));
//      }
//      // al_draw_text(font, al_map_rgb(0, 0, 0), j*40, i*40,
//      // ALLEGRO_ALIGN_CENTER, buffer);
//    }
//  }


//this used to draw the side bar
//  al_draw_filled_rectangle(field_width, 0, window_width, window_height,
//                           al_map_rgb(100, 100, 100));




    //  for (i = 0; i < monsterSet.size(); i++) {
//    monsterSet[i]->Draw();
//  }
//
//  for (std::list<Tower *>::iterator it = towerSet.begin(); it != towerSet.end();
//       it++)
//    (*it)->Draw();
//
//  if (selectedTower != -1)
//    Tower::SelectedTower(mouse_x, mouse_y, selectedTower);
}

