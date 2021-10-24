//
// Created by YDiamond on 13.10.2021.
//

#include "algs_shell.h"

int delta[8] = {1, 4, 10, 23, 57, 132, 301, 701};

int define_delta(int size){
    int i = 0;
    while(delta[i] < size && i < 8){
        i++;
    }
    return i;
}

void insertion_sort(int* mas, int size, int d, int start){
    for(int i = start+d; i < size; i+=d){
        int j = i;
        while(mas[j] < mas[j - d] && j > start){
            swap(mas + j, mas + j - d );
            j-=d;
        }
    }
}

void shell_sort(int * mas, int size){
    int start = define_delta(size);
    for(int i = start; i >= 0; i-- ){
        for(int j = 0; j < delta[i]; j++){
            insertion_sort(mas, size, delta[i], j);
        }
    }
}