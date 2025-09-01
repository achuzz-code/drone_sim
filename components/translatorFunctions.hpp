#include "raylib.h"
#include <LinearMath/btMatrix3x3.h>
inline Matrix BtToRaylib(const btMatrix3x3 &btRot) {
  Matrix mat = {0};

  // Bullet stores row-major; Raylib uses column-major
  mat.m0 = btRot[0][0];
  mat.m4 = btRot[0][1];
  mat.m8 = btRot[0][2];
  mat.m12 = 0.0f;
  mat.m1 = btRot[1][0];
  mat.m5 = btRot[1][1];
  mat.m9 = btRot[1][2];
  mat.m13 = 0.0f;
  mat.m2 = btRot[2][0];
  mat.m6 = btRot[2][1];
  mat.m10 = btRot[2][2];
  mat.m14 = 0.0f;
  mat.m3 = 0.0f;
  mat.m7 = 0.0f;
  mat.m11 = 0.0f;
  mat.m15 = 1.0f;

  return mat;
}
