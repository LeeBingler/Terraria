#pragma once

#include <raylib.h>

struct AssetsManager {
  Texture2D dirt = {};

  void loadAll();
};
