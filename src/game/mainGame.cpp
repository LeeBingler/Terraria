#include "blocks.hpp"
#include <mainGame.hpp>
#include <mapGame.hpp>
#include <assetsManager.hpp>
#include <blocks.hpp>
#include <helpers.hpp>

#include <raylib.h>
#include <iostream>
#include <cmath>

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
  // Assets
  assetManager.loadAll();

  // Map
  gamedata.mapGame.create(30, 10);

  gamedata.mapGame.getBlock(0, 0)->type = Block::dirt;
  gamedata.mapGame.getBlock(1, 1)->type = Block::stone;
  gamedata.mapGame.getBlock(2, 2)->type = Block::ice;
  gamedata.mapGame.getBlock(3, 3)->type = Block::jar;
  gamedata.mapGame.getBlock(4, 4)->type = Block::boneBricks;

  // Camera
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

  float mouseWheelMovement = GetMouseWheelMove();
  gamedata.camera.zoom += mouseWheelMovement;
}

void handleMouseUpdateBlock(int blockX, int blockY) {

  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    auto block = gamedata.mapGame.getBlock(blockX, blockY);

    if (block)
      *block = {};
  }

  if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
    auto block = gamedata.mapGame.getBlock(blockX, blockY);

    if (block)
      block->type = Block::gold;
  }
}

void drawMap() {
  for (int y = 0; y < gamedata.mapGame.h; ++y) {
    for (int x = 0; x < gamedata.mapGame.w; ++x) {
      auto block = gamedata.mapGame.getBlockUnsafe(x, y);

      if (block.type != Block::air) {
        float positionX = x * gamedata.blockSize;
        float positionY = y * gamedata.blockSize;

        DrawTexturePro(assetManager.blockTextures, getTextureAtlas(block.type, 0, 32, 32),
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

  Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), gamedata.camera);
  int blockX = (int)floor(worldPos.x);
  int blockY = (int)floor(worldPos.y);

  handleCameraMovement(deltatime);
  handleMouseUpdateBlock(blockX, blockY);

  BeginMode2D(gamedata.camera);

  drawMap();

  // Draw the frame on mouse position
  DrawTexturePro(
      assetManager.frame, {0, 0, (float)assetManager.frame.width, (float)assetManager.frame.height},
      {(float)blockX, (float)blockY, gamedata.blockSize, gamedata.blockSize}, {}, 0, WHITE);

  EndMode2D();

  return true;
}

bool gameClose() {
  std::cout << "\n\nCLOSED!!!!!!!!!\n\n";
  return true;
}
