#include <raylib.h>
#include <stdio.h>

#include "util.c"

#define WINDOW_HEIGHT 1000
#define WINDOW_WIDTH 800

#define BOARD_HEIGHT (WINDOW_HEIGHT - 100)
#define BOARD_WIDTH (WINDOW_WIDTH - 100)

#define RECT_SIZE 7

int grid[BOARD_HEIGHT][BOARD_WIDTH] = {0};

Vector2 top = {(float)(WINDOW_HEIGHT - BOARD_HEIGHT) / 2,
               (float)(WINDOW_WIDTH - BOARD_WIDTH) / 2};

Vector2 size = {RECT_SIZE, RECT_SIZE};

int rules(int i, int j, int h, int w, int **grid) {
  int live_neighbors = 0;

  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
      if (dx == 0 && dy == 0) {
        continue;
      }

      int neighborX = i + dx;
      int neighborY = j + dy;

      if (neighborX >= 0 && neighborX < h && neighborY >= 0 && neighborY < w) {
        live_neighbors += grid[neighborX][neighborY];
      }
    }
  }

  return live_neighbors;
}

void transition(int h, int w, int **grid, int **next_grid) {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      int live_neighbors = rules(i, j, h, w, grid);

      if (grid[i][j] == 1) {
        if (live_neighbors < 2 || live_neighbors > 3) {
          next_grid[i][j] = 0;
        } else {
          next_grid[i][j] = 1;
        }
      } else {
        if (live_neighbors == 3) {
          next_grid[i][j] = 1;
        } else {
          next_grid[i][j] = 0;
        }
      }
    }
  }

  swap(h, w, grid, next_grid);
}

void draw(int h, int w, int **grid) {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      Vector2 pos = {top.x + i * RECT_SIZE, top.y + j * RECT_SIZE};

      if (grid[i][j]) {
        DrawRectangleV(pos, size, BLACK);
      } else {
        DrawRectangleLines(pos.x, pos.y, size.x, size.y, LIGHTGRAY);
      }
    }
  }
}

double speed_input(double current_speed) {
  if (IsKeyPressed(KEY_RIGHT)) {
    current_speed += 0.01;
  } else if (IsKeyPressed(KEY_LEFT) && current_speed > 0) {
    current_speed -= 0.01;
  }

  return current_speed;
}

int main(void) {
  double speed = 0.05;

  int h = BOARD_HEIGHT / RECT_SIZE;
  int w = BOARD_WIDTH / RECT_SIZE;

  int **grid = rng(h, w);
  int **next_grid = clone(h, w, grid);

  InitWindow(WINDOW_HEIGHT, WINDOW_WIDTH, "Game of Live - Raylib");

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(RAYWHITE);

    draw(h, w, grid);

    transition(h, w, grid, next_grid);

    speed = speed_input(speed);

	char text_speed[100];
    sprintf(text_speed, "%f", speed);

	DrawFPS(10, 10);

	DrawText(text_speed, 820, 10, 24, BLACK);

    WaitTime(speed);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}