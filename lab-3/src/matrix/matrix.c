// matrix.c
#include "matrix.h"

#include <stdlib.h>
#include <string.h>

#include "../vector/vector.h"

Matrix createMatrix(int rows, int cols, double* data) {
  Matrix matrix;
  matrix.rows = rows;
  matrix.cols = cols;
  matrix.data = (Vector*)malloc(rows * sizeof(Vector));

  if (data == NULL) {
    for (int i = 0; i < rows; i++) {
      matrix.data[i] = createVector(cols, NULL);
    }

    return matrix;
  }

  for (int i = 0; i < rows; i++) {
    matrix.data[i] = createVector(cols, &data[i * cols]);
  }

  return matrix;
}

Matrix cloneMatrix(Matrix matrix) {
  Matrix newMatrix = createMatrix(matrix.rows, matrix.cols, NULL);

  for (int i = 0; i < matrix.rows; i++) {
    newMatrix.data[i] = cloneVector(matrix.data[i]);
  }

  return newMatrix;
}

void destroyMatrix(Matrix matrix) {
  for (int i = 0; i < matrix.rows; i++) {
    destroyVector(matrix.data[i]);
  }

  free(matrix.data);
}

double getMatrixElement(Matrix matrix, int rowIndex, int colIndex) {
  Vector row = matrix.data[rowIndex];

  double element = getVectorElement(row, colIndex);

  return element;
}

void setMatrixElement(Matrix matrix, int rowIndex, int colIndex, double value) {
  Vector row = matrix.data[rowIndex];

  setVectorElement(row, colIndex, value);
}

Vector getMatrixRow(Matrix matrix, int rowIndex) {
  Vector row = matrix.data[rowIndex];

  return cloneVector(row);
}

void setMatrixRow(Matrix matrix, int rowIndex, Vector rowData) {
  for (int j = 0; j < matrix.cols; j++) {
    setMatrixElement(matrix, rowIndex, j, getVectorElement(rowData, j));
  }
}

char* matrixToString(Matrix matrix) {
  int bufferSize = matrix.rows * matrix.cols * 32;
  char* buffer = (char*)malloc(bufferSize * sizeof(char));
  buffer[0] = '\0';

  for (int i = 0; i < matrix.rows; i++) {
    char* rowString = vectorToString(matrix.data[i]);
    strcat(buffer, rowString);
    strcat(buffer, "\n");
    free(rowString);
  }

  return buffer;
}