#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <time.h>

#define HEIGHT 1000
#define WIDTH 800

#define BOARD_HEIGHT 900
#define BOARD_WIDTH 700

#define RECT_SIZE 7

int grid[BOARD_HEIGHT][BOARD_WIDTH] = {0};

Vector2 top =
{
	(HEIGHT - BOARD_HEIGHT) / 2,
	(WIDTH - BOARD_WIDTH) / 2
};

Vector2 size =
{
	RECT_SIZE,
	RECT_SIZE
};

int **rand_grid(int height, int width)
{
	srand(time(NULL));

	int **grid = (int **)malloc(sizeof(int *) * (height + 2));

	for (int i = 0; i < height; i++)
	{
		int *row = (int *)malloc(sizeof(int) * (width + 2));

		for (int j = 0; j < width; j++)
		{
			row[j] = rand() % 10 % 2;
		}

		grid[i] = row;
	}

	return grid;
}

int rules(int i, int j, int height, int width, int **grid)
{
    int live_neighbors = 0;

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) {
                continue;
            }

            int neighborX = i + dx;
            int neighborY = j + dy;

            if (neighborX >= 0 && neighborX < height && neighborY >= 0 && neighborY < width) {
                live_neighbors += grid[neighborX][neighborY];
            }
        }
    }

	return live_neighbors;	
}

void transition(int height, int width, int **old_grid, int **new_grid)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int live_neighbors = rules(i, j, height, width, old_grid);

            if (old_grid[i][j] == 1) {
                if (live_neighbors < 2 || live_neighbors > 3) {
                    new_grid[i][j] = 0;
                } else {
                    new_grid[i][j] = 1;
                }
            } else {
                if (live_neighbors == 3) {
                    new_grid[i][j] = 1;
                } else {
                    new_grid[i][j] = 0;
                }
            }
		}
	}
}

void swap_grid(int height, int width, int **old_grid, int **new_grid, int**swap)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			swap[i][j] = old_grid[i][j];
			old_grid[i][j] = new_grid[i][j];
			new_grid[i][j] = swap[i][j];
		}
	}
}

int **copy(int height, int width, int **grid)
{
	int **new_grid = (int **)malloc(sizeof(int *) * (height + 2));

	for (int i = 0; i < height; i++)
	{
		int *row = (int *)malloc(sizeof(int) * (width + 2));

		for (int j = 0; j < width; j++)
		{
			row[j] = grid[i][j];
		}

		new_grid[i] = row;
	}

	return new_grid;
}

void draw(int height, int width, int **grid)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Vector2 pos =
			{
				top.x + i * RECT_SIZE,
				top.y + j * RECT_SIZE
			};

			if (grid[i][j]) {
				DrawRectangleV(pos, size, BLACK);
			} else {
				DrawRectangleLines(pos.x, pos.y, size.x, size.y, LIGHTGRAY);
			}
		}
	}
}

int main(void)
{
	int grid_height = BOARD_HEIGHT / RECT_SIZE;
	int grid_width = BOARD_WIDTH / RECT_SIZE;

	int **old_grid = rand_grid(grid_height, grid_width);
	int **new_grid = copy(grid_height, grid_width, old_grid);
	int **swap = copy(grid_height, grid_width, old_grid);

	double speed = 0.05;

    InitWindow(HEIGHT, WIDTH, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);

			draw(grid_height, grid_width, old_grid);

			transition(grid_height, grid_width, old_grid, new_grid);

			swap_grid(grid_height, grid_width, old_grid, new_grid, swap);

			if (IsKeyPressed(KEY_RIGHT)) {
				speed += 0.01;
			} else if (IsKeyPressed(KEY_LEFT) && speed > 0) {
				speed -= 0.01;
			}

			WaitTime(speed);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}