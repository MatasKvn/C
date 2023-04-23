#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "BigInt.h" // pakeisti i h

int main()
{
    BigInt a = BigInt_fromString("34");
    BigInt b = BigInt_fromString("-97643");
    BigInt c;
    BigInt d;

    char* mA = BigInt_toStr(a);
    char* mB = BigInt_toStr(b);
    char* mC;
    char* mD;

    printf("Numbers: a:|%s| b:|%s|\n", mA, mB);
    free(mA);
    free(mB);

    // sum
    printf("=================\n Addition: ");
    sumBigInt(a, b, &c);
    mC = BigInt_toStr(c);
    mA = BigInt_toStr(a);
    mB = BigInt_toStr(b);
    printf("|%s| = |%s| + |%s|\n", mC, mA, mB);
    freeBigInt(c);
    free(mC);

    // subtraction
    printf("=================\n Subtraction: ");
    subtractBigInt(a, b, &c);
    mC = BigInt_toStr(c);
    printf("|%s| = |%s| - |%s|\n", mC, mA, mB);
    freeBigInt(c);
    free(mC);

    // multiplication
    printf("=================\n Multiplication: ");
    multiplyBigInt(a, b, &c);
    mC = BigInt_toStr(c);
    printf("|%s| = |%s| * |%s|\n", mC, mA, mB);
    freeBigInt(c);
    free(mC);

    // division and remainder
    printf("=================\n Division: ");
    divideBigInt(a, b, &c, &d);
    mC = BigInt_toStr(c);
    mD = BigInt_toStr(d);
    printf("|%s|", mC);
    printf("\n=================|%s||%s|\n Remainder: ", mA, mB);
    printf("|%s|", mD);
    free(mD);
    free(mC);

    // absolute value
    printf("\n================\n abs: ");
    absBigInt(b, &b);
    mB = BigInt_toStr(b);
    printf("|%s|", mB);

    freeBigInt(a);
    freeBigInt(b);
    freeBigInt(c);
    freeBigInt(d);

    return 0;



    return 0;
}