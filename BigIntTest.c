#include "bigInt.h"
#include <stdint.h>
#include <stdio.h>

int main()
{
	bigInt *w = strToBI("123456789123456789123456789123456789");
	printBI(w);
	printf("\n");
	deleteBI(&w);
	w = strToBI("-123456789123456789123456789123456789");
	printBI(w);
	printf("\n");
	deleteBI(&w);
	w = strToBI("+123456789123456789123456789123456789");
	printBI(w);
	printf("\n");
	deleteBI(&w);
	bigInt *x = u64ToBI((uint64_t) 123456789);
	printBI(x);
	printf("\n");
	bigInt *y = copyBI(x);
	printBI(y);
	printf("\n");
	y->s = 0xFF;
	printBI(y);
	printf("\n");
	bigInt *z = i64ToBI((int64_t) -1);
	printBI(z);
	printf("\n");
	deleteBI(&z);
	uint8_t b = 0x00;
	printf("Current bool value: %x\n", b);	//should be 0x00
	b = greater(x, y);
	printf("x > y: %x\n", b);	//should be 0xFF
	b = greater(y, x);
	printf("y > x: %x\n", b);	//should be 0x00
	b = lesser(x, y);
	printf("x < y: %x\n", b);	//should be 0x00
	b = lesser(y, x);
	printf("y < x: %x\n", b);	//should be 0xFF
	b = equal(x, y);
	printf("x = y: %x\n", b);	//should be 0x00
	b = equal(y, x);
	printf("y = x: %x\n", b);	//should be 0x00
	b = greaterEqual(x, y);
	printf("x >= y: %x\n", b);	//should be 0xFF
	b = greaterEqual(y, x);
	printf("y >= x: %x\n", b);	//should be 0x00
	b = lesserEqual(x, y);
	printf("x <= y: %x\n", b);	//should be 0x00
	b = lesserEqual(y, x);
	printf("y <= x: %x\n", b);	//should be 0xFF
	deleteBI(&x);
	deleteBI(&y);
	return 0;
}