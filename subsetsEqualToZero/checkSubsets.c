#include <stdio.h>
#include <math.h>
#include "checkSubsets.h"

// Checks if a given set has a subset, that is equal to 0
void checkSubsets(int* arr, int n)
{
    int sum;
    int totalSubsets = pow(2, n);
    int count;

    for (int i = 1; i < totalSubsets; i++) {
        sum = 0;
        for (int j = 0; j < n; j++) {
            // printf("%d / 2^%d %% 2 ==== %d \n",i, j, (i / (int)pow(2, j)) % 2);
            if ((i / (int)pow(2, j)) % 2 == 1){ // checks wheter to include element into the subset
                sum += arr[j];  // counts the sum of the subset
            }
        }
        if(sum == 0){
            printf("Subset with sum equal to 0 found!");
            return;
        }
    }
    printf("Subset with sum equal to 0 not found!");
}

// Prints the first n elements of the array
void printSet(int* arr, int n)
{
    printf("{");
    for(int i=0; i<n; ++i){
        printf("%d", arr[i]);
        if(i != n-1){
            printf(", ");
        }
    }
    printf("}");
}