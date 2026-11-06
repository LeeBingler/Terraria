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
  const int movementSpeedPlayer = 7;

  const float blockSize = 1;

  Camera2D camera;

  MapGame mapGame;

} gamedata;

AssetsManager assetManager;

GameData &getGameData() { return gamedata; }

bool gameInit() {
  assetManager.loadAll();

  gamedata.mapGame.create(30, 10);

  gamedata.mapGame.getBlock(0, 0)->type = Block::dirt;
  gamedata.mapGame.getBlock(1, 1)->type = Block::dirt;

  gamedata.camera.target = {0, 0};
  gamedata.camera.zoom = 100;
  gamedata.camera.rotation = 0;

  return true;
}

void handleCameraMovement(double deltatime) {
  if (IsKeyDown(KEY_UP))
    gamedata.camera.target.y -= gamedata.movementSpeedPlayer * deltatime;
  if (IsKeyDown(KEY_DOWN))
    gamedata.camera.target.y += gamedata.movementSpeedPlayer * deltatime;
  if (IsKeyDown(KEY_RIGHT))
    gamedata.camera.target.x += gamedata.movementSpeedPlayer * deltatime;
  if (IsKeyDown(KEY_LEFT))
    gamedata.camera.target.x -= gamedata.movementSpeedPlayer * deltatime;
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

  gamedata.camera.offset = {(float)(GetScreenWidth() / 2.0), (float)(GetScreenHeight() / 2.0)};

  handleCameraMovement(deltatime);

  BeginMode2D(gamedata.camera);

  drawMap();

  EndMode2D();

  return true;
}

bool gameClose() {
  std::cout << "\n\nCLOSED!!!!!!!!!\n\n";
  return true;
}
