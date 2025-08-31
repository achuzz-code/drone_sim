#include "raylib.h"
#include <algorithm>
#include <vector>
class Grapher {
private:
  std::vector<float> values;
  int sx, sy;
  float rangeY;
  int max;
  float scaleX, scaleY;
  float minY, yMaxExpected;
  int width, height;
  const char *domainLabel;
  const char *rangeLabel;

public:
  Grapher(int startX, int startY, int width, int height,
          float yMaxExpected = 1.0f, float scaleXInp = 1.0f) {
    sx = startX;
    sy = startY;
    this->width = width;
    this->height = height;
    max = (int)(width / scaleXInp);
    scaleX = scaleXInp;
    this->yMaxExpected = yMaxExpected;
    scaleY = height / yMaxExpected;
    domainLabel = "x";
    rangeLabel = "y";
  }
  void render(float inp) {

    DrawRectangle(sx - 5, sy - 5, width + 10, height + 10, RED);
    DrawRectangle(sx, sy, width, height, DARKBLUE);
    if (values.size() > max)
      values.erase(values.begin());
    values.push_back(-inp);
    if (values.size() < 1)
      return;
    auto [minIt, maxIt] = std::minmax_element(values.begin(), values.end());
    scaleY = height / std::max(std::max(-(*minIt), *maxIt), yMaxExpected);
    int semiHeight = height / 2;
    for (int i = 1; i < values.size(); i++) {
      DrawLine(
          sx + i * scaleX - 1, sy + (values[i - 1] * scaleY) * 0.5 + semiHeight,
          sx + i * scaleX, sy + (values[i] * scaleY) * 0.5 + semiHeight, GREEN);
    }
  }
  void renderStatic() {
    int semiHeight = height / 2;
    for (int i = 1; i < values.size(); i++) {
      DrawLine(
          sx + i * scaleX - 1, sy + (values[i - 1] * scaleY) * 0.5 + semiHeight,
          sx + i * scaleX, sy + (values[i] * scaleY) * 0.5 + semiHeight, GREEN);
    }
  }
  ~Grapher() {}
};
