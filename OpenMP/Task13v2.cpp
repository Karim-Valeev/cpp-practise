#include <iostream>
#include <omp.h>
#include <unistd.h>

int main()
{
    #pragma omp parallel num_threads(8)
    {
        usleep(100 * (8 - omp_get_thread_num()));
        int thread_id = omp_get_thread_num();
        int local_number_of_threads = omp_get_num_threads();
        printf("Hello world | thread id: %d | threads: %d\n", thread_id, local_number_of_threads);
    }
    return 0;
}

// Каждый поток просим подождать определенное кол-во микросекунд, чтобы они выстроились в нужном порядке
