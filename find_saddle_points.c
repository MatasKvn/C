/*

This program finds the saddle points in the given matrix

*/

#include <stdio.h>
#include <stdlib.h>

int isSaddlePoint(int n, int A[][n], int posX, int posY)// function detects wheter an element is a saddle point or not
{
    int isCorrect1 = 1;
    int isCorrect2 = 1;

    for(int i=0; i<n; ++i)
    {
        if(A[posY][posX] >= A[posY][i] && posX != i)
        {
            isCorrect1 = 0;
            break;
        }
        if(A[posY][posX] <= A[i][posX] && posY != i) 
        {
            isCorrect1 = 0;
            break;
        }
    }

    for(int i=0; i<n; ++i)
    {
        if(A[posY][posX] <= A[posY][i] && posX != i)
        {
            isCorrect2 = 0;
            break;
        }
        if(A[posY][posX] >= A[i][posX] && posY != i) 
        {
            isCorrect2 = 0;
            break;
        }
    }

    if(isCorrect1 + isCorrect2 == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

int main()
{
    //input
    int n;

    printf("Enter the number of rows and collumns: ");
    scanf("%d", &n);

    int A[n][n];
    printf("Enter the %d matrix elements:\n", n*n);

    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
            scanf("%d", &A[i][j]);
    }


    // print entered matrix 
    printf("=================Your entered matrix:=================\n");
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
            printf("%d ", A[i][j]);
        printf("\n");
    }

    printf("=================Saddle point matrix:=================\n");
    // printf saddle point matrix(0 - no, 1 - yes)
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            printf("%d ", isSaddlePoint(n, A, j, i));
        }
        printf("\n");
    }

    // print the coordinates of the saddle point
    printf("===========Coordinated of the saddle points:=========\n");
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            if(isSaddlePoint(n, A, j, i))
                printf("(%d;%d)\n", j+1, i+1);
        }
    }

    return 0;
}
