//
// Created by YDiamond on 13.10.2021.
//

#include <stdio.h>
#include "algs_shell.h"
#include "omp.h"

int delta[8] = {1, 4, 10, 23, 57, 132, 301, 701};

int define_delta(int size) {
    int i = 0;
    while (delta[i] < size && i < 7) {
        i++;
    }
    return i;
}

void shell_sort(int *arr, int n) {
    // Start with a big gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < n; i += 1) {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
}

void parallel_shell_sort(int *arr, int n, int threads) {
    // Start with a big gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        int i, temp, position;
#pragma omp parallel default(none) private(i, temp, position) shared(arr, gap, n) num_threads(threads)
#pragma omp for
        for (i = gap; i < gap * 2; i += 1) {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            //printf("step: %i thread: %i from: %i\n", gap, omp_get_thread_num(), i);
            for (position = i; position < n; position+=gap) {
                temp = arr[position];

                // shift earlier gap-sorted elements up until the correct
                // location for a[i] is found
                int j;
                for (j = position; j >= gap && arr[j - gap] > temp; j -= gap)
                    arr[j] = arr[j - gap];

                //  put temp (the original a[i]) in its correct location
                arr[j] = temp;
            }
        }


    }
}