#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 100000000  // Arreglo grande para notar diferencias

int main() {
    int *array = malloc(SIZE * sizeof(int));
    long long sum = 0;
    double start, end;

    // Inicializar el arreglo
    for (int i = 0; i < SIZE; i++)
        array[i] = 1;

    for (int threads = 1; threads <= 16; threads *= 2) {
        sum = 0;
        omp_set_num_threads(threads);

        start = omp_get_wtime();
        #pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < SIZE; i++) {
            sum += array[i];
        }
        end = omp_get_wtime();

        printf("Hilos: %d, Suma: %lld, Tiempo: %f segundos\n", threads, sum, end - start);
    }

    free(array);
    return 0;
}
