#include <mainGame.hpp>
#include <assetsManager.hpp>

#include <raylib.h>
#include <iostream>
#include <sys/types.h>

struct GameData {
  double positionX = 0;
  double positionY = 0;
  double movementSpeedPlayer = 200;

  Texture TextureDirt;
} gamedata;

AssetsManager assetManager;

GameData &getGameData() { return gamedata; }

bool gameInit() {
  assetManager.loadAll();

  return true;
}

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

  DrawTexturePro(assetManager.dirt,
                 {0, 0, (float)assetManager.dirt.width, (float)assetManager.dirt.height},
                 {50, 50, 50, 50}, {}, 0, WHITE);

  return true;
}

bool gameClose() {
  std::cout << "\n\nCLOSED!!!!!!!!!\n\n";
  return true;
}
