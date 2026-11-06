#include "raylib.h"
#include <helpers.hpp>

Rectangle getTextureAtlas(int x, int y, int cellSizePixelX, int cellSizePixelY) {
  return Rectangle{(float)x * cellSizePixelX, (float)y * cellSizePixelY, (float)cellSizePixelX,
                   (float)cellSizePixelY};
}
