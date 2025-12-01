// integral.c
#include "integral.h"

#include <math.h>
#include <stdio.h>

double calculateIntegralNewtonLeibniz(double a, double b, double (*F)(double x)) {
  return F(b) - F(a);
}

int calculateTrapezoidalStepsForPrecision(double a, double b, double eps, double (*f_dd)(double x)) {
  double M_2 = fmax(fabs(f_dd(a)), fabs(f_dd(b)));

  double h = sqrt((12.0 * eps) / ((b - a) * M_2));

  int n = ceil((b - a) / h);

  return n;
}

IntegralResult calculateIntegralTrapezoidal(double a, double b, int n, double (*f)(double x)) {
  double h = (b - a) / n;
  double x_0 = a;
  double x_1 = a + h;
  double sum = 0.0;

  for (int i = 0; i < n; i++) {
    sum += (f(x_0) + f(x_1)) * h / 2.0;

    x_0 += h;
    x_1 += h;
  }

  IntegralResult result;
  result.I = sum;
  result.h = h;

  return result;
}

IntegralResult calculateIntegralTrapezoidalRunge(double a, double b, double eps, double (*f)(double x)) {
  double r = 2.0;
  int n = round(1.0 / pow(eps, 1.0 / r));

  double I_n = calculateIntegralTrapezoidal(a, b, n, f).I;
  double I_2n = calculateIntegralTrapezoidal(a, b, 2 * n, f).I;
  double R_n = fabs(I_2n - I_n) / (pow(2.0, r) - 1.0);

  while (R_n > eps) {
    n *= 2;

    I_n = I_2n;

    I_2n = calculateIntegralTrapezoidal(a, b, 2 * n, f).I;

    R_n = fabs(I_2n - I_n) / (pow(2.0, r) - 1.0);
  }

  IntegralResult result;
  result.I = I_2n;
  result.h = (b - a) / n;

  return result;
}