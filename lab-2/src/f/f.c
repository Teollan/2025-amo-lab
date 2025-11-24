// f.c
#include "f.h"

#include <math.h>

double f(double x) {
  double a = 15.0 * (x + 1.0);
  double b = sqrt(1.0 + cos(x / 3.0));
  double c = 1.1 * cos(x / 5.0);
  double d = 3.0;

  return (a * b) - c - d;
}

double A = -1.0;
double B = -0.5;

double m1 = 20.87;
double M1 = 21.26;

double LAMBDA = 0.047;
double Q = 0.018;
