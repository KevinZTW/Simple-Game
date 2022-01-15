#include "GameWindow.h"

int main(int argc, char *argv[]) {
  GameWindow *TowerGame = new GameWindow();
    //在這邊寫個全域變數更改 key event 行為 + 先 draw start menu?
  TowerGame->game_play();

  delete TowerGame;
  return 0;
}
