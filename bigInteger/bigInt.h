#ifndef __BIGINT__
#define __BIGINT__

typedef struct BigInt{
    int sign;
    int capacity;
    int *digits;
} BigInt;

// arithmetic operations
void divideBigInt(BigInt a, BigInt b, BigInt* quetient, BigInt* remainder);
void multiplyBigInt(BigInt a, BigInt b, BigInt* output);
void subtractBigInt(BigInt a, BigInt b, BigInt* output);
void sumBigInt(BigInt a, BigInt b, BigInt* output);

void sumBigIntAbs(BigInt a, BigInt b, BigInt* output);
void subtractBigIntAbs(BigInt a, BigInt b, BigInt* output);
void absBigInt(BigInt a, BigInt* output);

// conversion operations
BigInt readBigInt(FILE *stream);
BigInt BigInt_fromString(char *str);
char* BigInt_toStr(BigInt n);
BigInt BigInt_fromInt(int n);
int BigInt_toInt(BigInt n);

// utility operations
int compareBigInt(BigInt a, BigInt b);
int compareBigIntAbs(BigInt a, BigInt b);
void freeBigInt(BigInt a);
void copyBigInt(BigInt* destination, BigInt source);

#endif