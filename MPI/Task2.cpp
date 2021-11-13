#include<mpi.h>
#include<iostream>

int main(int argc, char** argv)
{
//    srand((unsigned int)time(NULL));
//    вместо NULL из С используют нову. более продуманную переменную nullptr (+ что-то с указателями)
    srand((unsigned int)time(nullptr));
    int size, rank = 4;
    int N = 20;
    int x[N];
    int result;

    MPI_Init(&argc, &argv);


    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int elements_per_proc = N / size;
    int *subarr = new int[elements_per_proc];
    int localmax;
    if (rank == 0) {
        for (int i = 0; i < N; i++) {
            x[i] = rand() % 2000;
            printf("%d ", x[i]);
        }
    }

//    скаттер и редюсе коллективные операции
//    все ждут пока не выполнится, тк блокирующая ф-ция
//    распределени данных, не путать с BCast, деление на части и каждому процу часть массива
    MPI_Scatter(x, elements_per_proc, MPI_INT, subarr, elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    localmax = 0;
    for (int i = 0; i < elements_per_proc; i++)
        if (subarr[i] > localmax) localmax = subarr[i];

//    работает с векторами, есть еще олредьюс без айди рута
    MPI_Reduce(&localmax, &result, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

//    каждый поток дойдет до сюда
    if (rank == 0)
        printf("\nmax = %d \n", result);

    MPI_Finalize();
    return 0;
}