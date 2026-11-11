#include <assetsManager.hpp>
#include <raylib.h>

void AssetsManager::loadAll() {
  blockTextures = LoadTexture(RESOURCES_PATH "texturesWithBackgroundVersion.png");
  treeTextures = LoadTexture(RESOURCES_PATH "treetextures.png");

  frame = LoadTexture(RESOURCES_PATH "frame.png");
}
