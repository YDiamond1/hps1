//
// Created by YDiamond on 24.10.2021.
//

#include <stdlib.h>
#include "merge_sort.h"


static int get(int *mas, int *pointers, int *sizes, int threads) {
    int j = 0;
    while (pointers[j] == sizes[j + 1] - sizes[j] && j != threads) j++;

    if (j == threads)
        exit(0);

    int min = mas[pointers[j]];
    int position = j;
    for (int pointer = 0; pointer < threads; pointer++) {
        if (pointers[pointer] < sizes[pointer + 1] - sizes[pointer] && min > mas[sizes[pointer] + pointers[pointer]]){
            min =  mas[sizes[pointer] + pointers[pointer]];
            position = pointer;
        }
    }

    pointers[position]++;
    return min;
}

void mergeSort(int **mas, int size, void (*sort)(int *, int)) {
    omp_set_dynamic(0);
#pragma omp parallel shared(mas, size) num_threads(2)
    {
        omp_set_num_threads(2);
        int count_of_threads = omp_get_max_threads();
        int sizes[count_of_threads + 1];
        sizes[0] = 0;
        int mod = size % count_of_threads;
        for (int j = 1; j <= count_of_threads; j++) {
            sizes[j] = sizes[j - 1] + size / count_of_threads;
            if (mod > 0) {
                mod--;
                sizes[j]++;
            }
        }
#pragma omp for
        for (int i = 0; i < count_of_threads; i++) {
            sort(*mas + sizes[i], sizes[i + 1] - sizes[i]);
        }

        int pointers[count_of_threads];
        for (int m = 0; m < count_of_threads; m++) {
            pointers[m] = 0;
        }

        int *new_mas = malloc(size * sizeof(int));
        for (int m = 0; m < size; m++) {
            new_mas[m] = get(*mas, pointers, sizes, count_of_threads);
        }
        free(*mas);
        *mas = new_mas;
    }
}