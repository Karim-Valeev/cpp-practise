#include <iostream>
#include <omp.h>

int main()
{
    int n = 1000;

    int a[n][n];
    int b[n];
    int c[n];

    for(int i = 0; i < n; i++) {
        b[i] = (rand() % 1000);
        for(int j = 0; j < n; j++) {
            a[i][j] = (rand() % 1000);
        }
    }

    double start = omp_get_wtime();

    for(int i = 0; i < n; i++) {
        c[i] = 0;
        for(int j = 0; j < n; j++) {
            c[i] += a[i][j] * b[j];
        }
    }
    double end = omp_get_wtime( );
    printf("Sequential time = %fs\n", end-start);

    start = omp_get_wtime();

//    Todo try different options to find the best one
// static,4 and 4 threads - on average two times better
// dynamic,250 and 4 threads  - on average three times better
// guided,250 and 4 threads - on average three times better
// auto and 4 threads - on average three times better
    #pragma omp parallel for schedule(dynamic,250) num_threads(4)
    for(int i = 0; i < n; i++) {
        c[i] = 0;
        for(int j = 0; j < n; j++) {
            c[i] += a[i][j] * b[j];
        }
    }
    end = omp_get_wtime( );
    printf("Parallel time = %fs\n", end-start);
    return 0;
}

