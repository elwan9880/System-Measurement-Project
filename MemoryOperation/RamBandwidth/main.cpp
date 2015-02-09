//
//  main.cpp
//  RamBandwidth
//
//  Created by Shao ChunTse on 12/6/14.
//  Copyright (c) 2014 Shao ChunTse. All rights reserved.
//

#include <Windows.h>
#include <iostream>
#include <time.h>
#include <stdint.h>
#include <intrin.h>
#include <cmath>
#include <ctime>
#include <cstdlib>

#define KILO 1024
#define MEGA 1048576
#define GIGA 1073741824
#define CACHELINE 64
#define TICKSPERSEC 3292140000
#define TESTNUM 10

void flushCache()
{
	uint8_t * cache = (uint8_t *)malloc(sizeof(uint8_t) * (9 * MEGA)); // L1 + L2 + L3 ~ 9MB
	free(cache);
}

double evalRamBandwidth(int arraySize, int memOp) {

	uint8_t * array = (uint8_t *)malloc(sizeof(uint8_t) * arraySize);
    
	double startTick = 0;
	double endTick = 0;
	double tickCount = 0;

	// fill up array with random number
	srand((unsigned int)time(NULL));
	for (int i = 0; i < arraySize; i ++)
	{
		array[i] = (uint8_t)(rand() % 32);
	}

	// enforce array to swap to memory
	flushCache();

	long long unsigned int a = 0;

	if (memOp == 1)
	{
		// start counter for read
		startTick = __rdtsc();

		for (int i = 0; i < arraySize; i += CACHELINE)
		{
			a += array[i];
		}

		// stop counter for read
		endTick = __rdtsc();
	} 
	else if (memOp == 2)
	{
		// start counter for write
		startTick = __rdtsc();

		for (int i = 0; i < arraySize; i += CACHELINE)
		{
			array[i] = (uint8_t)((sizeof(uint8_t) - i) % sizeof(uint8_t));
		}

		// stop counter write
		endTick = __rdtsc();
	}
	else
	{
		printf("memOp is wrong.\n");
	}

	tickCount = endTick - startTick;
	double ramBandwidth = (arraySize / MEGA) / (tickCount / TICKSPERSEC);

	free(array);
	return ramBandwidth;
}

int main()
{
	SetThreadAffinityMask(GetCurrentThread(), 2);

	// for read, memOp = 1;
	printf("--- FOR READ ---\n");
	double ramBandwidth = 0;

	for (int arraySize = 2 * MEGA; arraySize <= 16 * MEGA; arraySize = arraySize * 2)
	{
		for (int i = 0; i < TESTNUM; i++)
		{
			ramBandwidth += evalRamBandwidth(arraySize, 1);
		}
		printf("For size of array %d-megabyte: %f MB / Sec.\n", arraySize / MEGA, ramBandwidth / TESTNUM);
		ramBandwidth = 0;
	}

	// for read, memOp = 2;
	printf("--- FOR WRITE ---\n");
	for (int arraySize = 2 * MEGA; arraySize <= 16 * MEGA; arraySize = arraySize * 2)
	{
		for (int i = 0; i < TESTNUM; i++)
		{
			ramBandwidth += (evalRamBandwidth(arraySize, 2) / TESTNUM);
		}
		printf("For size of array %d-megabyte: %f MB / Sec.\n", arraySize / MEGA, ramBandwidth);
		ramBandwidth = 0;
	}

	system("PAUSE");
	return 0;
}
