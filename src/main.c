#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dot_product.h"

// Gets the current time in seconds accurately
static double now_seconds(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec * 1e-9;
}

int main(void) {
    printf("========================================================================================\n");
    printf(" Dot Product Kernel Benchmark\n");
    printf(" Runs per kernel per size: %d\n", 20);

    for (int t = 0; t < 3; t++) {
        const int sizes_exp[] = {20, 24, 28};
        const int  e = sizes_exp[t];
        const int n = 1 << e;

        double *A = malloc((size_t)n * sizeof(double));
        double *B = malloc((size_t)n * sizeof(double));
        if (A == NULL || B == NULL) {
            printf("2^%d: malloc failed, skipping this size\n\n", e);
            free(A);
            free(B);
            continue;
        }

        srand(67);
        for (int i = 0; i < n; i++) {
            A[i] = (double)rand() / (double)RAND_MAX;
            B[i] = (double)rand() / (double)RAND_MAX;
        }

        printf("========================================================================================\n");
        printf(" n = 2^%d = %d\n", e, n);
        printf("========================================================================================\n");
        printf(" Iter |        C sdot        |  C (ms)     |       ASM sdot       | ASM (ms)    | Check\n");
        printf("------|----------------------|-------------|----------------------|-------------|-------\n");

        double c_total = 0.0, asm_total = 0.0;
        int all_pass = 1;

        for (int r = 0; r < 20; r++) {
            double c_result = 0.0, asm_result = 0.0;

            // Time after - time before, converted to (ms)
            // Calls the C kernel in between
            const double c_t0 = now_seconds();
            dot_product_c(n, A, B, &c_result);
            const double c_t1 = now_seconds();
            const double c_ms = (c_t1 - c_t0) * 1000.0;
            // Calls the ASM kernel in between
            const double asm_t0 = now_seconds();
            dot_product_asm(n, A, B, &asm_result);
            const double asm_t1 = now_seconds();
            const double asm_ms = (asm_t1 - asm_t0) * 1000.0;

            // Checks if the kernel outputs are the same
            const int pass = (c_result == asm_result);
            if (!pass) all_pass = 0;

            printf(" %4d | %20.11f | %11.6f | %20.11f | %11.6f |  %s\n",
                   r + 1, c_result, c_ms, asm_result, asm_ms, pass ? "PASS" : "FAIL");

            c_total += c_ms;
            asm_total += asm_ms;
        }

        const double c_avg_ms = c_total / 20;
        const double asm_avg_ms = asm_total / 20;
        const double speedup = (asm_avg_ms > 0.0) ? (c_avg_ms / asm_avg_ms) : 0.0;

        printf("----------------------------------------------------------------------------------------\n");
        printf(" C avg = %11.6f ms  |  ASM avg = %11.6f ms  |  Speedup = %.5fx  |  %s\n\n",
               c_avg_ms, asm_avg_ms, speedup, all_pass ? "PASS" : "FAIL");

        free(A);
        free(B);
    }
    return 0;
}