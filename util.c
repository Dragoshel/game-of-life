#include <time.h>
#include <stdlib.h>

int **clone(int h, int w, int **matrix) {
  int **matrix_clone = (int **)malloc(sizeof(int *) * (h + 2));

  for (int i = 0; i < h; i++) {
    int *row = (int *)malloc(sizeof(int) * (w + 2));

    for (int j = 0; j < w; j++) {
      row[j] = matrix[i][j];
    }

    matrix_clone[i] = row;
  }

  return matrix_clone;
}

void swap(int h, int w, int **matrix_a, int **matrix_b) {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      int c = matrix_a[i][j];
      matrix_a[i][j] = matrix_b[i][j];
      matrix_b[i][j] = c;
    }
  }
}

int **rng(int h, int w) {
  srand(time(NULL));

  int **matrix = (int **)malloc(sizeof(int *) * (h + 2));

  for (int i = 0; i < h; i++) {
    int *row = (int *)malloc(sizeof(int) * (w + 2));

    for (int j = 0; j < w; j++) {
      row[j] = rand() % 10 % 2;
    }

    matrix[i] = row;
  }

  return matrix;
}