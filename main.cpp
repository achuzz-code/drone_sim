#include "raylib.h"
int main(void) {
  // Initialization
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "RAYLIB Cuboid Example");

  // Define the camera
  Camera camera = {0};
  camera.position = {10.0f, 10.0f, 10.0f}; // Camera position
  camera.target = {0.0f, 0.0f, 0.0f};      // Camera looking at point
  camera.up = {0.0f, 1.0f, 0.0f};          // Camera up vector (Y-axis)
  camera.fovy = 45.0f;                     // Camera field of view
  camera.projection = CAMERA_PERSPECTIVE;  // Camera mode type

  SetTargetFPS(60);

  // Main game loop
  while (!WindowShouldClose()) {
    // Update
    UpdateCamera(&camera, CAMERA_ORBITAL);

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

    // Draw the cuboid
    DrawCubeV({0.0f, 0.0f, 0.0f}, {2.0f, 3.0f, 4.0f}, BLUE);

    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
  }

  // De-Initialization
  CloseWindow();

  return 0;
}
