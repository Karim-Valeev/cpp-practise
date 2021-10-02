#include <iostream>
#include <omp.h>

int main()
{
    int  n = 12;
    int a[n];
    int b[n];
    int c[n];

    #pragma omp parallel for schedule(static, 2) num_threads(3)
    for (int i = 0; i < n; i++)
    {
        a[i] = i;
        b[i] = i;
        printf(
                "Threads: %d | thread id: %d | a[%d] = %d | b[%d] = %d\n",
                omp_get_num_threads(),
                omp_get_thread_num(),
                i,
                a[i],
                i,
                b[i]
        );

    }

    std::cout << "\n";

    #pragma omp parallel for schedule(dynamic, 3) num_threads(4)
    for (int i = 0; i < n; i++)
    {
        c[i] = a[i] + b[i];
        printf(
                "Threads: %d | thread id: %d | c[%d] = %d\n",
                omp_get_num_threads(),
                omp_get_thread_num(),
                i,
                c[i]
        );
    }
    return 0;
}

// Schedule controls how loop iterations are divided among threads.
// Choosing the right schedule can have great impact on the speed of the application.

// So one of the advantages for using static scheduling is that it improves locality in memory access.
// The disadvantage is that bad choice of scheduling parameters can ruin the performance.

// (static, 2) - This will "chop" iteration space into blocks of two iterations
// and there will be 4 such blocks in total.

// Чем лучше деление, тем лучше работа с памятью и соотвественно эффективность

// Про dynamic
// The work will be shared amongst threads but this procedure will occur at a runtime.
// Thus involving more overhead. Second parameter specifies size of the chunk of the data.