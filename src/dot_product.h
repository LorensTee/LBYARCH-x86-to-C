#define DOT_PRODUCT_H

void dot_product_c(int n, const double *A, const double *B, double *sdot);
extern void dot_product_asm(int n, double *A, double *B, double *sdot);
