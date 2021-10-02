#include <iostream>
#include <omp.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    int n = 6;
    int m = 8;
    int a[n][m];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            a[i][j] = rand() % 100;
        }
    }

    int min = a[0][0];
    int max = a[0][0];

    #pragma omp parallel for shared(a, min, max)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (max < a[i][j])

            #pragma omp critical
            {
                max = a[i][j];
            }

            #pragma omp critical
            if (min > a[i][j])
            {
                min = a[i][j];
            }
        }
    }

    printf("Minimum is: %d \nMaximum is: %d\n", min, max);
    return 0;
}

// reduced мы сделали с помощью shared
// critical - Specifies that code is only be executed on one thread at a time.
