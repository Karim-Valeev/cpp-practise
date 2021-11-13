#include<mpi.h>
#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
//    По кругу от проца к процу передаем число и инкрементируем на +1
    int rank,size;
    int message = 1;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int *sendBuf = new int[1];
    int *recBuf = new int[1];
    int s_message, r_message;

    if (rank == 0) {
        s_message = 1;
        printf("message before: %d\n", s_message);
        MPI_Send(&s_message, 1, MPI_INT, rank + 1, rank + 1, MPI_COMM_WORLD);
        MPI_Recv(&r_message, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        printf("message after: %d\n", r_message);
    }
    if (rank != 0) {
        MPI_Recv(&r_message, 1, MPI_INT, rank - 1, rank, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        s_message = 2*r_message;

        if (rank != size - 1){
            MPI_Send(&s_message, 1, MPI_INT, rank + 1, rank + 1, MPI_COMM_WORLD);
        } else {
            MPI_Send(&s_message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}

