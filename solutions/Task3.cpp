#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    int a = 10;
    int b = 20;

    printf("Before first: a:%d, b:%d\n", a, b);
#pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        int myid = omp_get_thread_num();
        a += myid;
        b += myid;
        printf("thread number %d, threads: %d\n", myid, omp_get_num_threads());
        printf("In first: a:%d, b:%d\n", a, b);
    }
    printf("After first: a:%d, b:%d\n", a, b);

    printf("Before second: a:%d, b:%d\n", a, b);
#pragma omp parallel num_threads(4) shared(a) private(b)
    {
        int myid = omp_get_thread_num();
        a -= myid;
        b -= myid;
        printf(" thread number %d, threads: %d\n", myid, omp_get_num_threads());
        printf("In second: a:%d, b:%d\n", a, b);
    }
    printf("After second: a:%d, b:%d\n", a, b);
}

