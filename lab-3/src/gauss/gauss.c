// gauss.c
#include "gauss.h"

#include <stdio.h>
#include <stdlib.h>

#include "../matrix/matrix.h"
#include "../vector/vector.h"

Vector solveWithGaussianElimination(Matrix A_B) {
  Matrix U = performForwardSubstitution(A_B);

  Vector X = performBackSubstitution(U);

  destroyMatrix(U);

  return X;
}

Matrix performForwardSubstitution(Matrix augmentedMatrix) {
  Matrix A_B = cloneMatrix(augmentedMatrix);

  for (int i = 0; i < A_B.rows; i++) {
    double a_ii = getMatrixElement(A_B, i, i);

    Vector row_i = getMatrixRow(A_B, i);
    Vector scaled_row_i = multiplyVectorByScalar(row_i, 1.0 / a_ii);

    setMatrixRow(A_B, i, scaled_row_i);

    for (int k = i + 1; k < A_B.rows; k++) {
      double a_ki = getMatrixElement(A_B, k, i);

      Vector row_k = getMatrixRow(A_B, k);
      Vector scaled_row_k = multiplyVectorByScalar(scaled_row_i, a_ki);
      Vector subtracted_row_k = subtractVectors(row_k, scaled_row_k);

      setMatrixRow(A_B, k, subtracted_row_k);

      destroyVector(subtracted_row_k);
      destroyVector(row_k);
      destroyVector(scaled_row_k);
    }

    destroyVector(row_i);
    destroyVector(scaled_row_i);
  }

  return A_B;
}

Vector performBackSubstitution(Matrix matrix) {
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