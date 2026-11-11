#pragma once

#include <raylib.h>

struct AssetsManager {
  Texture2D blockTextures = {};
  Texture2D treeTextures = {};
  Texture2D frame = {};

  void loadAll();
};
