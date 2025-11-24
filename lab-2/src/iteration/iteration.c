// iteration.c
#include "iteration.h"

#include <math.h>
#include "f.h"

double approximateRootIterations(double x) {
  return x - (LAMBDA * f(x));
}

int hasConvergedIterations(double previousApproximation, double currentApproximation, double epsilon) {
  double error = fabs(currentApproximation - previousApproximation);
  double threshold = ((1 - Q) / Q) * epsilon;

  return error <= threshold;
}

IterationMethodResult performIterationMethod(double initialGuess, double epsilon) {
  int iterationCount = 0;
  double previousApproximation = 0.0;
  double currentApproximation = initialGuess;

  do {
    previousApproximation = currentApproximation;
    currentApproximation = approximateRootIterations(previousApproximation);
    iterationCount++;
  } while (!hasConvergedIterations(previousApproximation, currentApproximation, epsilon));

  IterationMethodResult result;
  result.iterations = iterationCount;
  result.approximation = currentApproximation;
  result.residual = fabs(currentApproximation - approximateRootIterations(currentApproximation));

  return result;
}