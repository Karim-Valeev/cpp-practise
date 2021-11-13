#include <iostream>
#include <omp.h>

int main()
{
    int n = 16000;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
    }

    double b[n];

    double start = omp_get_wtime();

    #pragma omp parallel for schedule(static, 8) num_threads(8)
    for (int i = 1; i < n - 1; i++) {
        b[i] = (a[i-1] + a[i] + a[i+1])/3;
    }
    double end = omp_get_wtime( );
    printf("Static section time = %fs\n", end-start);

    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic, 400) num_threads(8)
    for (int i = 1; i < n - 1; i++) {
        b[i] = (a[i-1] + a[i] + a[i+1])/3;
    }
    end = omp_get_wtime();
    printf("Dynamic section time = %fs\n", end-start);

    start = omp_get_wtime();
    #pragma omp parallel for schedule(guided, 2000) num_threads(8)
    for (int i = 1; i < n - 1; i++) {
        b[i] = (a[i-1] + a[i] + a[i+1])/3;
    }
    end = omp_get_wtime();
    printf("Guided section time = %fs\n", end-start);

    start = omp_get_wtime();
    #pragma omp parallel for schedule(auto) num_threads(8)
    for (int i = 1; i < n - 1; i++) {
        b[i] = (a[i-1] + a[i] + a[i+1])/3;
    }
    end = omp_get_wtime();
    printf("Auto section time = %fs\n", end-start);
    return 0;
}
// статик хуже остальных

// Когда в dynamic слишком маленькая или слишком большая порция - тормозит

// guided:
// Similar to dynamic scheduling, but the chunk size starts off large
// and decreases to better handle load imbalance between iterations.
// The optional chunk parameter specifies them minimum size chunk to use.
// By default the chunk size is approximately loop_count/number_of_threads.

// The OpenMP documentation for schedule clause says that, when schedule(auto) is specified,
// then the decision regarding the scheduling is delegated to compiler or runtime system.