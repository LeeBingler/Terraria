#include <mainGame.hpp>

#include <raylib.h>
#include <iostream>
#include <sys/types.h>

struct GameData {
  double positionX = 0;
  double positionY = 0;
  double movementSpeedPlayer = 200;
} gamedata;

GameData &getGameData() { return gamedata; }

bool gameInit() { return true; }

void handlePlayerMovement(double deltatime) {
  if (IsKeyDown(KEY_W))
    gamedata.positionY -= gamedata.movementSpeedPlayer * deltatime;
  if (IsKeyDown(KEY_S))
    gamedata.positionY += gamedata.movementSpeedPlayer * deltatime;
  if (IsKeyDown(KEY_D))
    gamedata.positionX += gamedata.movementSpeedPlayer * deltatime;
  if (IsKeyDown(KEY_A))
    gamedata.positionX -= gamedata.movementSpeedPlayer * deltatime;
}

bool gameUpdate() {
  double deltatime = GetFrameTime();
  if (deltatime > 1. * 5)
    deltatime = 1. * 5;

  handlePlayerMovement(deltatime);

  DrawRectangle(gamedata.positionX, gamedata.positionY, 50, 50, RED);
  return true;
}

bool gameClose() {
  std::cout << "\n\nCLOSED!!!!!!!!!\n\n";
  return true;
}
