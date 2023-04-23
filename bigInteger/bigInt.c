#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "BigInt.h"

/// arithmetic operations

void divideBigInt(BigInt a, BigInt b, BigInt* quetient, BigInt* remainder)
{
    BigInt zero = BigInt_fromInt(0);
    BigInt one = BigInt_fromInt(1);

    BigInt divident;
    copyBigInt(&divident, a);
    free(remainder->digits);
    free(quetient->digits);
    *quetient = BigInt_fromInt(0);
    *remainder = BigInt_fromInt(0);
    
    
    int comparison = compareBigIntAbs(b, zero);
    
    if(comparison <= 0){
        free(quetient->digits);
        free(remainder->digits);
        *quetient = BigInt_fromInt(0);
        *remainder = BigInt_fromInt(0);
        freeBigInt(one);
        freeBigInt(zero);
        return;
    }
    
    comparison = compareBigIntAbs(a, b);
    if(comparison < 0){
        free(quetient->digits);
        free(remainder->digits);
        *quetient = BigInt_fromInt(0);
        copyBigInt(remainder, a);
        freeBigInt(zero);
        freeBigInt(one);
        return;
    }
    
    while(comparison >= 0){
        subtractBigIntAbs(divident, b, &divident);
        sumBigIntAbs(*quetient, one, quetient);

        comparison = compareBigIntAbs(divident, b);
    }

    *remainder = divident;

    freeBigInt(zero);
    freeBigInt(one);

    if(a.sign == b.sign){
        quetient->sign = 0;
    }else{
        quetient->sign = 1;
    }
    if(a.sign == 1){
        remainder->sign = 1;
    }else{
        remainder->sign = 0;
    }

    //memory leak prevention
    if(quetient->digits == a.digits){
        freeBigInt(a);
    }
    if(quetient->digits == b.digits){
        freeBigInt(b);
    }
    if(remainder->digits == a.digits){
        freeBigInt(a);
    }
    if(remainder->digits == b.digits){
        freeBigInt(b);
    }
}

void multiplyBigInt(BigInt a, BigInt b, BigInt* output)
{
    BigInt result;
    result.capacity = (a.capacity >= b.capacity) ? a.capacity : b.capacity;
    result.digits = (int*)calloc((result.capacity), sizeof(int));

    BigInt zero;
    zero.capacity = 1;
    zero.digits = (int*)calloc(zero.capacity, sizeof(int));
    zero.sign = 0;

    BigInt one = BigInt_fromInt(1);

    BigInt count;
    copyBigInt(&count, b);
    int comparison = compareBigIntAbs(b, zero);

    if(comparison <= 0){
        free(output->digits);
        *output = zero;
        freeBigInt(one);
        return;
    }

    while(comparison > 0){
        sumBigIntAbs(result, a, &result);

        subtractBigIntAbs(count, one, &count);
        comparison = compareBigIntAbs(count, zero);
    }
    freeBigInt(zero);
    freeBigInt(one);
    
    if(a.sign == b.sign){
        result.sign = 0;
    }else{
        result.sign = 1;
    }

    //memory leak prevention
    output->digits = NULL;
    if(output->digits == a.digits){
        freeBigInt(a);
    }
    if(output->digits == b.digits){
        freeBigInt(b);
    }
    free(output->digits);
    *output = result;
}

void subtractBigInt(BigInt a, BigInt b, BigInt* output)
{
    BigInt result;
    BigInt bigger, smaller;
    int comparison = compareBigIntAbs(a, b);
    if(comparison == 1){
        bigger = a;
        smaller = b;
    }else if(comparison == -1){
        bigger = b;
        smaller = a;
    }else{
        bigger = a;
        smaller = b;
    }
    
    if(bigger.sign == smaller.sign){
        subtractBigIntAbs(bigger, smaller, &result);
        if(compareBigInt(b, bigger) == 0){
            result.sign = (bigger.sign == 1) ? 0 : 1;
        }
    }else{ // if a.sign != b.sign
        sumBigIntAbs(a, b, &result);
        if(a.sign == 1 && b.sign == 0){
            result.sign = 1;
        }
        if(b.sign == 1){
            result.sign == 0;
        }
    }

    //memory leak prevention
    output->digits = NULL;
    if(output->digits == a.digits){
        freeBigInt(a);
    }
    if(output->digits == b.digits){
        freeBigInt(b);
    }
    free(output->digits);
    *output = result;
}

