#include "raylib.h"
#include "raymath.h"
inline void DrawArrow3D(Vector3 value, Vector3 pos = Vector3{0, 0, 0},
                        float shaftRadius = 0.1, float headRadius = 0.5,
                        float headLength = 0.5, Color color = BLACK) {

  // Calculate the end point and total length of the arrow vector
  Vector3 end = Vector3Add(pos, value);
  float length = Vector3Length(value);

  // --- Fix 1: Handle zero-length vectors ---
  // If the arrow has no length, don't draw anything to prevent division by
  // zero.
  if (length < 0.0001f) {
    return;
  }
  DrawCapsule(pos, end, shaftRadius, 10, 10, color);
  DrawSphere(end, 0.2, color);
}
