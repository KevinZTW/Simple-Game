#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <allegro5/allegro_video.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "algif5/src/algif.h"
#include <vector>
#include <list>
#include <string>
#include <time.h>

#include "Item.h"
#include "Circle.h"
#include "People.h"
#include "DeathBringer.h"
#include "Imp.h"
#include "Slime.h"
#include "Menu.h"
#include "Level.h"
#include "Wolf.h"
#include "Arcane.h"
#include "Archer.h"
#include "Canon.h"
#include "Poison.h"
#include "Storm.h"
#include "Attack.h"
#include "Slider.h"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7


// clock rate
const float FPS = 60;

// total number of level
const int LevelNum = 4;

// 1 coin every 2 seconds
const int CoinSpeed = FPS * 2;
const int Coin_Time_Gain = 1;

enum {Start =0 ,Game, End, Exit, Video1};
class GameWindow
{
public:

    // constructor
    GameWindow();

    // each process of scene
    void video_display(ALLEGRO_VIDEO *video);
    void play_video();
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();

    int game_run();
    int game_update();

    void show_err_msg(int msg);
    void game_destroy();

        void init_start_menu();
    void init_end_menu();
    void run_start_menu();
    void run_end_menu();
    void screen_cleanup();
    // each drawing scene function
    void draw_running_map();

    // process of updated event
    int process_event();
    int process_menu_event();
    // detect if mouse hovers over a rectangle
    bool mouse_hover(int, int, int, int);
    // detect if a tower will be constructed on road
    bool isOnRoad();

    bool init_scene_monster(const std::string &config_path);
    void change_scene();
    Tower* create_tower(int);
    Monster* create_monster();

public:
    bool initial = true;
    int gameState = 0;
private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *tower[Num_TowerType];
    ALLEGRO_BITMAP *background = NULL;

    ALLEGRO_VIDEO * video;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT_QUEUE *video_event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *video_timer = NULL;
    ALLEGRO_TIMER *monster_pro = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;

    ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;

    LEVEL *level = NULL;
    Menu *menu = NULL;


    People* hero;
    std::vector<Monster*> monsterList;
    std::vector<Item*> itemList;
    int monster_state_update_counter = 0;
    int monster_state_update_frequency = 20;

    //menu
    ALLEGRO_BITMAP* start_menu_background[2];
    ALLEGRO_BITMAP* end_menu_background[2];
    int start_menu_select = 0;
    int end_menu_select = 0;
    //legacy
    std::vector<Monster*> monsterSet;
    std::list<Tower*> towerSet;

    int Monster_Pro_Count = 0;
    int Coin_Inc_Count = 0;
    int mouse_x, mouse_y;
    int selectedTower = -1, lastClicked = -1;

    bool redraw = false;
    bool mute = false;

    bool changeScene = false;
    int scene = 0;
    std::string monster_config_path = "./MonsterConfig/scene0.txt";
};


#endif // MAINWINDOW_H_INCLUDED
