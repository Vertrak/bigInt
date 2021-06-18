/*//ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*
**	Filename: bigInt.h
**	Author: Vertrak
**	Date: June 16, 2021
**	Purpose: function headers for bigInt type
**	Github repository: tbd
**
**	Forewarning:
**	I am not responsible for any losses or damages incurred by this code.
**	You are not required to use this project in your code.
**	If this crashes your computer, the fault lies with you.
**	
**	PS: if you have a problem with tabs instead of spaces, sucks for you.
*///ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef BIGINT
#define BIGINT
#define LIMIT ((uint64_t) 10000000000000000000U)
#define DIGITS 19

typedef struct BI
{
	uint8_t s;
	uint64_t *n;
	uint64_t l;
}bigInt;

//Return new bigInt
bigInt* bigIntLen(uint64_t l);
bigInt* i64ToBI(int64_t n);
bigInt* u64ToBI(uint64_t n);
bigInt* strToBI(char *s);
bigInt* copyBI(bigInt *a);
void printBI(bigInt *a);
void deleteBI(bigInt **a);
//Return 0x00 for false; 0xFF for true; Relative comparisons
uint8_t greater(bigInt *a, bigInt *b);
uint8_t lesser(bigInt *a, bigInt *b);
uint8_t equal(bigInt *a, bigInt *b);
uint8_t greaterEqual(bigInt *a, bigInt *b);
uint8_t lesserEqual(bigInt *a, bigInt *b);
uint8_t magComp(uint8_t (*f)( bigInt*, bigInt*), bigInt *a, bigInt *b);
//Return pointer to new bigInt
bigInt* add(bigInt *a, bigInt *b);
bigInt* subtract(bigInt *a, bigInt *b);
bigInt* multiply(bigInt *a, bigInt *b);
bigInt* divide(bigInt *a, bigInt *b);
bigInt* modulus(bigInt *a, bigInt *b);
bigInt* power(bigInt *a, bigInt *b);
bigInt* root(bigInt *a, bigInt *b);
//Return pointer to first arguement holding new value
bigInt* assignFirst(bigInt* (*f)(bigInt*, bigInt*), bigInt *a, bigInt *b);
#endif