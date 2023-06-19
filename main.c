#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <time.h>

#define HEIGHT 800
#define WIDTH 600

#define BOARD_HEIGHT 300
#define BOARD_WIDTH 300

#define RECT_SIZE 20

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
	int **grid = (int **)malloc(sizeof(int *) * height);

	srand(time(NULL));

	for (int i = 0; i < height; i++)
	{
		int *row = (int *)malloc(sizeof(int) * width);

		for (int j = 0; j < width; j++)
		{
			row[j] = rand() % 10 % 2;
		}

		grid[i] = row;
	}

	return grid;
}

int main(void)
{
	int grid_height = BOARD_HEIGHT / RECT_SIZE;
	int grid_width = BOARD_WIDTH / RECT_SIZE;
	int **grid = rand_grid(grid_height, grid_width);

    InitWindow(HEIGHT, WIDTH, "raylib [core] example - basic window");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);

			for (int i = 0; i < grid_height; i++)
			{
				for (int j = 0; j < grid_width; j++)
				{
					Vector2 pos =
					{
						top.x + i * RECT_SIZE,
						top.y + j * RECT_SIZE
					};

					if (grid[i][j])
					{
						DrawRectangleV(pos, size, BLACK);
					}
					else
					{
						DrawRectangleV(pos, size, RAYWHITE);
					}
				}
			}

        EndDrawing();
    }

    CloseWindow();

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		free(grid[i]);
	}

	free(grid);

    return 0;
}