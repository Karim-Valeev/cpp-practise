#include <iostream>
#include <omp.h>

void print_thread_number()
{
    int thread_id = omp_get_thread_num();
    int local_number_of_threads = omp_get_num_threads();
    printf(" threads: %d | thread id: %d\n", local_number_of_threads, thread_id);
}

int main()
{
    int number_of_threads = 3;

    std::cout << "Parallel:\n";

#pragma omp parallel num_threads(number_of_threads) if ( number_of_threads > 2 )
    {
        print_thread_number();
    }

    std::cout << "\nNot parallel:\n";

    number_of_threads = 2;

#pragma omp parallel num_threads(number_of_threads) if ( not (number_of_threads <= 2))
    {
        print_thread_number();
    }

    return 0;
}

// Тк не || -> создался только один нулевой поток