void sumBigInt(BigInt a, BigInt b, BigInt* output)
{
    BigInt result;
    result.sign = 0;
    int carry = 0;
    int res;

    if(a.sign == b.sign)
    {
        sumBigIntAbs(a, b, &result);
        result.sign = a.sign;
    }
    else if(a.sign != b.sign){
        BigInt bigger, smaller;
        int comparison = compareBigIntAbs(a, b);
        if(comparison == 1){
            bigger = a;
            smaller = b;
        }else if(comparison == -1){
            bigger = b;
            smaller = a;
        }else{
            bigger = a;
            smaller = b;
        }

        a.sign = 0;
        b.sign = 0;
        subtractBigIntAbs(a, b, &result);
        if(bigger.sign == 1){
            result.sign = 1;
            
        }
        if(bigger.sign == 0)
            result.sign = 0;
    }
    
    //memory leak prevention
    output->digits = NULL;
    if(output->digits == a.digits){
        freeBigInt(a);
    }
    if(output->digits == b.digits){
        freeBigInt(b);
    }
    free(output->digits);
    *output = result;
}

void subtractBigIntAbs(BigInt a, BigInt b, BigInt* output)
{
    BigInt bigger, smaller;
    int comparison = compareBigIntAbs(a, b);
    if(comparison == 1){
        bigger = a;
        smaller = b;
    }else if(comparison == -1){
        bigger = b;
        smaller = a;
    }else{
        bigger = a;
        smaller = b;
    }

    BigInt result;
    result.sign = 0;
    int carry = 0;
    int res;

    result.sign = bigger.sign;
    result.capacity = (bigger.capacity > smaller.capacity) ? bigger.capacity+1 : smaller.capacity+1;

    result.digits = (int*)calloc(result.capacity, sizeof(int));
    result.digits[result.capacity-1] = 0;

    for(int i=0; i<result.capacity-1; ++i)
    {
        if(i > smaller.capacity-1){
            res = bigger.digits[i];
        }else if(i > bigger.capacity-1){
            res = smaller.digits[i];
        }else{
            res = bigger.digits[i] - smaller.digits[i];
        }
        if(res < 0){
            carry = -1;
            res = 10 + res;
        }
        
        result.digits[i] += res;
        result.digits[i+1] = carry;

        if(result.digits[i] < 0 && i < result.capacity-2){  // adjusts subtraction with single digits
            result.digits[i] += 10;
            result.digits[i+1] -= 1;
            
        }

        carry = 0;
    }
    for(int i=result.capacity-1; i>=0; --i){
        if(result.digits[i] != 0 || i == 0){
            if(i == 0){result.sign = 0;}
            break;
        }else{
            --result.capacity;
        }
    }
    result.digits = (int*)realloc(result.digits, result.capacity*sizeof(int));

    //memory leak prevention
    output->digits = NULL;
    if(output->digits == a.digits){
        freeBigInt(a);
    }
    if(output->digits == b.digits){
        freeBigInt(b);
    }
    free(output->digits);
    *output = result;
}


void sumBigIntAbs(BigInt a, BigInt b, BigInt* output)
{
    BigInt result;
    result.sign = 0;
    int carry = 0;
    int res;

    result.capacity = (a.capacity > b.capacity) ? a.capacity : b.capacity;
    ++result.capacity;

    result.digits = (int*)calloc(result.capacity, sizeof(int));
    result.digits[result.capacity-1] = 0;

    for(int i=0; i<result.capacity-1; ++i)
    {
        if(i > b.capacity-1){
            res = a.digits[i];
        }else if(i > a.capacity-1){
            res = b.digits[i];

        }else{
            res = a.digits[i] + b.digits[i];
        }
        if(res + result.digits[i] > 9){
            carry = 1;
            res = res - 10;
        }
        result.digits[i] += res;
        result.digits[i+1] = carry;
        carry = 0;
    }

    for(int i=result.capacity-1; i>=0; --i){
        if(result.digits[i] != 0 || i == 0){
            if(i == 0){result.sign = 0;}
            break;
        }else{
            --result.capacity;
        }
    }
    result.digits = (int*)realloc(result.digits, result.capacity*sizeof(int));


    //memory leak prevention
    output->digits = NULL;
    if(output->digits == a.digits){
        freeBigInt(a);
    }
    if(output->digits == b.digits){
        freeBigInt(b);
    }
    free(output->digits);
    *output = result;
}

// |a|
void absBigInt(BigInt a, BigInt* output)
{
    if(a.digits == output->digits){
        output->sign = 0;
        return;
    }

    freeBigInt(*output);
    copyBigInt(output, a);
    output->sign = 0;
}

