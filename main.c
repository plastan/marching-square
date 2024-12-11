#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define RADIUS 1
#define RESOLUTION 10
#define FONTSIZE 1
#define FONTOPACITY .3

// int ceil(float x) {
//   if (x > 0) {
//     return (int)x;
//   } else {
//     return (int)x - 1;
//   }
// }

void line(Vector2 a, Vector2 b) { DrawLine(a.x, a.y, b.x, b.y, WHITE); }

void action(int value, Vector2 a, Vector2 b, Vector2 c, Vector2 d) {

  switch (value) {
  case 1:

    line(a, d);
    break;

  case 2:
    line(d, c);
    break;
  case 3:

    line(a, c);
    break;
  case 4:

    line(b, c);
    break;
  case 5:
    line(a, d);
    line(b, c);
    break;
  case 6:

    line(b, d);
    break;
  case 7:

    line(a, b);
    break;
  case 8:

    line(a, b);
    break;
  case 9:

    line(b, d);
    break;
  case 10:

    line(a, b);
    line(d, c);
    break;
  case 11:

    line(b, c);
    break;

  case 12:

    line(a, c);
    break;
  case 13:

    line(d, c);
    break;
  case 14:

    line(a, d);
    break;

  default:

    break;
  }
}

int main(void) {
  const int screenWidth = 600;
  const int screenHeight = 600;

  const int res = RESOLUTION;

  int cols = 1 + screenWidth / res;
  int rows = 1 + screenHeight / res;

  int grid[rows][cols];
  InitWindow(screenWidth, screenHeight, "Marching square");

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      // grid[i][j] = (float)GetRandomValue(0, 10) / (float)GetRandomValue(1,
      // 10);
      grid[i][j] = GetRandomValue(0, 1);
      // grid[j][i] = (float)rand() / (float)(RAND_MAX / 1);
    }
  }

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {

    BeginDrawing();

    ClearBackground(BLACK);
    for (int i = 0; i < rows - 1; i++) {
      for (int j = 0; j < cols - 1; j++) {

        int decimal = grid[i][j] * pow(2, 3) + grid[i][j + 1] * pow(2, 2) +
                      grid[i + 1][j + 1] * pow(2, 1) +
                      grid[i + 1][j] * pow(2, 0);

        float half = (float)res * 0.5;
        Vector2 a = (Vector2){j * res, i * res + half};
        Vector2 b = (Vector2){(j)*res + half, i * res};
        Vector2 c = (Vector2){(j + 1) * res, i * res + half};
        Vector2 d = (Vector2){j * res + half, (i + 1) * res};
        printf("vector a : %f %f \n", a.x, a.y);
        printf("vector b : %f %f \n", b.x, b.y);
        printf("vector c : %f %f \n", c.x, c.y);
        printf("vector d : %f %f \n", d.x, d.y);
        action(decimal, a, b, c, d);

        printf("%d <=> %d %d %d %d \n", decimal, grid[i][j], grid[i][j + 1],
               grid[i + 1][j + 1], grid[i + 1][j]);

        DrawText(TextFormat("%d", decimal), j * res + half, i * res + half,
                 FONTSIZE, ColorAlpha(WHITE, FONTOPACITY));
      }
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        float alpha = grid[i][j];
        DrawCircle(j * res, i * res, RADIUS, ColorAlpha(RED, alpha));
        DrawRectangleLines(j * res, i * res, res, res, ColorAlpha(GRAY, .5));
      }
    }

    EndDrawing();
  }

  CloseWindow(); // Close window and OpenGL context

  return 0;
}
