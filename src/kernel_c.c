#include "dot_product.h"

// Multiplies 2 doubles together, then adds to the sum
void dot_product_c(const int n, const double *A, const double *B, double *sdot) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += A[i] * B[i];
    }
    *sdot = sum;
}
