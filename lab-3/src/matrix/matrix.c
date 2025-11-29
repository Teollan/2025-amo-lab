// matrix.c
#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../vector/vector.h"

Matrix createMatrix(int rows, int cols, double *data) {
  Matrix matrix;
  matrix.rows = rows;
  matrix.cols = cols;
  matrix.data = (double *) malloc(rows * cols * sizeof(double));

  if (data == NULL) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        matrix.data[i * cols + j] = 0.0;
      }
    }

    return matrix;
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix.data[i * cols + j] = data[i * cols + j];
    }
  }

  return matrix;
}

Matrix cloneMatrix(Matrix matrix) {
  return createMatrix(matrix.rows, matrix.cols, matrix.data);
}

void destroyMatrix(Matrix matrix) {
  free(matrix.data);
}

double getMatrixElement(Matrix matrix, int i, int j) {
  return matrix.data[i * matrix.cols + j];
}

void setMatrixElement(Matrix matrix, int i, int j, double value) {
  matrix.data[i * matrix.cols + j] = value;
}

Vector getMatrixColumn(Matrix matrix, int j) {
  Vector column = createVector(matrix.rows, NULL);

  for (int i = 0; i < matrix.rows; i++) {
    double value = getMatrixElement(matrix, i, j);

    setVectorElement(column, i, value);
  }

  return column;
}

Matrix getMatrixSubmatrix(Matrix matrix, int i_start, int j_start, int rows, int cols) {
  Matrix submatrix = createMatrix(rows, cols, NULL);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double value = getMatrixElement(matrix, i_start + i, j_start + j);

      setMatrixElement(submatrix, i, j, value);
    }
  }

  return submatrix;
}

void performRowScaling(Matrix matrix, int i, double scalar) {
  for (int j = 0; j < matrix.cols; j++) {
    double value = getMatrixElement(matrix, i, j);

    setMatrixElement(matrix, i, j, value * scalar);
  }
}

void performRowTransformation(Matrix matrix, int i, int k, double scalar) {
  for (int j = 0; j < matrix.cols; j++) {
    double a_ij = getMatrixElement(matrix, i, j);
    double a_kj = getMatrixElement(matrix, k, j);

    setMatrixElement(matrix, i, j, a_ij + scalar * a_kj);
  }
}

char *matrixToString(Matrix matrix) {
  char *buffer = (char *) malloc(matrix.rows * 256);
  buffer[0] = '\0';

  char rowBuffer[256];

  for (int i = 0; i < matrix.rows; i++) {
    int offset = 0;

    offset += sprintf(rowBuffer + offset, "[");

    for (int j = 0; j < matrix.cols; j++) {
      float a_ij = getMatrixElement(matrix, i, j);

      offset += sprintf(rowBuffer + offset, "% 9.4f", a_ij);

      if (j < matrix.cols - 1) {
        offset += sprintf(rowBuffer + offset, ", ");
      }
    }

    offset += sprintf(rowBuffer + offset, "]\n");
    strcat(buffer, rowBuffer);
  }

  return buffer;
}
