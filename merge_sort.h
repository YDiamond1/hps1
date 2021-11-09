//
// Created by YDiamond on 24.10.2021.
//

#ifndef LAB1_MERGE_SORT_H
#define LAB1_MERGE_SORT_H
#include <omp.h>
#include <malloc.h>
void mergeSort(int **mas, int size, int threads, void (*sort)(int*, int));

#endif //LAB1_MERGE_SORT_H
