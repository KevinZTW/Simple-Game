#include "GameWindow.h"

int main(int argc, char *argv[]) {
  GameWindow *Game = new GameWindow();
    //在這邊寫個全域變數更改 key event 行為 + 先 draw start menu?
    Game->play_video();

    while(Game->gameState !=Exit){

        Game->init_start_menu();
        while(Game->gameState == Start){
            //play start menu
            Game->run_start_menu();
        }
        Game->screen_cleanup();

        Game->game_init();
        Game->game_play();

        //end menu

//        Game->screen_cleanup();
        Game->init_end_menu();
        Game->gameState = End;
        while(Game->gameState == End){
            //show end menu
            Game->run_end_menu();
        }
        Game->game_reset();
    }

    Game->show_err_msg(GAME_EXIT);
  delete Game;
  return 0;
}
