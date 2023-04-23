// Demonstrative code

#include <stdio.h>
#include "checkSubsets.h"

int main()
{
    int arr[] = {-3, -999, 2, -5, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Set: ");
    printSet(arr, n);
    printf("\n");
    checkSubsets(arr, n);

    return 0;
}