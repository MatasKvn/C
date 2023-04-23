# BIG INTEGER
this library provides the data structure and functions for holding and working 
with integers that are larger than allowed by "C" 

BigInt - big integer datatype, holds the number, its length and sign
values can be assigned manually, or using the functions provided below

# functions:

# arithmetic operations
///
void divideBigInt(BigInt a, BigInt b, BigInt* quetient, BigInt* remainder)
divides "a" by "b" and returns the "quetient" and the "remainder"
///
void multiplyBigInt(BigInt a, BigInt b, BigInt* output)
multipllies "a" and "b" and puts the result into "output"
///
void subtractBigInt(BigInt a, BigInt b, BigInt* output)
places the subtraction of "b" from "a" into "output"
///
void sumBigInt(BigInt a, BigInt b, BigInt* output)
places the sum of "a" and "b" into "output"
///

# absolute value arithmetic operations
///
void sumBigIntAbs(BigInt a, BigInt b, BigInt* output)
places the sum of "a" and "b" absolute values into "output"
///
void subtractBigIntAbs(BigInt a, BigInt b, BigInt* output)
places the absolute subtraction of "b" from "a" into "output"
///
void absBigInt(BigInt a, BigInt* output)
places the absolute value of "a" into "output"
///

# conversion operations
///
BigInt readBigInt(FILE *stream)
returns the read string as BigInt
///
BigInt BigInt_fromString(char *str)
returns *str as BigInt
///
char* BigInt_toStr(BigInt n)
returns the BigInt n as a pointer to a dynamic char array(be sure to free allocated memory)
///
BigInt BigInt_fromInt(int n)
returns the integer n as a BigInt
///
int BigInt_toInt(BigInt n)
returns the converted BigInt to int(make sure the BigInt is small enough for int to hold)
///

# utility operations
///
int compareBigInt(BigInt a, BigInt b)
compares "a" and "b", returns 1 if a>b, -1 if a<b, 0 if a=b
///
int compareBigIntAbs(BigInt a, BigInt b)
compares "a" and "b", returns 1 if |a|>|b|, -1 if |a|<|b|, 0 if |a|=|b|
///
void freeBigInt(BigInt a)
frees the memory allocated for the datatype(deletes the BigInt)
///
void copyBigInt(BigInt* destination, BigInt source)
copies the BigInt from the "source" to the "destination"
///