#include <iostream>
#include <omp.h>

int main()
{
    int global_number_of_threads = 8;
#pragma omp parallel num_threads(global_number_of_threads)
    {
        int thread_id = omp_get_thread_num();
        int local_number_of_threads = omp_get_num_threads();
        printf("Hello world | thread id: %d | threads: %d\n", thread_id, local_number_of_threads);
    }
    return 0;
}

// Вывод не всегда одинаковый

// Все нити процесса имеют равные права доступа к любым частям виртуальной памяти процесса -> поэтому рандомно вызываются
