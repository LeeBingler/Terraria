#include "blocks.hpp"
#include <mainGame.hpp>
#include <mapGame.hpp>
#include <assetsManager.hpp>
#include <blocks.hpp>
#include <helpers.hpp>

#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>

struct GameData {
  double positionX = 0;
  double positionY = 0;
  const int movementSpeedPlayer = 7;

  const float blockSize = 1;

  int blockType = Block::air;
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
  gamedata.mapGame.getBlock(5, 5)->type = Block::woodLog;

  gamedata.mapGame.getBlockBg(6, 6)->type = Block::blueRubyBlockWall;

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

    block = gamedata.mapGame.getBlockBg(blockX, blockY);

    if (block)
      *block = {};
  }

  if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
    Block *block = {};

    if (gamedata.blockType < Block::BLOCK_BACKGROUND)
      block = gamedata.mapGame.getBlock(blockX, blockY);
    else
      block = gamedata.mapGame.getBlockBg(blockX, blockY);

    if (block)
      block->type = gamedata.blockType;
  }
}

void handleKeyboardBlock() {
  if (IsKeyDown(KEY_ZERO))
    gamedata.blockType = Block::air;
  if (IsKeyDown(KEY_ONE))
    gamedata.blockType = Block::woodLog;
  if (IsKeyDown(KEY_TWO))
    gamedata.blockType = Block::leaves;
  if (IsKeyDown(KEY_THREE))
    gamedata.blockType = Block::rubyBlockWall;
  if (IsKeyDown(KEY_FOUR))
    gamedata.blockType = Block::bricks;
  if (IsKeyDown(KEY_FIVE))
    gamedata.blockType = Block::grass;
  if (IsKeyDown(KEY_SIX))
    gamedata.blockType = Block::stone;
  if (IsKeyDown(KEY_SEVEN))
    gamedata.blockType = Block::copper;
  if (IsKeyDown(KEY_EIGHT))
    gamedata.blockType = Block::clay;
}

void drawMap() {
  // Get border of screen to render only what we see
  Vector2 topLeftView = GetScreenToWorld2D({0, 0}, gamedata.camera);
  Vector2 bottomRightView =
      GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, gamedata.camera);

  int startViewX = (int)floorf(topLeftView.x - 1);
  int endViewX = (int)ceilf(bottomRightView.x - 1);
  int startViewY = (int)floorf(topLeftView.y - 1);
  int endViewY = (int)ceilf(bottomRightView.y - 1);

  startViewX = Clamp(startViewX, 0, gamedata.mapGame.w - 1);
  endViewX = Clamp(endViewX, 0, gamedata.mapGame.w - 1);

  startViewY = Clamp(startViewY, 0, gamedata.mapGame.h - 1);
  endViewY = Clamp(endViewY, 0, gamedata.mapGame.h - 1);

  // Drawing map
  for (int y = startViewY; y <= endViewY; ++y) {
    for (int x = startViewX; x <= endViewX; ++x) {
      auto block = gamedata.mapGame.getBlockUnsafe(x, y);
      auto blockBg = gamedata.mapGame.getBlockUnsafeBg(x, y);
      const float positionX = x * gamedata.blockSize;
      const float positionY = y * gamedata.blockSize;

      // Drawing background block
      if (blockBg.type != Block::air) {

        DrawTexturePro(assetManager.blockTextures, getTextureAtlas(blockBg.type - 1, 0, 32, 32),
                       {positionX, positionY, gamedata.blockSize, gamedata.blockSize}, {}, 0,
                       WHITE);
      }

      // Drawing front block
      if (block.type != Block::air && block.type != Block::woodLog) {

        DrawTexturePro(assetManager.blockTextures, getTextureAtlas(block.type, 0, 32, 32),
                       {positionX, positionY, gamedata.blockSize, gamedata.blockSize}, {}, 0,
                       WHITE);

        // Draw woolLog
      } else if (block.type == Block::woodLog) {
        const auto blockUp = gamedata.mapGame.getBlock(x, y - 1);
        const auto blockDown = gamedata.mapGame.getBlock(x, y + 1);
        const auto blockRight = gamedata.mapGame.getBlock(x + 1, y);
        const auto blockLeft = gamedata.mapGame.getBlock(x - 1, y);

        const bool hasVertical = blockDown && blockUp;
        const bool hasHorizontal = blockLeft && blockRight;

        // Middle trunc without leaves
        int tiles = 0;

        // Base trunc
        if (hasVertical && blockDown->type != Block::air && blockDown->type != Block::woodLog) {

          // Base trunc without wood up
          if (blockUp->type != Block::woodLog)
            tiles = 7;

          // Base trunc
          else
            tiles = 4;

          // Middle trunc
        } else if (hasVertical && hasHorizontal && blockUp->type == Block::woodLog &&
                   blockDown->type == Block::woodLog) {

          // Middle trunc leaves only right
          if (blockRight->type == Block::leaves && blockLeft->type != Block::leaves)
            tiles = 2;

          // Middle trunc leaves only left
          else if (blockRight->type != Block::leaves && blockLeft->type == Block::leaves)
            tiles = 3;

          // Middle trunc leaves two sides
          else if (blockRight->type == Block::leaves && blockLeft->type == Block::leaves)
            tiles = 1;

          // Top Trunc
        } else if (hasVertical && hasHorizontal && blockDown->type == Block::woodLog &&
                   blockUp->type != Block::woodLog) {

          // Top trunc with leaves
          if (blockLeft->type == Block::leaves && blockRight->type == Block::leaves &&
              blockUp->type == Block::leaves)
            tiles = 5;

          // Top trunc without leaves
          else
            tiles = 6;
        }

        DrawTexturePro(assetManager.treeTextures, getTextureAtlas(tiles, 0, 32, 32),
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
  handleKeyboardBlock();
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
