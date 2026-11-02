#include <raylib.h>

int main() {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 400, "Window");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Test", 190, 200, 20, RED);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
