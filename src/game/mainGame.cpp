#include <mainGame.hpp>

#include <raylib.h>

bool gameInit() { return true; }

bool gameUpdate() {
  DrawText("Test", 190, 200, 20, RED);

  DrawRectangle(50, 50, 100, 100, {255, 0, 0, 127});
  DrawRectangle(75, 75, 100, 100, {0, 255, 0, 127});
  return true;
}

bool gameClose() { return true; }
