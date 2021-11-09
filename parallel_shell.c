//
// Created by YDiamond on 09.11.2021.
//

#include <malloc.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include "algs/algs_shell.h"

static int check_sort(const int *mas, int n) {
    for (int i = 1; i < n; i++) {
        if (mas[i] < mas[i - 1])
            return 0;
    }
    return 1;
}

static void print_mas(int *mas, int n) {
    for (int i = 0; i < n; i++) {
        printf("%i ", mas[i]);
    }
}

const char *format = "threads: %i - parallel shell sort, real: %.2fs cpu %.2fs \n";

#define size 5000000
#define qThread 3

int main() {
    int threads[qThread] = {1, 2, 4};
    int *ideal_mas = malloc(size * sizeof(int));
    int *mas_for_sort = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        ideal_mas[i] = size - i;
    }

    for (int thread = 0; thread < qThread; thread++) {
        memcpy(mas_for_sort, ideal_mas, size * sizeof(int));
        struct timeval real_start, real_end;
        clock_t cpu_start;
        clock_t cpu_end;
        double cpu_time;
        double real_time;


        cpu_start = clock();
        gettimeofday(&real_start, NULL);

        parallel_shell_sort(mas_for_sort, size, threads[thread]);

        cpu_end = clock();
        gettimeofday(&real_end, NULL);

        if (check_sort(mas_for_sort, size) == 1) {
            printf("Sort OK ");
        } else {
            printf("Sort NOT OK ");
            print_mas(mas_for_sort, size);
        }

        cpu_time = (double) (cpu_end - cpu_start) / CLOCKS_PER_SEC;
        real_time = (double) (real_end.tv_usec - real_start.tv_usec) / 1000000 +
                    (double) (real_end.tv_sec - real_start.tv_sec);

        printf(format, threads[thread],  real_time, cpu_time);

    }
    free(ideal_mas);
    free(mas_for_sort);
}