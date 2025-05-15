

#include <simple2d.h>
#include <math.h>

// A simple struct for one sloped platform
typedef struct {
  float x1, y1, x2, y2;
} Platform;

// Three platforms
Platform platforms[3];

// Draw one sloped platform as a thick quad
void draw_platform(Platform p) {
  float thickness = 6.0f;
  float dx = p.x2 - p.x1, dy = p.y2 - p.y1;
  float len = sqrtf(dx*dx + dy*dy);
  float ux = dx / len, uy = dy / len;
  float px = -uy * thickness/2, py = ux * thickness/2;

  S2D_DrawQuad(
    p.x1 + px, p.y1 + py, 0.6, 0.6, 1, 1,
    p.x2 + px, p.y2 + py, 0.6, 0.6, 1, 1,
    p.x2 - px, p.y2 - py, 0.6, 0.6, 1, 1,
    p.x1 - px, p.y1 - py, 0.6, 0.6, 1, 1
  );
}

void update() { }

void render() {
  // Full-screen dark background
  S2D_DrawQuad(
    0,   0,   0.1, 0.1, 0.1, 1,
    800, 0,   0.1, 0.1, 0.1, 1,
    800, 600, 0.1, 0.1, 0.1, 1,
    0,   600, 0.1, 0.1, 0.1, 1
  );

  // Small yellow rectangle at top-left of first (top) platform
  {
    float mx = platforms[0].x1;
    float my = platforms[0].y1;
    float sz = 20;
    S2D_DrawQuad(
      mx,       my - sz, 1,1,0,1,
      mx + sz,  my - sz, 1,1,0,1,
      mx + sz,  my,      1,1,0,1,
      mx,       my,      1,1,0,1
    );
  }

  // Larger red rectangle at top-left of last (bottom) platform
  {
    float mx = platforms[2].x1;
    float my = platforms[2].y1;
    float sz = 40;
    S2D_DrawQuad(
      mx,       my - sz, 1,0,0,1,
      mx + sz,  my - sz, 1,0,0,1,
      mx + sz,  my,      1,0,0,1,
      mx,       my,      1,0,0,1
    );
  }

  // Draw the three platforms
  for (int i = 0; i < 3; i++) {
    draw_platform(platforms[i]);
  }
}

int main() {
  platforms[0] = (Platform){  60, 560, 740, 540 };  // top
  platforms[1] = (Platform){  40, 430, 760, 410 };  // middle
  platforms[2] = (Platform){  60, 300, 740, 280 };  // bottom

  S2D_Window *window = S2D_CreateWindow(
    "Sloped Platforms with Monkeys", 800, 600,
    update, render,
    0
  );

  S2D_Show(window);
  return 0;
}