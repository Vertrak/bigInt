/*//ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*
**	Filename: bigInt.c
**	Author: Vertrak
**	Date: June 16, 2021
**	Purpose: arithmetic functions for bigInt type
**	Github repository: tbd
**
**	Forewarning:
**	I am not responsible for any losses or damages incurred by this code.
**	You are not required to use this project in your code.
**	If this crashes your computer, the fault lies with you.
**	
**	PS: if you have a problem with tabs instead of spaces, sucks for you.
*///ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*ಠ_ಠ*

#include "bigInt.h"

/*
**	Creates new BigInt with array length L
**	Takes care of zeroed out bigint mem allocation
*/
bigInt* bigIntLen(uint64_t l)
{
	//allocate new bigint
	bigInt *b = (bigInt*) malloc(sizeof(bigInt));
	if(!b)
	{
		printf("Out of memory!\n");
		return NULL;
	}
	//Allocate new int array of 0s
	b->n = (uint64_t*) calloc(l, sizeof(uint64_t));
	if(!b->n)
	{
		printf("Out of memory!\n");
		free(b);
		return NULL;
	}
	//Finish setting new bigInt to 0
	b->l = l;
	b->s = 0x00;
	return b;
}

//Convert int64_t to bigInt
bigInt* i64ToBI(int64_t n)
{
	//Allocate new bigint; Check for failed allocation
	bigInt *b = bigIntLen(1);
	if(!b) return NULL;
	//Set sign and array; Length set by bigIntLen
	b->s = ((n >> 63) & 0x1) ? 0xFF : 0x00;
	b->n[0] = n < 0 ? -n : n;
	return b;
}

//Convert uint64_t to bigInt
bigInt* u64ToBI(uint64_t n)
{
	bigInt *b;
	//Allocate memory only as necessary
	if(n < LIMIT)
	{
		//Allocate new bigint; Check for failed allocation
		b = bigIntLen(1);
		if(!b) return NULL;	
	}
	else
	{
		//Allocate new bigint; Check for failed allocation
		b = bigIntLen(2);
		if(!b) return NULL;
		b->n[1] = 1;
	}
	b->n[0] = n % LIMIT;
	return b;
}

//Convert string to bigInt; Returns bigInt of 0 if invalid input provided
bigInt* strToBI(char *s)
{
	bigInt *b;	//end result
	uint64_t c;	//counter
	uint8_t sh;	//shift bool
	c = sh = (s[0] == '+' || s[0] == '-') ? 1 : 0;	//Check for sign character
	while(s[c] != '\0')	//Loop through unspecified length string
	{
		if(s[c] < 48 || s[c] > 57)	//check for non numeric characters
		{
			printf("Invalid string!\nAttempting to return bigInt of 0.\n");
			return bigIntLen((int64_t) 1);
		}
		c++;
	}
	//calculate array length and create BI; Check for failed allocation
	b = bigIntLen((c - sh) / DIGITS + ((c - sh) % DIGITS ? 1 : 0));
	if(!b) return NULL;
	b->s = (sh && s[0] == '-') ? 0xFF : 0x00;	//Set sign
	uint64_t d;	//digit counter
	uint64_t o = c - sh;	//offset count
	uint64_t m = 1;	//digit multiplier
	for(d = 0; d < o % DIGITS; d++)	//Get initial multiplier
		m *= 10;
	for(d = sh; d < c; d++)	//Process string most significant digit to least
	{
		b->n[(o-d)/DIGITS] += ((uint64_t) s[d] - 48) * m;
		m /= 10;
		if(!m) m = LIMIT / 10;	//reset multiplier
	}
	return b;
}

//Returns duplicate of provided bigInt
bigInt* copyBI(bigInt *a)
{
	bigInt *c = bigIntLen(a->l);
	c->s = a->s;
	for(c->l = 0; c->l < a->l; c->l++)
		c->n[c->l] = a->n[c->l];
	return c;
}

//Displays bigInt in terminal
void printBI(bigInt *a)
{
	if(a->s)	//Check for negative sign
		printf("-");
	uint64_t c = a->l;
	while(c) printf("%ld", a->n[--c]);	//Print one uint64_t at a time
}

//Frees bigInt provided
void deleteBI(bigInt **a)
{
	free((*a)->n);	//Always free uint64_t array first
	free(*a);	//Then you can free bigInt
	*a = NULL;	//Make sure it doesn't point to anything!
}

//Checks for a > b
uint8_t greater(bigInt *a, bigInt *b)
{
	//Check sign
	if(a->s != b->s)
		return a->s ? 0x00 : 0xFF;
	//Check length
	if(a->l != b->l)
		return a->s ? (a->l < b->l ? 0xFF : 0x00) : (a->l > b->l ? 0xFF : 0x00);
	//Compare piece by piece
	uint64_t c = a->l - 1;
	while(c && a->n[c] == b->n[c]) c--;
	//Return results based on sign
	if(a->s)
		return a->n[c] < b->n[c] ? 0xFF : 0x00;
	return a->n[c] > b->n[c] ? 0xFF : 0x00;
}

