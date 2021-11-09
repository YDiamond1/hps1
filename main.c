#include <stdio.h>
#include "algs/alg_smooth.h"
#include "algs/algs_shell.h"
#include "merge_sort.h"
#include "time.h"
#include <sys/time.h>
#include <string.h>


const char *format = "threads: %i - %s sort, real: %.2fs cpu %.2fs \n";

int check_sort(const int *mas, int size) {
    for (int i = 1; i < size; i++) {
        if (mas[i] < mas[i - 1])
            return 0;
    }
    return 1;
}

void print_mas(int *mas, int size) {
    for (int i = 0; i < size; i++) {
        printf("%i ", mas[i]);
    }
}

typedef void(*ISort)(int *, int);

#define size 5000000
#define qThread 3
#define qSortings 2

int main() {
    int threads[qThread] = {1, 2, 4};
    ISort sortings[2] = {smooth_sort, shell_sort};
    char *names[2] = {"smooth", "shell"};

    int *ideal_mas = malloc(size * sizeof(int));
    int *mas_for_sort = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        ideal_mas[i] = size - i;
    }

    for (int thread = 0; thread < qThread; thread++) {
        for (int sorting = 0; sorting < qSortings; sorting++) {
            memcpy(mas_for_sort, ideal_mas, size * sizeof(int));
            struct timeval real_start, real_end;
            clock_t cpu_start;
            clock_t cpu_end;
            double cpu_time;
            double real_time;


            cpu_start = clock();
            gettimeofday(&real_start, NULL);

            mergeSort(&mas_for_sort, size, threads[thread], sortings[sorting]);

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

            printf(format, threads[thread], names[sorting], real_time, cpu_time);
        }
    }


    //print_mas(ideal_mas, size);

    free(ideal_mas);
    free(mas_for_sort);
    return 0;
}
