// main.c
#include <math.h>
#include <stdlib.h>

#include "chords/chords.h"
#include "f/f.h"
#include "iteration/iteration.h"
#include "log/log.h"

void testIterationMethod() {
  FILE* outputFile = fopen("../iteration_method_results.csv", "w");

  writeTableRowToConsole(1, "Iteration Method Results:");
  writeTableRowToConsole(3, "Epsilon", "Approximation", "Residual");

  writeTableRowToFile(outputFile, 3, "Epsilon", "Approximation", "Residual");

  double initialGuess = (A + B) / 2.0;

  for (int i = 0; i < 5; i++) {
    int power = (i * 3) + 2;
    double epsilon = pow(10.0, -power);

    IterationMethodResult result =
        performIterationMethod(initialGuess, epsilon);

    char* epsilonStr = exponentToString(10, -power);
    char* residualStr = doubleToString(result.residual, "%.10e");
    char* approximationStr = doubleToString(result.approximation, "%.10f");

    writeTableRowToConsole(3, epsilonStr, approximationStr, residualStr);

    writeTableRowToFile(outputFile, 3, epsilonStr, approximationStr,
                        residualStr);

    free(epsilonStr);
    free(residualStr);
    free(approximationStr);
  }
}

void testChordsMethod() {
  FILE* outputFile = fopen("../chords_method_results.csv", "w");

  writeTableRowToConsole(1, "Chords Method Results:");
  writeTableRowToConsole(3, "Epsilon", "Approximation", "Residual");

  writeTableRowToFile(outputFile, 3, "Epsilon", "Approximation", "Residual");

  double fixedPoint = B;
  double initialGuess = A;

  for (int i = 0; i < 5; i++) {
    int power = (i * 3) + 2;
    double epsilon = pow(10.0, -power);

    ChordsMethodResult result =
        performChordsMethod(initialGuess, fixedPoint, epsilon);

    char* epsilonStr = exponentToString(10, -power);
    char* residualStr = doubleToString(result.residual, "%.10e");
    char* approximationStr = doubleToString(result.approximation, "%.10f");

    writeTableRowToConsole(3, epsilonStr, approximationStr, residualStr);

    writeTableRowToFile(outputFile, 3, epsilonStr, approximationStr,
                        residualStr);

    free(epsilonStr);
    free(residualStr);
    free(approximationStr);
  }
}

void testComparison() {
  FILE* outputFile = fopen("../comparison.csv", "w");

  writeTableRowToConsole(1, "Iteration vs Chords:");
  writeTableRowToConsole(3, "Epsilon", "Iterations (I)", "Iterations (C)");

  writeTableRowToFile(outputFile, 3, "Epsilon", "Iterations (I)",
                      "Iterations (C)");

  double initialGuessIterations = (A + B) / 2.0;

  double fixedPointChords = B;
  double initialGuessChords = A;

  for (int i = 0; i < 5; i++) {
    int power = (i * 3) + 2;
    double epsilon = pow(10.0, -power);

    IterationMethodResult resultIterations =
        performIterationMethod(initialGuessIterations, epsilon);
    ChordsMethodResult resultChords =
        performChordsMethod(initialGuessChords, fixedPointChords, epsilon);

    char* epsilonStr = exponentToString(10, -power);
    char* iterationsIterations = intToString(resultIterations.iterations);
    char* chordsIterations = intToString(resultChords.iterations);

    writeTableRowToConsole(3, epsilonStr, iterationsIterations,
                           chordsIterations);

    writeTableRowToFile(outputFile, 3, epsilonStr, iterationsIterations,
                        chordsIterations);

    free(epsilonStr);
    free(iterationsIterations);
    free(chordsIterations);
  }
}

int main() {
  testIterationMethod();

  writeTableRowToConsole(1, "\n");

  testChordsMethod();

  writeTableRowToConsole(1, "\n");

  testComparison();

  writeTableRowToConsole(1, "\n");

  return 0;
}