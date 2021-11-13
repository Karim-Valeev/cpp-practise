#include<mpi.h>
#include<iostream>


int main(int argc, char** argv)
{
    srand((unsigned int)time(nullptr));
    int rank, size;
    int N = 2000000;
    int x[N];

    double startSend, endSend;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        for (int i = 0; i < N; i++) {
            x[i] = rand() % 1000;
        }

        startSend = MPI_Wtime();
        MPI_Send(x, N, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(x, N, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        endSend = MPI_Wtime();
        printf("Send time: %f\n", endSend-startSend);

//        MPI_SSEND is a way of ensuring that both processes
//        have reached a certain point in their execution without having to do an MPI_BARRIER
        startSend = MPI_Wtime();
        MPI_Ssend(x, N, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Recv(x, N, MPI_INT, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        endSend = MPI_Wtime();
        printf("Ssend time: %f\n", endSend-startSend);

//      it expects a ready destination to receive the message. This can increase the MPI performance
        startSend = MPI_Wtime();
        MPI_Rsend(x, N, MPI_INT, 1, 2, MPI_COMM_WORLD);
        MPI_Recv(x, N, MPI_INT, 1, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        endSend = MPI_Wtime();
        printf("Rsend time: %f\n", endSend-startSend);

    } else {
        MPI_Recv(x, N, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(x, N, MPI_INT, 0, 0, MPI_COMM_WORLD);

        MPI_Recv(x, N, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Ssend(x, N, MPI_INT, 0, 1, MPI_COMM_WORLD);

        MPI_Recv(x, N, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Rsend(x, N, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}