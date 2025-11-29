// gauss.c
#include "gauss.h"

#include <stdio.h>
#include <stdlib.h>

#include "../matrix/matrix.h"
#include "../vector/vector.h"

Vector solveWithGaussianElimination(Matrix A_B) {
  performForwardElimination(A_B);

  return performBackwardSubstitution(A_B);
}

void performForwardElimination(Matrix A_B) {
  for (int i = 0; i < A_B.rows; i++) {
    double a_ii = getMatrixElement(A_B, i, i);

    performRowScaling(A_B, i, 1.0 / a_ii);

    for (int k = i + 1; k < A_B.rows; k++) {
      double a_ki = getMatrixElement(A_B, k, i);

      performRowTransformation(A_B, k, i, -1.0 * a_ki);
    }
  }
}

Vector performBackwardSubstitution(Matrix matrix) {
  Vector X = createVector(matrix.rows, NULL);

  for (int i = matrix.rows - 1; i >= 0; i--) {
    double b_i = getMatrixElement(matrix, i, matrix.cols - 1);

    double sum = 0.0;

    for (int j = i + 1; j < matrix.cols - 1; j++) {
      double a_ij = getMatrixElement(matrix, i, j);
      double x_j = getVectorElement(X, j);

      sum += a_ij * x_j;
    }

    double x_i = b_i - sum;

    setVectorElement(X, i, x_i);
  }

  return X;
}