//Checks for a < b
uint8_t lesser(bigInt *a, bigInt *b)
{
	//Check for sign
	if(a->s != b->s)
		return b->s ? 0x00 : 0xFF;
	//Check for length
	if(a->l != b->l)
		return a->s ? (a->l > b->l ? 0xFF : 0x00) : (a->l < b->l ? 0xFF : 0x00);
	//Check piece by piece
	uint64_t c = a->l-1;
	while(c && a->n[c] == b->n[c]) c--;
	//Return results based on sign
	if(a->s)
		return a->n[c] > b->n[c] ? 0xFF : 0x00;
	return a->n[c] < b->n[c] ? 0xFF : 0x00;
}

//Checks for a == b
uint8_t equal(bigInt *a, bigInt *b)
{
	//Check sign and length
	if(a->s != b->s || a->l != b->l)
		return 0x00;
	//Check piece by piece and return results
	uint64_t c = a->l-1;
	while(c && a->n[c] == b->n[c]) c--;
	return a->n[c] == b->n[c] ? 0xFF : 0x00;
}

//Checks for a >= b
uint8_t greaterEqual(bigInt *a, bigInt *b)
{
	//Check sign
	if(a->s != b->s)
		return a->s ? 0x00 : 0xFF;
	//Check length
	if(a->l != b->l)
		return a->s ? (a->l < b->l ? 0xFF : 0x00) : (a->l > b->l ? 0xFF : 0x00);
	//Check piece by piece
	uint64_t c = a->l-1;
	while(c && a->n[c] == b->n[c]) c--;
	//Return results based on sign
	if(a->s)
		return a->n[c] > b->n[c] ? 0x00 : 0xFF;
	return a->n[c] < b->n[c] ? 0x00 : 0xFF;
}

//Checks for a <= b
uint8_t lesserEqual(bigInt *a, bigInt *b)
{
	//Check sign
	if(a->s != b->s)
		return b->s ? 0x00 : 0xFF;
	//Check length
	if(a->l != b->l)
		return a->s ? (a->l > b->l ? 0xFF : 0x00) : (a->l < b->l ? 0xFF : 0x00);
	//Check piece by piece
	uint64_t c = a->l-1;
	while(c && a->n[c] == b->n[c]) c--;
	//Return results based on sign
	if(a->s)
		return a->n[c] < b->n[c] ? 0x00 : 0xFF;
	return a->n[c] > b->n[c] ? 0x00 : 0xFF;
}

//Checks for |a| comp |b|; Requires comparison function pointer
uint8_t magComp(uint8_t (*f)(bigInt*,bigInt*), bigInt *a, bigInt *b)
{
	//Save signs
	uint8_t sa = a->s;
	uint8_t sb = b->s;
	uint8_t r;
	//Make positive and compare
	a->s = 0x00;
	b->s = 0x00;
	r = f(a, b);
	//Restore signs and result
	a->s = sa;
	b->s = sb;
	return r;
}

