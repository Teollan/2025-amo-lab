#include <stdio.h>
#include "ch.c"
#include "log.c"

const double RANGE_START = -0.8;
const double RANGE_END = 1.9;
const double RANGE_MIDDLE = (RANGE_END + RANGE_START) / 2;
const double RANGE_STEP = (RANGE_END - RANGE_START) / 10;

const int N = 6;

void run_task_1() {
    FILE *logfile = fopen("./task1.log.csv", "w");

    char epsilon_str[50];
    char terms_str[50];
    char absolute_error_str[50];
    char remainder_term_str[50];

    log_columns(logfile, 4, "Epsilon", "Terms", "Absolute Error", "Remainder Term");

    for (int power = -2; power >= -14; power -= 3) {
        double epsilon = pow(10, power);
        ChResult result = ch_with_precision(RANGE_MIDDLE, epsilon);

        sprintf(epsilon_str, "10^%d", power);
        sprintf(terms_str, "%d", result.terms);
        sprintf(absolute_error_str, "%.16f", result.absolute_error);
        sprintf(remainder_term_str, "%.16f", result.remainder_term);
        log_columns(logfile, 4, epsilon_str, terms_str, absolute_error_str, remainder_term_str);

        printf("Epsilon: 10^%d\n", power);
        printf("N: %d\n", result.terms);
        printf("Precise value: %.16f\n", result.precise);
        printf("Approximate value: %.16f\n", result.approximate);
        printf("Absolute error: %.16f\n", result.absolute_error);
        printf("Remainder term: %.16f\n", result.remainder_term);
        printf("\n");
    }
}

void run_task_2() { 
    FILE *logfile = fopen("./task2.log.csv", "w");

    char xi_str[50];
    char absolute_error_str[50];
    char remainder_term_str[50];

    log_columns(logfile, 3, "X", "Absolute Error", "Remainder Term");

    for (int i = 0; i <= 10; i++) {
        double x = RANGE_START + (RANGE_STEP * i);
        ChResult result = ch_with_terms(x, N);

        sprintf(xi_str, "%.10f", x);
        sprintf(absolute_error_str, "%.16f", result.absolute_error);
        sprintf(remainder_term_str, "%.16f", result.remainder_term);
        log_columns(logfile, 3, xi_str, absolute_error_str, remainder_term_str);

        printf("X: %f\n", x);
        printf("N: %d\n", result.terms);
        printf("Precise value: %.16f\n", result.precise);
        printf("Approximate value: %.16f\n", result.approximate);
        printf("Absolute error: %.16f\n", result.absolute_error);
        printf("Remainder term: %.16f\n", result.remainder_term);
        printf("\n");
    }
}

int main() {
    run_task_1();
    run_task_2();

    return 0;
}