#include "mpi.h"
#include <math.h>
#include <stdio.h>
int main(int argc, char **argv)
{
    MPI_Status status;
    int num;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &num);
    double d = 100.0;
    int tag = 1;
    if (num == 0)
    {
        // synchronous Send
        MPI_Ssend(&d, 1, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD);
        MPI_Send(&d, 1, MPI_DOUBLE, 1, 2, MPI_COMM_WORLD);
        printf("done 0");
    }
    else
    {
        // Synchronous Send
        MPI_Recv(&d, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD, &status);
        MPI_Recv(&d, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
        printf("done 1");
    }

    MPI_Finalize();
    return 0;
}