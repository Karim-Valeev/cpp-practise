#include <iostream>
#include <omp.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    int n = 600;
    int m = 800;
    int a[n][m];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            a[i][j] = rand() % 500000;
        }
    }

    int res_max = a[0][0];
    int res_min = a[0][0];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {

            if (res_max < a[i][j])
            {
                res_max = a[i][j];
            }

            if (res_min > a[i][j])
            {
                res_min = a[i][j];
            }
        }
    }



    int min = a[0][0];
    int max = a[0][0];

    #pragma omp parallel for shared(a, min, max)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {

            if (max < a[i][j]){
                #pragma omp critical(for_max)
                if (max < a[i][j]) {
                    max = a[i][j];
                }
            }

            if (min > a[i][j]){
                #pragma omp critical(for_min)
                if (min > a[i][j]) {
                    min = a[i][j];
                }
            }

        }
    }

    printf("Real Minimum is: %d Maximum is: %d\n", res_min, res_max);
    printf("From parallel areas: Minimum is: %d Maximum is: %d\n", min, max);
    return 0;
}

// reduced мы сделали с помощью shared
// critical - Specifies that code is only be executed on one thread at a time.
