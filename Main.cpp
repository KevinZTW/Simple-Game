#include "GameWindow.h"

int main(int argc, char *argv[]) {
  GameWindow *Game = new GameWindow();
    //在這邊寫個全域變數更改 key event 行為 + 先 draw start menu?
    Game->init_start_menu();
    while(Game->gameState == Start){
        //play start menu
        Game->run_start_menu();
    }
    Game->screen_cleanup();

    Game->game_init();
    Game->game_play();

  delete Game;
  return 0;
}
