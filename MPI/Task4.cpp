#include<mpi.h>
#include<iostream>
#include <ctime>

using namespace std;

int main(int argc, char** argv)
{
    srand((unsigned int)time(nullptr));
    int N = 20;
    int rank, size;
    int a[N], min = -100, max = 100;
    int sum_count[2], proc_sum_count[2];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            int random = min + (rand() % static_cast<int>(max - min + 1));
            a[i] = random;

            printf("%d ", a[i]);
        }
    }

    int *len = new int[size];
    int *ind = new int[size];

    int rest = N;
    int k = rest / size;
    len[0] = k;
    ind[0] = 0;

    for (int i = 1; i < size; i++) {
        rest -= k;
        k = rest / (size - i);
        len[i] = k;
        ind[i] = ind[i - 1] + len[i - 1];
    }

    int proc_num = len[rank];
    int *proc_part = new int[proc_num];

    MPI_Scatterv(a, len, ind, MPI_INT, proc_part, proc_num,
                 MPI_INT, 0, MPI_COMM_WORLD);

    proc_sum_count[0] = 0;
    proc_sum_count[1] = 0;

    for (int i = 0; i < proc_num; i++) {
        if (proc_part[i] > 0) {
            proc_sum_count[0] += proc_part[i];
            proc_sum_count[1]++;
        }
    }

    MPI_Reduce(&proc_sum_count, &sum_count, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("%d %d", sum_count[0], sum_count[1]);
        double result = (double) sum_count[0] / sum_count[1];
        printf("\nMiddle: %f", result);
    }

    MPI_Finalize();
    return 0;
}