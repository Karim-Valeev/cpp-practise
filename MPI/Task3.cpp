#include<mpi.h>
#include<iostream>
#include <ctime>


int main(int argc, char** argv)
{
    srand((unsigned int)time(nullptr));
    int iter_num = 1000000;
    double x, y, z, pi;
    int proc_count;
    int circle_count = 0, tag = 999;
    int rank, size, proc_id;
    MPI_Status status;

    MPI_Init(&argc, &argv);


    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    proc_count = 0;
    for (int i = 0; i < iter_num; i++) {
        x = (double)rand() / (double)RAND_MAX * 2 - 1;
        y = (double)rand() / (double)RAND_MAX * 2 - 1;
        z = x * x + y * y;
        if (z <= 1) proc_count++;
    }
//    printf("%d", proc_count);
//    recv и send операции вида точка точка
    if (rank == 0) {
        circle_count = proc_count;
        for (proc_id = 1; proc_id < size; proc_id++) {
            MPI_Recv(&proc_count, 1, MPI_INT, proc_id, tag, MPI_COMM_WORLD, &status);
            circle_count += proc_count;
        }
        pi = (double) circle_count / (iter_num * size) * 4;
        printf("Iterations: %d, Pi ~= %g \n", iter_num * size, pi);
    } else {
        MPI_Send(&proc_count, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}