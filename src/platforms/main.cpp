#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>

#include <mainGame.hpp>

void configRaylib() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 400, "Window");
  SetExitKey(KEY_NULL);
  SetTargetFPS(240);
}

void imGUIDisplay() {
  ImGui::Begin("test");

  ImGui::Text("Hello");
  ImGui::Button("Button");
  ImGui::End();
}

int main() {
#if PRODUCTION_BUILD == 1
  SetTraceLogLevel(LOG_NONE); // No log if production build
#endif

  configRaylib();

  rlImGuiSetup(true);

  if (!gameInit()) {
    return 1;
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    rlImGuiBegin();

    if (!gameUpdate()) {
      CloseWindow();
    }

    imGUIDisplay();

    rlImGuiEnd();

    EndDrawing();
  }

  CloseWindow();
  gameClose();
  rlImGuiShutdown();

  return 0;
}
