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

Matrix getInverseMatrix(Matrix matrix) {
  if (matrix.cols != matrix.rows) {
    Matrix emptyMatrix = {0, 0, NULL};

    return emptyMatrix;
  }

  int n = matrix.rows;

  // Create augmented matrix [A | I]
  Matrix aug = createMatrix(n, 2 * n, NULL);

  // Fill augmented matrix
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      setMatrixElement(aug, i, j, getMatrixElement(matrix, i, j));
    }

    for (int j = 0; j < n; j++) {
      setMatrixElement(aug, i, j + n, (i == j) ? 1.0 : 0.0);
    }
  }

  // Perform Gauss–Jordan elimination
  for (int i = 0; i < n; i++) {
    double pivot = getMatrixElement(aug, i, i);

    if (pivot == 0.0) {
      destroyMatrix(aug);

      return (Matrix){0, 0, NULL};
    }

    //
    // 1. Normalize pivot row
    //
    Vector row = getMatrixRow(aug, i);

    for (int j = 0; j < row.length; j++) {
      double v = getVectorElement(row, j);

      setVectorElement(row, j, v / pivot);
    }

    setMatrixRow(aug, i, row);

    destroyVector(row);

    //
    // 2. Eliminate column i in all other rows
    //
    for (int k = 0; k < n; k++) {
      if (k == i) {
        continue;
      }

      double factor = getMatrixElement(aug, k, i);
      if (factor == 0.0) {
        continue;
      }

      Vector targetRow = getMatrixRow(aug, k);
      Vector pivotRow = getMatrixRow(aug, i);

      for (int j = 0; j < targetRow.length; j++) {
        double newVal = getVectorElement(targetRow, j) -
                        factor * getVectorElement(pivotRow, j);

        setVectorElement(targetRow, j, newVal);
      }

      setMatrixRow(aug, k, targetRow);

      destroyVector(targetRow);
      destroyVector(pivotRow);
    }
  }

  //
  // Extract inverse from augmented matrix
  //
  Matrix inverse = createMatrix(n, n, NULL);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double v = getMatrixElement(aug, i, j + n);

      setMatrixElement(inverse, i, j, v);
    }
  }

  destroyMatrix(aug);
  return inverse;
}

Matrix multiplyMatrices(Matrix A, Matrix B) {
  if (A.cols != B.rows) {
    Matrix emptyMatrix = {0, 0, NULL};

    return emptyMatrix;
  }

  Matrix result = createMatrix(A.rows, B.cols, NULL);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.cols; j++) {
      double sum = 0.0;
      for (int k = 0; k < A.cols; k++) {
        double aElement = getMatrixElement(A, i, k);
        double bElement = getMatrixElement(B, k, j);
        sum += aElement * bElement;
      }
      setMatrixElement(result, i, j, sum);
    }
  }

  return result;
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