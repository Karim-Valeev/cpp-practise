#include<mpi.h>
#include<iostream>
#include <ctime>

using namespace std;

void showArrayAndProcRank(int rank, int arr[], int arr_length){
    printf("Rank: %d\n", rank);
    for (int i = 0; i < arr_length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    srand((unsigned int)time(nullptr));
    int rank, size;
    int N = 20;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int partition = N / size;
    int *arr = new int[N];
    int *r_arr = new int[partition];
    int *result = new int[N];

    if (rank == 0)
    {
        printf("Array before: ");
        for (int i = 0; i < N; i++){
            arr[i] = i;
            printf("%d ", arr[i]);
        }
        for (int i = 0; i < size; i++){
            int *s_arr = new int[partition];
            for (int j = 0; j < partition; j++)
                s_arr[j] = arr[j + i * partition];
            if (i == 0){
                r_arr = s_arr;
                showArrayAndProcRank(0, r_arr, partition);
            } else {
                MPI_Send(s_arr, partition, MPI_INT, i, i + 10, MPI_COMM_WORLD);
            }
        }
    }
    if (rank != 0){
        MPI_Recv(r_arr, partition, MPI_INT, 0, rank + 10, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        showArrayAndProcRank(rank, r_arr, partition);
        MPI_Send(r_arr, partition, MPI_INT, 0, rank + 100, MPI_COMM_WORLD);
    } else {
        for (int i = 0; i < partition; i++){
            arr[i] = r_arr[i];
        }
    }

    if (rank == 0){
        for (int i = 1; i < size; i++)
        {
            MPI_Recv(r_arr, partition, MPI_INT, i, i + 100, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
            for (int j = 0; j < partition; j++)
            {
                arr[partition * i + j] = r_arr[j];
            }
        }
        printf("Array after: ");
        for (int i = 0; i < N; i++)
            printf("%d ", arr[i]);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}