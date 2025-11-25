// gauss.c
#include "gauss.h"

#include <stdio.h>
#include <stdlib.h>

#include "../matrix/matrix.h"
#include "../vector/vector.h"

Vector solveWithGaussianElimination(Matrix augmentedMatrix) {
  Matrix upperTriangularMatrix = performForwardSubstitution(augmentedMatrix);

  printf("Upper triangular matrix:\n%s\n",
         matrixToString(upperTriangularMatrix));

  Vector solution = performBackSubstitution(upperTriangularMatrix);

  destroyMatrix(upperTriangularMatrix);

  return solution;
}

Matrix performForwardSubstitution(Matrix matrix) {
  Matrix clone = cloneMatrix(matrix);

  for (int targetRowIndex = 0; targetRowIndex < clone.rows; targetRowIndex++) {
    double targetRowScaleFactor =
        getMatrixElement(clone, targetRowIndex, targetRowIndex);

    Vector targetRow = getMatrixRow(clone, targetRowIndex);
    Vector scaledRow =
        multiplyVectorByScalar(targetRow, 1.0 / targetRowScaleFactor);

    setMatrixRow(clone, targetRowIndex, scaledRow);

    for (int subsequentRowIndex = targetRowIndex + 1;
         subsequentRowIndex < clone.rows; subsequentRowIndex++) {
      double subsequentRowScaleFactor =
          getMatrixElement(clone, subsequentRowIndex, targetRowIndex);

      Vector subsequentRow = getMatrixRow(clone, subsequentRowIndex);
      Vector modifiedRow =
          multiplyVectorByScalar(scaledRow, -subsequentRowScaleFactor);

      setMatrixRow(clone, subsequentRowIndex,
                   addVectors(subsequentRow, modifiedRow));

      destroyVector(subsequentRow);
      destroyVector(modifiedRow);
    }

    destroyVector(targetRow);
    destroyVector(scaledRow);
  }

  return clone;
}

Vector performBackSubstitution(Matrix matrix) {
  Vector solution = createVector(matrix.rows, NULL);

  for (int rowIndex = matrix.rows - 1; rowIndex >= 0; rowIndex--) {
    double equationResult = getMatrixElement(matrix, rowIndex, matrix.cols - 1);

    printf("Calculating variable for row %d: initial result = %f\n", rowIndex,
           equationResult);

    for (int colIndex = rowIndex + 1; colIndex < matrix.cols - 1; colIndex++) {
      double coefficient = getMatrixElement(matrix, rowIndex, colIndex);
      double knownValue = getVectorElement(solution, colIndex);

      printf("  Subtracting %f * %f for column %d\n", coefficient, knownValue,
             colIndex);

      equationResult -= coefficient * knownValue;
    }

    printf("  Final result for variable at row %d: %f\n", rowIndex,
           equationResult);
    setVectorElement(solution, rowIndex, equationResult);
  }

  return solution;
}