#include <iostream>
#include <omp.h>

int main()
{
    int n = 100;
    int a[n];

    for (int i = 0; i < n; i++)
    {
        a[i] = (rand() % 100);
    }

    int sum = 0;
    double average = 0;

    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }
    average = sum / n;
    printf("Average with reduction: %f\n\n", average);

    sum = 0;

    #pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
//        printf("sum =  %d\n", sum);
//        printf("a[%d] = %d\n",i, a[i]);
        sum += a[i];
    }

    average = sum / n;
    printf("Average without reduction: %f\n", average);
    return 0;
}

// Почему результаты разные - race condition
// Если его тормознуть принтф, то сичтает нормально,
// без нагрузок - перехватывает значения не в тот момент и поэтому меньше среднее

// reduction:
// OpenMP will make a copy of the reduction variable per thread,
// initialized to the identity of the reduction operator, for instance 1 for multiplication.

// Each thread will then reduce into its local variable;

// At the end of the parallel region, the local results are combined,
// again using the reduction operator, into the global variable.
