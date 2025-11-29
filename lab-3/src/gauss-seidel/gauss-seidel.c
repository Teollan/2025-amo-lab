// gauss-seidel.c
#include "gauss-seidel.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../matrix/matrix.h"
#include "../vector/vector.h"

Vector solveWithGaussSeidel(Matrix A, Vector B, double eps) {
  Vector X = cloneVector(B);
  Vector X_old = cloneVector(B);

  do {
    destroyVector(X_old);
    X_old = cloneVector(X);

    for (int i = 0; i < A.rows; i++) {
      double a_ii = getMatrixElement(A, i, i);

      double b_i = getVectorElement(B, i);

      double sum = 0.0;

      for (int j = 0; j < A.cols; j++) {
        if (j == i) {
          continue;
        }

        double a_ij = getMatrixElement(A, i, j);
        double x_j = getVectorElement(X, j);

        sum += a_ij * x_j;
      }

      double x_i = (b_i - sum) / a_ii;

      setVectorElement(X, i, x_i);
    }
  } while (!hasGaussSeidelConverged(X, X_old, eps));

  destroyVector(X_old);

  return X;
}

int hasGaussSeidelConverged(Vector X, Vector X_old, double eps) {
  double maxError = 0.0;

  for (int i = 0; i < X.length; i++) {
    double x_i = getVectorElement(X, i);
    double x_i_old = getVectorElement(X_old, i);

    double error = fabs(x_i - x_i_old);

    if (error > maxError) {
      maxError = error;
    }
  }

  return maxError < eps;
}

int isMatrixDiagonallyDominant(Matrix A) {
  for (int i = 0; i < A.rows; i++) {
    double a_ii = fabs(getMatrixElement(A, i, i));
    double sum = 0.0;

    for (int j = 0; j < A.cols; j++) {
      if (i != j) {
        sum += fabs(getMatrixElement(A, i, j));
      }
    }

    if (a_ii < sum) {
      return 0;
    }
  }

  return 1;
}