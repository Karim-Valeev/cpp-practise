#include <iostream>
#include <omp.h>

int main()
{
    srand((unsigned int)time(nullptr));

    int n = 6;
    int m = 8;

    int d[n][m];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            d[i][j] = (rand() % 20);
            printf("d[%d][%d] = %d\n", i,j, d[i][j]);
        }
    }


    #pragma omp parallel sections shared(d)
    {
        #pragma omp section
        {
            double sum = 0;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    sum += d[i][j];
                }
            }
            double average = sum / (n * m);
            printf("\nThread id: %d\nAverage: %f\n\n", omp_get_thread_num(), average);
        }

        #pragma omp section
        {
            int min = d[0][0];
            int max = d[0][0];

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (max < d[i][j])
                    {
                        max = d[i][j];
                    }
                    if (min > d[i][j])
                    {
                        min = d[i][j];
                    }
                }
            }
            printf("Thread id: %d\nMin value: %d\nMax value: %d\n\n", omp_get_thread_num(), min, max);
        }

        #pragma omp section
        {
            int counter = 0;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (d[i][j] % 3 == 0)
                    {
                        counter++;
                    }
                }
            }
            printf("Thread id: %d\nCounter: %d", omp_get_thread_num(), counter);
        }
    }
    return 0;

}

// section -
