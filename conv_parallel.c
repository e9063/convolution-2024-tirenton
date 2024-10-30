#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

void reverse_filter(int *F, int *FF, int NF) {
    for (int i = 0; i < NF; i++) {
        FF[i] = F[NF - i - 1];
    }
}

void parallel_convolution(int *A, int *FF, int *R, int NA, int NF) {
    omp_set_num_threads(8);
    #pragma omp parallel for
    for (int i = 0; i <= NA - NF; i++) {
        R[i] = 0;
        for (int j = 0; j < NF; j++) {
            R[i] += A[i + j] * FF[j];
        }
    }
}

int main() {
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);
    int *FF = malloc(sizeof(int) * NF);
    int *R = malloc(sizeof(int) * (NA - NF + 1));

    for (int i = 0; i < NA; i++)
    {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < NF; i++)
    {
        scanf("%d", &F[i]);
    }

    reverse_filter(F, FF, NF);

    clock_t start_timep = clock();
    parallel_convolution(A, FF, R, NA, NF);
    clock_t end_timep = clock();
    double parallel_time = (double)(end_timep - start_timep) / CLOCKS_PER_SEC;

    // printf("Parallel convolution time: %f seconds\n", parallel_time);

    // printf("Convolution result:\n");
    for (int i = 0; i < NA - NF +1; i++) {
        printf("%d\n", R[i]);
    }
    // printf("\n");

    free(F);
    free(A);
    free(FF);
    free(R);

    return 0;
}
