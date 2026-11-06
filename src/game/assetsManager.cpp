#include <assetsManager.hpp>
#include <raylib.h>

void AssetsManager::loadAll() { blockTextures = LoadTexture(RESOURCES_PATH "textures.png"); }
