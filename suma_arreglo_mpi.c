#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int total_procs, id_proc;
    const int TAM = 8;
    int arreglo[TAM] = {2, 4, 6, 8, 10, 12, 14, 16};

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &total_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &id_proc);

    int elementos_por_proc = TAM / total_procs;
    int* sub_arreglo = (int*)malloc(elementos_por_proc * sizeof(int));

    MPI_Scatter(arreglo, elementos_por_proc, MPI_INT,
                sub_arreglo, elementos_por_proc, MPI_INT,
                0, MPI_COMM_WORLD);

    int suma_local = 0;
    for (int i = 0; i < elementos_por_proc; i++) {
        suma_local += sub_arreglo[i];
    }

    int suma_total = 0;
    MPI_Reduce(&suma_local, &suma_total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (id_proc == 0) {
        printf("La suma total del arreglo es: %d\n", suma_total);
    }

    free(sub_arreglo);
    MPI_Finalize();
    return 0;
}
