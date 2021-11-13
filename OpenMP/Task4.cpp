#include <iostream>
#include <omp.h>

int main()
{
    srand((unsigned int)time(nullptr));

    int n = 10;
    int a[n];
    int b[n];

//    Filling arrays with random values
    for(int i = 0; i < n; i++)
    {
        a[i] = (rand() % 10);
        b[i] = (rand() % 10);
        printf("a[%d] = %d   b[%d] = %d\n", i, a[i], i, b[i]);
    }

    int min = a[0];
    int max = b[0];

    #pragma omp parallel num_threads(2)
    {
        if(omp_get_thread_num() == 0)
        {
            for (int i = 0; i < n; i++)
            {
                if(min > a[i])
                {
                    min = a[i];
                }
            }
        } else {
            for (int i = 0; i < n; i++)
            {
                if(max < b[i])
                {
                    max = b[i];
                }
            }
        }
    }

    printf("\nmin in a:%d\n", min);
    printf("max in b:%d\n", max);
    return 0;
}
