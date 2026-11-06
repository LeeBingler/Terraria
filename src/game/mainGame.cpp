#include <blocks.hpp>
#include <mainGame.hpp>
#include <mapGame.hpp>
#include <assetsManager.hpp>

#include <raylib.h>
#include <iostream>
#include <sys/types.h>

struct GameData {
  double positionX = 0;
  double positionY = 0;
  double movementSpeedPlayer = 200;

  float blockSize = 32;

  MapGame mapGame;

} gamedata;

AssetsManager assetManager;

GameData &getGameData() { return gamedata; }

bool gameInit() {
  assetManager.loadAll();

  gamedata.mapGame.create(30, 10);

  gamedata.mapGame.getBlock(0, 0)->type = Block::dirt;
  gamedata.mapGame.getBlock(1, 1)->type = Block::dirt;

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

void drawMap() {
  for (int y = 0; y < gamedata.mapGame.h; ++y) {
    for (int x = 0; x < gamedata.mapGame.w; ++x) {
      auto block = gamedata.mapGame.getBlockUnsafe(x, y);

      if (block.type != Block::air) {
        float positionX = x * gamedata.blockSize;
        float positionY = y * gamedata.blockSize;

        DrawTexturePro(assetManager.dirt,
                       {0, 0, (float)assetManager.dirt.width, (float)assetManager.dirt.height},
                       {positionX, positionY, gamedata.blockSize, gamedata.blockSize}, {}, 0,
                       WHITE);
      }
    }
  }
}

bool gameUpdate() {
  double deltatime = GetFrameTime();
  if (deltatime > 1. * 5)
    deltatime = 1. * 5;

  handlePlayerMovement(deltatime);

  drawMap();

  // Player drawing
  DrawRectangle(gamedata.positionX, gamedata.positionY, gamedata.blockSize, gamedata.blockSize,
                RED);

  return true;
}

bool gameClose() {
  std::cout << "\n\nCLOSED!!!!!!!!!\n\n";
  return true;
}
