// chords.c
#include "chords.h"

#include <math.h>
#include <stdio.h>

#include "../f/f.h"

double approximateRootChords(double x, double c) {
  double nominator = f(x) * (x - c);
  double denominator = f(x) - f(c);

  return x - (nominator / denominator);
}

int hasConvergedChords(double currentApproximation, double epsilon) {
  double error = fabs(f(currentApproximation)) / m1;
  double threshold = epsilon;

  return error <= threshold;
}

ChordsMethodResult performChordsMethod(double initialGuess, double fixedPoint,
                                       double epsilon) {
  int iterationCount = 0;
  double previousApproximation = 0.0;
  double currentApproximation = initialGuess;

  do {
    previousApproximation = currentApproximation;
    currentApproximation =
        approximateRootChords(previousApproximation, fixedPoint);
    iterationCount++;
  } while (!hasConvergedChords(currentApproximation, epsilon));

  ChordsMethodResult result;
  result.iterations = iterationCount;
  result.approximation = currentApproximation;
  result.residual =
      fabs(currentApproximation -
           approximateRootChords(currentApproximation, fixedPoint));

  return result;
}