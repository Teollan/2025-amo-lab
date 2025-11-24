#include <stdio.h>
#include "vector.h"
#include "matrix.h"
#include "gauss.h"

int main() {
  // double data[] = {
  //   14, 19, 15,  4, 180,
  //   17, 33,  5, 10, 208,
  //   11,  6, 28, 10, 230,
  //    6, 19,  3, 13, 149,
  // };

  double data[] = {
    2, 1, 1,
    1, 3, 2,
    1, 0, 0
  };

  Matrix A = createMatrix(3, 3, data);

  // Compute inverse
  Matrix invA = getInverseMatrix(A);

  // Multiply A * invA
  // Matrix product = multiplyMatrices(A, invA);

  // Print original matrix
  printf("Original Matrix A:\n%s\n", matrixToString(A));

  // Print inverse
  printf("Inverse Matrix invA:\n%s\n", matrixToString(invA));

  // Print product
  // printf("Product A * invA:\n%s\n", matrixToString(product));

  // Matrix matrix = createMatrix(4, 5, data);
  // printf("Initial matrix:\n%s\n", matrixToString(matrix));

  // Vector solution = solveWithGaussianElimination(matrix);
  // printf("Solution vector:\n%s\n", vectorToString(solution));

  destroyMatrix(A);

  return 0;
}