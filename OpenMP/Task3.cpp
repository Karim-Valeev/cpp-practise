#include <iostream>
#include <omp.h>

int main()
{
    int a = 20;
    int b = 100;

    printf("Initial values: \na:%d\nb:%d\n\n", a, b);

    #pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {
        int thread_id = omp_get_thread_num();
        int local_number_of_threads = omp_get_num_threads();

        a += thread_id;
        b += thread_id;

        printf("threads: %d | thread id: %d\n", local_number_of_threads, thread_id);
        printf("In first area: \na:%d\nb:%d\n\n", a, b);
    }

    printf("After first area: \na:%d\nb:%d\n\n", a, b);
    std::cout << "==================================\n\n";
    printf("Before second area: \na:%d\nb:%d\n\n", a, b);

    #pragma omp parallel num_threads(4) shared(a) private(b)
    {
        int thread_id = omp_get_thread_num();
        int local_number_of_threads = omp_get_num_threads();

        a -= thread_id;
        b -= thread_id;
        printf("threads: %d | thread id: %d\n", local_number_of_threads, thread_id);
        printf("In second area: \na:%d\nb:%d\n\n", a, b);
    }

    printf("After second area: \na:%d\nb:%d\n", a, b);
    return 0;
}

// shared - The shared clause declares the variables in the list to be shared among all the threads in a team.
// All threads within a team access the same storage area for shared variables.

// private - The private clause declares the variables in the list to be private to each thread in a team.

// firstprivate - The firstprivate clause provides a superset of the functionality provided by the private clause.
// The private variable is initialized by the original value of the variable
// when the parallel construct is encountered.

