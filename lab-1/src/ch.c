#include <math.h>

typedef struct {
    int terms;
    double precise;
    double approximate;
    double absolute_error;
    double remainder_term;
} ChResult;

double term(int n, double radians) {
    double result = 1.0;

    for (int k = 1; k < n; k++) {
        result *= (radians * radians) / ((2 * k) * (2 * k - 1));
    }

    return result;
}

double remainder_term(int n, double radians) {
    return (2.0/3.0) * term(n, radians);
}

ChResult ch_with_precision(double radians, double epsilon) {
    int n = 0;
    double approximate = 0.0;

    do {
        n++;
        approximate += term(n, radians);
    } while (remainder_term(n, radians) >= epsilon);

    double precise = cosh(radians);
    double absolute_error = fabs(precise - approximate);
    double remainder_term_value = remainder_term(n, radians);    

    return (ChResult){n, precise, approximate, absolute_error, remainder_term_value};
}

ChResult ch_with_terms(double radians, int N) {
    int n = 0;
    double approximate = 0.0;

    do {
        n++;
        approximate += term(n, radians);
    } while (n < N);

    double precise = cosh(radians);
    double absolute_error = fabs(precise - approximate);
    double remainder_term_value = remainder_term(n, radians);    

    return (ChResult){n, precise, approximate, absolute_error, remainder_term_value};
}