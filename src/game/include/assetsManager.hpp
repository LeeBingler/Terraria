#pragma once

#include <raylib.h>

struct AssetsManager {
  Texture2D dirt = {};
  Texture2D blockTextures = {};
  Texture2D frame = {};

  void loadAll();
};
