// Eratosthenes algorithm : finds out the prime numbers below N -> [2, N] 
#include<stdio.h>
#include <iostream>
#include "BitArray.h"

#define PRIME false
#define COMPOSITE true

typedef unsigned long long ull_int;
const ull_int N = 20000;
//by default all other values will be 0 ( false <=> PRIME )
//bool sieve[N] = { PRIME, };

//
BitArray sieve(N);
//

//just outputs all prime numbers
void print_primes() {

	for (ull_int i = 2; i < N; i++)
		if (sieve[i] == PRIME)
			printf("%d is a prime!\n", i);
}
//the algorithm is simple, for each prime number,
//mark all numbers which have this number as a multiplier  
void eratosthenes_sieve() {

	for (ull_int i = 2; i <= N; i++)
		if (sieve[i] == PRIME)
			for (ull_int j = i * i; j <= N; j += i) //the start value and the step are important
				//sieve[j] = COMPOSITE;
				sieve.SetBit(j, COMPOSITE);


	print_primes();
}

int main() {

	eratosthenes_sieve();

//	int size = 100;
//
//	BitArray a(size);
//
//	for (size_t i = 0; i < size; i++)
//	{
//		a.SetBit(i, i % 2 == 0);
//	}
//	
//	for (size_t i = 0; i < size; i++)
//	{
//		std::cout<<a[i];
//	}
//
//	a.PrintDebug();


	return 0;
}