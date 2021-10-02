#include <iostream>
#include <omp.h>

int main()
{
    int n = 30;
    int a[n];

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
    }

    int counter = 0;

    #pragma omp parallel for shared(a, counter)
    for (int i = 0; i < n; i++)
    {
        if (a[i] % 9 == 0)
        {
            #pragma omp atomic

            counter += 1;
        }
    }

    printf("Counter = %d\n", counter);
    return 0;
}

// atomic - The atomic construct ensures that a specific storage location is accessed atomically,
// rather than exposing it to the possibility of multiple,
// simultaneous reading and writing threads that may result in indeterminate values.