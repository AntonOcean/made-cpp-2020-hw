#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


#define SIGN 0x8000000000000000
#define EXPONENT 0x7FF0000000000000
#define FRACTION 0x000FFFFFFFFFFFFF
#define FRACTION_LAST_BIT 0x0008000000000000

/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64 (double number) {
    return *((uint64_t *)(&number));
}


/**
 * Checkers here:
 */

bool checkForPlusZero (uint64_t number) {
    return !number;
}

bool checkForMinusZero (uint64_t number) {
    return number == SIGN;
}

bool checkForPlusInf (uint64_t number) {
    return number == EXPONENT;
}

bool checkForMinusInf (uint64_t number) {
    return number == SIGN + EXPONENT;
}

bool checkForPlusNormal (uint64_t number) {
    uint64_t exponent = number & EXPONENT;
    uint64_t sign = number & SIGN;
    return !sign && 0 < exponent && exponent < EXPONENT;
}

bool checkForMinusNormal (uint64_t number) {
    uint64_t exponent = number & EXPONENT;
    uint64_t sign = number & SIGN;
    return sign && 0 < exponent && exponent < EXPONENT;
}

bool checkForPlusDenormal (uint64_t number) {
    uint64_t exponent = number & EXPONENT;
    uint64_t fraction = number & FRACTION;
    uint64_t sign = number & SIGN;
    return !sign && !exponent && fraction;
}

bool checkForMinusDenormal (uint64_t number) {
    uint64_t exponent = number & EXPONENT;
    uint64_t fraction = number & FRACTION;
    uint64_t sign = number & SIGN;
    return sign && !exponent && fraction;
}

bool checkForSignalingNan (uint64_t number) {
    uint64_t exponent = number & EXPONENT;
    uint64_t fraction = number & FRACTION;
    return exponent == EXPONENT && 0 < fraction && fraction <= FRACTION - FRACTION_LAST_BIT;
}

bool checkForQuietNan (uint64_t number) {
    uint64_t exponent = number & EXPONENT;
    return exponent == EXPONENT && number & FRACTION_LAST_BIT;
}


void classify (double number) {
    if (checkForPlusZero(convertToUint64(number))) {
        printf("Plus zero\n");
    }

    else if (checkForMinusZero(convertToUint64(number))) {
        printf("Minus zero\n");
    }

    else if (checkForPlusInf(convertToUint64(number))) {
        printf("Plus inf\n");
    }

    else if (checkForMinusInf(convertToUint64(number))) {
        printf("Minus inf\n");
    }

    else if (checkForPlusNormal(convertToUint64(number))) {
        printf("Plus normal\n");
    }

    else if (checkForMinusNormal(convertToUint64(number))) {
        printf("Minus normal\n");
    }

    else if (checkForPlusDenormal(convertToUint64(number))) {
        printf("Plus Denormal\n");
    }

    else if (checkForMinusDenormal(convertToUint64(number))) {
        printf("Minus Denormal\n");
    }

    else if (checkForSignalingNan(convertToUint64(number))) {
        printf("Signailing NaN\n");
    }

    else if (checkForQuietNan(convertToUint64(number))) {
        printf("Quiet NaN\n");
    }

    else {
        printf("Error.\n");
    }
}
