#include <stdio.h>
#include "algs/alg_smooth.h"
#include "algs/algs_shell.h"
#include "merge_sort.h"

void print_mas(int**mas, int size){
    for(int i = 0; i < size; i++){
        printf("%i ", *mas[i]);
    }
}
#define size 2000
int main() {
    int** mas = malloc(size * sizeof(int*));

    for(int i = 0; i < size; i++){
        int * tmp = malloc(sizeof(int));
        *tmp = size - i;
        mas[i] = tmp;
    }
    smooth_sort((value_t *) mas, size);

    print_mas(mas, size);
    for(int i = 0; i < size; i++)
        free(mas[i]);
    free(mas);
    return 0;
}
