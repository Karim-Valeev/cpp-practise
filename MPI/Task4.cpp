#include<mpi.h>
#include<iostream>
#include <ctime>

using namespace std;

int main(int argc, char** argv)
{
//    srand((unsigned int)time(nullptr));
    int N = 20;
    int rank, size;
    int a[N], min = 1001, max = -1000;
    int sum_count[2], proc_sum_count[2];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            a[i] = rand() % 2000-1000;
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    int *len = new int[size];
    int *ind = new int[size];

    int k = N / size; // = 5
    len[0] = k;
    ind[0] = 0;

    for (int i = 1; i < size; i++) {
//        по сколько отправлять
        len[i] = k;
//        смещение к i-му элементу
        ind[i] = ind[i - 1] + k;
    }
    int *proc_part = new int[k];

    MPI_Scatterv(a, len, ind, MPI_INT, proc_part, k,
                 MPI_INT, 0, MPI_COMM_WORLD);

    proc_sum_count[0] = 0;
    proc_sum_count[1] = 0;

    for (int i = 0; i < 5; i++) {
        if (proc_part[i] > 0) {
            proc_sum_count[0] += proc_part[i];
            proc_sum_count[1]++;
        }
    }

    MPI_Reduce(&proc_sum_count, &sum_count, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double result = (double) sum_count[0] / sum_count[1];
        printf("\nMiddle among positive: %f", result);
    }
    MPI_Finalize();
    return 0;
}