//
// Created by YDiamond on 24.10.2021.
//

#include <stdlib.h>
#include "merge_sort.h"


static int get(const int *mas, int *pointers, const int *sizes, int threads) {
    int j = 0;
    while (pointers[j] == sizes[j + 1] - sizes[j] && j != threads) j++;

    if (j == threads)
        exit(0);

    int min = mas[pointers[j]];
    int position = j;
    for (int pointer = 0; pointer < threads; pointer++) {
        if (pointers[pointer] < sizes[pointer + 1] - sizes[pointer] && min > mas[sizes[pointer] + pointers[pointer]]) {
            min = mas[sizes[pointer] + pointers[pointer]];
            position = pointer;
        }
    }

    pointers[position]++;
    return min;
}

void mergeSort(int **mas, int size, int threads, void (*sort)(int *, int)) {

    int mod, j, i;
    int sizes[threads + 1];

    sizes[0] = 0;
    mod = size % threads;
    for (j = 1; j <= threads; j++) {
        sizes[j] = sizes[j - 1] + size / threads;
        if (mod > 0) {
            mod--;
            sizes[j]++;
        }
    }

#pragma omp parallel firstprivate(sort, sizes) private(i) shared(mas, size, threads) num_threads(threads) default(none)
    {
        printf("threads: %i\n", omp_get_num_threads());
        #pragma omp for
        for (i = 0; i < threads; i++)
            sort(*mas + sizes[i], sizes[i + 1] - sizes[i]);
    }

    int pointers[threads];
    for (int m = 0; m < threads; m++) {
        pointers[m] = 0;
    }

    int *new_mas = malloc(size * sizeof(int));
    for (int m = 0; m < size; m++) {
        new_mas[m] = get(*mas, pointers, sizes, threads);
    }
    free(*mas);
    *mas = new_mas;
}