#pragma once

#include <raylib.h>

struct AssetsManager {
  Texture2D dirt = {};
  Texture2D blockTextures = {};

  void loadAll();
};
