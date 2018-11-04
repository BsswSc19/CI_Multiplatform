#include <math.h>
#include <stdio.h>
#include <stdlib.h>

extern void dgesv_(int* n, int* nrhs, double* a, int* lda, int* ipiv,
                   double* b, int* ldb, int* info);

int main(int argc, const char* argv[]) {
    const double THRESHOLD = 1.0e-16;

    int N = 5; 
    int nrhs = 1;

    int i = 0;
    int j = 0;

    // Define problem Ax = b
    double A[] = {1.0, 2.0, 3.0, 4.0, 5.0, 
                  2.0, 1.0, 2.0, 3.0, 4.0, 
                  3.0, 2.0, 1.0, 2.0, 3.0,
                  4.0, 3.0, 2.0, 1.0, 2.0,
                  1.0, 4.0, 3.0, 2.0, 1.0};
    double b[] = {1.0, 1.0, 1.0, 1.0, 1.0};

    // Solution is computed inplace, so create variables to store results.
    // Copy problem specification to work arrays.
    double x[N];
    for (i=0; i<N; ++i) {
        x[i] = b[i];
    }

    double LU[N*N];
    for (i=0; i<N*N; ++i) {
        LU[i] = A[i];
    }

    // Solve problem
    int ipiv[] = {0, 0, 0, 0, 0};
    int info = 0;
    dgesv_(&N, &nrhs, LU, &N, ipiv, x, &N, &info);
    if (info > 0) {
        printf("LAPACK ERROR - Unable to solve Ax = b\n");
        exit(1);
    }

    // Test solution
    for (i=0; i<N; ++i) {
        double b_i = 0.0;
        for (j=0; j<N; ++j) {
            b_i += A[j*N + i] * x[j];
        }

        if (fabs(b[i] - b_i) > THRESHOLD) {
            printf("FAIL - Solution %.16f at %d is not expected value of %.16f\n", 
                   b_i, i, b[i]);
            exit(2);
        }
    }

    return 0;
}

