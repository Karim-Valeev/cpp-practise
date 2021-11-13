#include<mpi.h>
#include<iostream>


int main(int argc, char** argv)
{
    srand((unsigned int)time(nullptr));
    int rank, size;
    int N = 20;
    int *x = new int[N];
    int *result = new int[N];
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            x[i] = i;
            printf("%d ",x[i]);
        }
        printf("\n");
    }

//  вспомогательные массивы
    int *send_lengths = new int[size];
    int *offsets = new int[size];
    int *revind = new int[size];

//
    int k = N / size;
    send_lengths[0] = k;
    offsets[0] = 0;
    revind[0] = N - k;

    for (int i = 1; i < size; i++) {
        send_lengths[i] = k;
        offsets[i] = offsets[i - 1] + send_lengths[i - 1];
//        с кем надо местами поменяться процессам
        revind[i] = revind[i - 1] - send_lengths[i];
    }

    int *sub_arr = new int[k];

    MPI_Scatterv(x, send_lengths, offsets,
                 MPI_INT, sub_arr, k,
                 MPI_INT, 0, MPI_COMM_WORLD);

    int *reverse_sub_arr = new int[k];
    printf("rank: %d\n", rank);
    for(int i = 0; i < k; i++) {
        reverse_sub_arr[i] = sub_arr[k - i - 1];
        printf("%d ",reverse_sub_arr[i]);
    }
    printf("\n");

    MPI_Gatherv(reverse_sub_arr, k, MPI_INT, result, send_lengths, revind, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        printf("\n");
        for(int i = 0; i < N; i++)
            printf("%d ",result[i]);
    }

    MPI_Finalize();
    return 0;
}
