
#include <raylib.h>
void moveCamera(Camera &camRef) {
  if (IsKeyDown(KEY_W)) {
    camRef.position.x -= 0.1;
  } else if (IsKeyDown(KEY_S)) {
    camRef.position.x += 0.1;
  } else if (IsKeyDown(KEY_A)) {
    camRef.position.z += 0.1;
  } else if (IsKeyDown(KEY_D)) {
    camRef.position.z -= 0.1;
  } else if (IsKeyDown(KEY_Q)) {
    camRef.position.y += 0.1;
  } else if (IsKeyDown(KEY_E)) {
    camRef.position.y -= 0.1;
  }
}