//Returns a + b
bigInt* add(bigInt *a, bigInt *b)
{
	//return as is if a or b is 0
	if(a->l < 2 && !a->n[0])
		return copyBI(b);
	if(b->l < 2 && !b->n[0])
		return copyBI(a);
	bigInt *c, *s, *l;	//New, smaller, and bigger bigInt pointers
	//Set poiters to smaller and larger bigInts
	if(magComp(&greater, a, b))
	{
		s = a;
		l = b;
	}
	else
	{
		s = b;
		l = a;
	}
	//Allocate new bigInt; Check for failed allocation
	c = bigIntLen(l->l + 1);
	if(!c) return NULL;
	uint64_t i;
	if(a->s == b->s)	//If signs equal, perform addition algorithm
	{
		c->s = l->s;	//Set resulting sign
		//Add a and b together with overflow 
		for(i = 0; i < s->l; i++)
		{
			c->n[i] += l->n[i] + s->n[i];
			if(c->n[i] >= LIMIT || (c->n[i] < l->n[i] && c->n[i] < s->n[i]))
			{
				c->n[i] -= LIMIT;
				c->n[i+1] += 1;
			}
		}
		//Add the rest of l, compensating for overflow
		for(i = s->l; i < c->l; i++)
		{
			c->n[i] += l->n[i];
			if(c->n[i] > LIMIT)
			{
				c->n[i] -= LIMIT;
				c->n[i+1] += 1;
			}
		}
	}
	else	//Perform subtraction algorithm
	{
		c->s = l->s;
		//Subtract s from l with overflow
		for(i = 0; i < s->l; i++)
		{
			c->n[i] += l->n[i] - s->n[i];
			if(c->n[i] > LIMIT || (c->n[i] > l->n[i] && c->n[i] > s->n[i]))
			{
				c->n[i] += LIMIT;
				c->n[i+1] -= 1;
			}
		}
		//Add rest of l, compensating for overflow
		for(i = s->l; i < l->l; i++)
		{
			c->n[i] += l->n[i];
			if(c->n[i] > LIMIT)
			{
				c->n[i] += LIMIT;
				c->n[i+1] -= 1;
			}
		}
	}
	//Find out how many cells are occupied
	i = c->l;
	while(!c->n[--i]);
	//Remove excess cells
	uint64_t* t = (uint64_t*) realloc(c->n, sizeof(uint64_t) * (i + 1));
	if(!t)
	{
		printf("Out of memory! Excess cells could not be removed.");
		return c;
	}
	c->n = t;
	return c;
}
/*
bigInt* subtract(bigInt *a, bigInt *b)
{
	//return as is if subtracting 0
	if(b->l < 2 && !b->n[0])
		return copyBI(a);
	//return negative b if subtracting from 0
	if(a->l < 2 && !a->n[0])
	{
		bigInt *n =  copyBI(b);
		n->s = n->s ? 0x00 : 0xFF;
		return n;
	}
	//alg goes here	
}

bigInt* multiply(bigInt *a, bigInt *b)
{
	if(a->l < 2)
	{
		//return 0 if arguement of 0
		if(!a->n[0])
			return bigIntLen((uint64_t) 1);
		//return n as is if arguement of 1
		if(a->n[0] == 1)
		{
			bigInt *n = copyBI(b);
			//flip sign if arguement of -1
			if(a->s)
				n->s = n->s ? 0x00 : 0xFF;
			return n; 
		}
	}
	if(b->l < 2)
	{
		//return 0 if arguement of 0
		if(!b->n[0])
			return bigIntLen((uint64_t) 0);
		//return n as is if arguement of 1
		if(b->n[0] == -1)
		{
			bigInt *n = copyBI(a);
			//flip sign if arguement of -1
			if(b->s)
				n->s = n->s ? 0x00 : 0xFF;
			return n;
		}		
	}

}

bigInt* divide(bigInt *a, bigInt *b)
{
	//spit out error if b is 0
	if(b->l < 2 && !b->n[0])
	{
		printf("Divide by zero!\nReturning original value.\n");
		return a;
	}
	//return as is if dividing by 1
	if(b->l < 2 && b->n[0] == 1)
		return copyBI(a);
	//return 0 if b is greater than a
	if(greater(a, b))
		return i64ToBI((int64_t) 0);
	//return 1 if b and a are equal
	if(equal(a, b))
		return i64ToBI((int64_t) 1);
	//alg goes here
}

bigInt* modulus(bigInt *a, bigInt *b)
{
	bigInt* c;
	//spit out error if b is 0
	if(b->l == 1 && b->n[0] == 0)
	{
		printf("Divide by 0 error!");
		return NULL;
	}
	//return 0 if b is 1
	if(b->l == 1 && b->n[0] == 1)
		return i64ToBI((int64_t) 0);
	//return a if b is greater
	if(greater(a, b))
		return copyBI(a);
	//alg goes here
}

bigInt* power(bigInt *a, bigInt *b)
{
	bigInt* c;
	//return 0 if power is less than 0
	if(b->s)
		return i64ToBI((int64_t) 0);
	//return 1 if power is 0
	if(b->l == 1 && b->n[0] == 0)
		return i64ToBI((int64_t) 1);
	c = copyBI(a);
	if(!c) return NULL;
	//return as is if power is 1
	if(b->l == 1 && b->n[0] == 1)
		return c;
	//alg goes here
}

bigInt* root(bigInt *a, bigInt *b)
{
	bigInt* c;
	//return 0 if root index less than 0
	if(b->s)
		return i64ToBI((int64_t) 0);
	//spit out error if root index is 0
	if(b->l == 1 && b->n[0] == 0)
	{
		printf("Index must be greater than 0!");
		return NULL;
	}
	//spit out error if b even and a negative
	if(!(b->n[0] % 2) && a->s)
	{
		printf("Number must be positive for even roots!");
		return NULL;
	}
	//return as is if root order 1
	if(b->l == 1 && b->n[0] == 1)
		return copyBI(a);
	//return +/-1 if root order greater than base
	uint8_t s = a->s;
	a->s = 0x00;
	if(greaterEqual(b, a))
	{
		a->s = s;
		return i64ToBI((int64_t) (a->s ? -1 : 1));
	}
	a->s = s;
	//alg goes here
}
*/
//Equivalent of a = a (op) b but without the memory leak it would incur
bigInt* assignFirst(bigInt* (*f)(bigInt*,bigInt*), bigInt *a, bigInt *b)
{
	//Atttempt operation; Check for allocation failure
	bigInt *c = f(a, b);
	if(!c)
	{
		printf("Function call failed!\nReturning original value.\n");
		return a;
	}
	deleteBI(&a);
	a = c;
	return a;
}