BigInt BigInt_fromString(char *str)
{
    BigInt result;
    result.sign = 0;
    result.capacity = 0;

    if(str[0] != '-' && !isdigit(str[0])){
        BigInt zero;
        zero.capacity = 1;
        zero.digits = (int*)calloc(zero.capacity, sizeof(int));
        zero.sign = 0;
        return zero;
    }

    if(str[0] == '-'){
        result.sign = 1;
    }

    for(int i = result.sign; isdigit(str[i]); ++i){
        ++result.capacity;
    }

    result.digits = (int*)malloc(result.capacity * sizeof(int));
    for(int i = result.capacity-1; i>=0; --i){
        result.digits[result.capacity-1 -i] = str[i+result.sign] - 48;
    }
    return result;
}

char* BigInt_toStr(BigInt n)
{
    char* result;
    if(n.capacity <= 1 && n.digits[0] == 0){
        result = (char*)malloc((2) * sizeof(char));
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    result = (char*)malloc((n.capacity+n.sign) * sizeof(char));
    if(n.sign == 1){
        result[0] = '-';
    }

    result[n.capacity+n.sign] = '\0';

    for(int i=n.sign; i<n.capacity+n.sign; ++i){
        result[i] = n.digits[n.capacity-(i-n.sign+1)] + 48;
    }

    return result;
}

BigInt BigInt_fromInt(int n)
{
    BigInt result;

    int count = 0;
    if(n == 0){
        result.digits = (int*)calloc(1, sizeof(int));
        result.capacity = 1;
        result.sign = 0;
        return result;
    }
    for(int i = n; i != 0; i /= 10){
        ++count;
    }

    result.capacity = count;
    result.digits = (int*)malloc(count * sizeof(int));
    if(n < 0){
        result.sign = 1;
        n *= -1;
    }else{
        result.sign = 0;
    }
    
    double t1, t2;
    for(int i = 0; i < count; ++i){
        t1 = pow(10.0, i+1);
        t2 = pow(10, i);
        result.digits[i] = n % (int)t1 / (int)t2;
    }

    return result;
}

int BigInt_toInt(BigInt n)
{
    int result = n.digits[0];
    int multiplier = 10;
    for(int i = 1; i < n.capacity; ++i){
        result +=  n.digits[i] * multiplier;
        multiplier *= 10;
    }
    if(n.sign == 1){
        result *= -1;
    }

    return result;
}

BigInt readBigInt(FILE *stream)
{
    char input[1000], temp;
    BigInt result;
    result.sign = 0;

    fscanf(stream, "%1[-]", &temp);
    result.sign = (temp == '-') ? 1 : 0;
    fscanf(stream, "%[0-9]", input);
    result.capacity = strlen(input);
    result.digits = (int*)malloc(result.capacity * sizeof(int));

    for(int i = 0; i < result.capacity; ++i)
    {
        result.digits[i] = input[result.capacity - i - 1] - 48;
    }

    return result;
}

/// Utility operations

// returns 1 if a>b, -1 if a<b, 0 if a=b
int compareBigInt(BigInt a, BigInt b)
{
    if(a.sign == 1 && b.sign == 0){
        return -1;
    }
    if(a.sign == 0 && b.sign == 1){
        return 1;
    }

    if(a.sign == 0 && b.sign == 0){
        if(a.capacity > b.capacity) return 1;
        if(a.capacity < b.capacity) return -1;
        
        int n = a.capacity;

        for(int i=a.capacity-1; i>=0; --i){
            if(a.digits[i] > b.digits[i])
                return 1;
            if(a.digits[i] < b.digits[i]){
                return -1;
            }
        }
    }
    if(a.sign == 1 && b.sign == 1){
        if(a.capacity > b.capacity) return -1;
        if(a.capacity < b.capacity) return 1;
        
        int n = a.capacity;
        

        for(int i=a.capacity-1; i>=0; --i){
            if(a.digits[i] > b.digits[i])
                return -1;
            if(a.digits[i] < b.digits[i]){
                return 1;
            }
        }
    }
    return 0;
}

// returns 1 if |a|>|b|, -1 if |a|<|b|, 0 if |a|=|b|
int compareBigIntAbs(BigInt a, BigInt b)
{
    
    if(a.capacity > b.capacity) return 1;
    if(a.capacity < b.capacity) return -1;
   
    int n = a.capacity;

    for(int i=a.capacity-1; i>=0; --i){
        if(a.digits[i] > b.digits[i])
            return 1;
        if(a.digits[i] < b.digits[i]){
            return -1;
        }
    }
    return 0;
}

void freeBigInt(BigInt a)
{
    free(a.digits);
}

void copyBigInt(BigInt* destination, BigInt source)
{
    destination->sign = source.sign;
    if(destination->digits == source.digits){
        return;
    }

    destination->capacity = source.capacity;
    free(destination->digits);
    destination->digits = (int*)malloc(destination->capacity*sizeof(int));

    for(int i=0; i < destination->capacity; ++i){
        destination->digits[i] = source.digits[i];
    }

}