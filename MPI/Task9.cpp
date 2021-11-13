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
    int *len = new int[size];
    int *ind = new int[size];
    int *revind = new int[size];

//
    int rest = N;
    int k = rest / size;
    len[0] = k;
    ind[0] = 0;
    revind[0] = N - k;

    for (int i = 1; i < size; i++) {
        rest -= k;
        k = rest / (size - i);
        len[i] = k;
        ind[i] = ind[i - 1] + len[i - 1];
        revind[i] = revind[i - 1] - len[i];
    }
    int ProcLen = len[rank];
    int *subarr = new int[ProcLen];

    MPI_Scatterv(x, 5, ind, MPI_INT, subarr, 5, MPI_INT, 0, MPI_COMM_WORLD);

    int *revers = new int[5];
    printf("rank: %d\n", rank);
    for(int i = 0; i < ProcLen; i++) {
        revers[i] = subarr[ProcLen - i - 1];
        printf("%d ",revers[i]);
    }
    printf("\n");
//    обеспечивающей переменное число посылаемых данных
    MPI_Gatherv(revers, ProcLen, MPI_INT, result, len, revind, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        printf("\n");
        for(int i = 0; i < N; i++)
            printf("%d ",result[i]);
    }

    MPI_Finalize();
    return 0;
}
