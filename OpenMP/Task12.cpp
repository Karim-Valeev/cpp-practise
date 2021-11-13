#include <iostream>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>


int main()
{
    srand((unsigned int)time(nullptr));

    int n = 100;
    int a[n];
    int max = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 1000;
        printf("a[%d] = %d\n",i,a[i]);
    }

    #pragma omp parallel for shared(max) num_threads(4)
    for (int i = 0; i < n; i++)
    {
        if (a[i] % 7 == 0)
        {
            #pragma omp critical
            if (a[i] > max)
            {
                max = a[i];
            }
        }
    }

    if(max == INT_MIN)
    {
        printf("\nThere are no elements in the array that are multiples of 7");
    } else {
        printf("\nMaximum multiple of 7 element is %d\n", max);
    }

    return 0;
}