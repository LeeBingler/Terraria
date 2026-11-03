#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>

int main() {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 400, "Window");

  rlImGuiSetup(true);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    rlImGuiBegin();
    DrawText("Test", 190, 200, 20, RED);

    DrawRectangle(50, 50, 100, 100, {255, 0, 0, 127});
    DrawRectangle(75, 75, 100, 100, {0, 255, 0, 127});

    ImGui::Begin("test");
    ImGui::Text("Hello");
    ImGui::Button("Button");
    ImGui::End();

    rlImGuiEnd();

    EndDrawing();
  }

  rlImGuiShutdown();
  CloseWindow();

  return 0;
}
