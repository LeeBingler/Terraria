#include <assetsManager.hpp>
#include <raylib.h>

void AssetsManager::loadAll() {
  blockTextures = LoadTexture(RESOURCES_PATH "textures.png");
  frame = LoadTexture(RESOURCES_PATH "frame.png");
}
