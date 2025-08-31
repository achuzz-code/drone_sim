#include "components/graph.hpp"
#include "components/objectBody.hpp"
#include "helperFn/cameraControl.hpp"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <cmath>
#include <ctime>
#include <string>
Matrix GetCustomRotationMatrix() {
  return (Matrix){-0.3333333f, 0.9333333f, -0.1333333f, 0.0f,
                  0.6666667f,  0.3333333f, 0.6666667f,  0.0f,
                  0.6666667f,  0.1333333f, -0.7333333f, 0.0f,
                  0.0f,        0.0f,       0.0f,        1.0f};
}
int main(void) {
  // Initialization
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  const int screenWidth = GetScreenWidth();
  const int screenHeight = GetScreenHeight();
  InitWindow(screenWidth, screenHeight, "RAYLIB Cuboid Example");
  Grapher gx = Grapher(10, 10, 200, 80, 10000, 1.0);
  Grapher gy = Grapher(210, 10, 200, 100, 10000, 1.0);
  // Define the camera
  Camera camera = {0};
  camera.position = {60.0f, 10.0f, 0.0f}; // Camera position
  // camera.target = {0.0f, 0.0f, 0.0f};      // Camera looking at point
  camera.up = {0.0f, 1.0f, 0.0f};         // Camera up vector (Y-axis)
  camera.fovy = 45.0f;                    // Camera field of view
  camera.projection = CAMERA_PERSPECTIVE; // Camera mode type

  SetTargetFPS(60);

  // Main game loop
  while (!WindowShouldClose()) {
    // UpdateCamera
    moveCamera(camera);
    // UpdateCamera(&camera, CAMERA_FIRST_PERSON);
    //  Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);
    rlPushMatrix();
    rlMultMatrixf(MatrixToFloat(GetCustomRotationMatrix()));

    // Draw the cuboid
    DrawCubeV({0.0f, 0.0f, 0.0f}, {2.0f, 3.0f, 4.0f}, BLUE);
    DrawCubeWires({0.0f, 0.0f, 0.0f}, 2.0f, 3.0f, 4.0f, RED);

    rlPopMatrix();
    DrawGrid(200, 6);
    EndMode3D();
    gx.render(GetMousePosition().y * 100.0f - 50000.0f);
    gy.render(GetMousePosition().x * 100.0f - 50000.0f);
    DrawText(std::to_string(GetMousePosition().y * 100.0f - 50000.0f).c_str(),
             200, 300, 30, RED);
    DrawFPS(10, 10);

    EndDrawing();
  }

  // De-Initialization
  CloseWindow();

  return 0;
}
