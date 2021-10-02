#include <iostream>
#include <omp.h>

int main()
{

    #pragma omp parallel num_threads(8)
    {

        for(int i=7; i>=0; i--)
        {
            #pragma omp barrier
            {
                if(i==omp_get_thread_num())
                {
                    #pragma omp critical
                    printf("Hello world | thread id: %d | threads: %d\n", omp_get_thread_num(), 8);
                }
            }
        }
    }
    return 0;
}

