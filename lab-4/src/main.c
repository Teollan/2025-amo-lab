// main.c
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "integral/integral.h"
#include "log/log.h"

const double A = 1.0;
const double B = 15.0;

const double MIN_EPS_POW = -2.0;
const double MAX_EPS_POW = -8.0;
const double EPS_POW_STEP = 1.0;

double F(double x) {
  return 10.0 * (x * log(x) - x);
}

double f(double x) {
  return 10.0 * log(x);
}

double f_d(double x) {
  return 10.0 / x;
}

double f_dd(double x) {
  return -10.0 / (x * x);
}

void calculateIntegralAnalytical() {
  FILE *file = fopen("../out/1.csv", "w");

  if (file == NULL) {
    fprintf(stderr, "Error: Could not open ../out/1.csv for writing\n");
    return;
  }

  double I_precise = calculateIntegralNewtonLeibniz(A, B, F);

  writeTableRowToConsole(4, "Epsilon", "Step", "Exact Value", "Obtained Error");
  writeTableRowToFile(file, 4, "Epsilon", "Step", "Exact Value", "Obtained Error");

  for (int eps_pow = MIN_EPS_POW; eps_pow >= MAX_EPS_POW; eps_pow -= EPS_POW_STEP) {
    double eps = pow(10, eps_pow);

    int n = calculateTrapezoidalStepsForPrecision(A, B, eps, f_dd);

    IntegralResult result = calculateIntegralTrapezoidal(A, B, n, f);
    double I = result.I;
    double h = result.h;

    char *eps_str = exponentToString(10, eps_pow);
    char *h_str = doubleToString(h, "%.15f");
    char *I_precise_str = doubleToString(I_precise, "%.15f");
    char *error_str = doubleToString(fabs(I_precise - I), "%.15f");

    writeTableRowToConsole(4, eps_str, h_str, I_precise_str, error_str);
    writeTableRowToFile(file, 4, eps_str, h_str, I_precise_str, error_str);

    free(eps_str);
    free(h_str);
    free(I_precise_str);
    free(error_str);
  }

  fclose(file);
}

void calculateIntegralRunge() {
  FILE *file = fopen("../out/2.csv", "w");

  if (file == NULL) {
    fprintf(stderr, "Error: Could not open ../out/2.csv for writing\n");
    return;
  }

  double I_precise = calculateIntegralNewtonLeibniz(A, B, F);

  writeTableRowToConsole(3, "Epsilon", "Step", "Obtained Error");
  writeTableRowToFile(file, 3, "Epsilon", "Step", "Obtained Error");

  for (int eps_pow = MIN_EPS_POW; eps_pow >= MAX_EPS_POW; eps_pow -= EPS_POW_STEP) {
    double eps = pow(10, eps_pow);

    IntegralResult result = calculateIntegralTrapezoidalRunge(A, B, eps, f);
    double I = result.I;
    double h = result.h;

    char *eps_str = exponentToString(10, eps_pow);
    char *h_str = doubleToString(h, "%.15f");
    char *error_str = doubleToString(fabs(I_precise - I), "%.15f");

    writeTableRowToConsole(3, eps_str, h_str, error_str);
    writeTableRowToFile(file, 3, eps_str, h_str, error_str);

    free(eps_str);
    free(h_str);
    free(error_str);
  }

  fclose(file);
}

int main() {
  printf("\n");

  calculateIntegralAnalytical();

  printf("\n");

  calculateIntegralRunge();

  printf("\n");

  return 0;
}