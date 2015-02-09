//
//  main.cpp
//  RamAccessTime
//
//  Created by Shao ChunTse on 12/3/14.
//  Copyright (c) 2014 Shao ChunTse. All rights reserved.
//

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <ctime>
#include <intrin.h>

#define KILO 1024
#define MEGA 1048576
#define SIZE_TESTCASENUM 16 // from 1KB to 64MB
#define STRIDESIZE_TESTCASENUM 7 // from 16B to 1024B
#define LOOPCOUNTS 10000000

double evalRamAccessTime(int size, int strideSize)
{
	SetThreadAffinityMask(GetCurrentThread(), 2);

    uint8_t * b = (uint8_t *)malloc(sizeof(uint8_t) * size); // total array size = SIZE x Byte
	srand((unsigned int)time(NULL));
	for (int i = 0; i < size; i++)
	{
		// random all entries in array b[]
		b[i] = rand() % sizeof(uint8_t);
	}

	int *c = (int *)b; // let count become easier
    
	double startTick = 0;
	double endTick = 0;
    double tickCount = 0;
	long int temp = 0;
	long int location = 0;
    
    for (int i = 0; i < LOOPCOUNTS; i++)
    {
		int cpuinfo[4];
		// start cycleCounter
		startTick = __rdtsc();

		// enforce temp can not be optimized
		__cpuid(cpuinfo, 0);
		temp += c[location];
		__cpuid(cpuinfo, 0);

		// stop tickCounter and cummulate it
		endTick = __rdtsc();
		tickCount += endTick - startTick;

		// eliminate the cpuid overhead
		startTick = __rdtsc();
		__cpuid(cpuinfo, 0);
		__cpuid(cpuinfo, 0);
		endTick = __rdtsc();
		tickCount -= endTick - startTick;

		location += strideSize / sizeof(int);
		location = location % (size / sizeof(int));
    }

	double ramAccessTicks = (double)tickCount / LOOPCOUNTS;
    
    free(b);
    
    return ramAccessTicks;
}

int main(){
    int size[SIZE_TESTCASENUM];  // size of array in byte
    int strideSize[STRIDESIZE_TESTCASENUM]; // size of array in byte
    
    for(int i = 0; i < SIZE_TESTCASENUM; i++)
    {
        size[i] = pow(2, i) * KILO; //from 2^0 KILO to 2^(SIZE_TESTCASENUM-1) KILO
    }
    
    for(int i = 0; i < STRIDESIZE_TESTCASENUM; i++)
    {
        strideSize[i] = pow(2, i + 4); //from 2^4 to 2^(SIZE_TESTCASENUM+3)
    }
    
   for (int i = 0; i < SIZE_TESTCASENUM; i++)
    {
        for (int j = 0; j < STRIDESIZE_TESTCASENUM; j++)
		{
			double ramAccessTime = evalRamAccessTime(size[i], strideSize[j]);
			printf("Size = %dKB, StrideSize = %dB, Ram access time = %f cycles\n", size[i] / KILO, strideSize[j], ramAccessTime);
        }
    }
	system("PAUSE");
    return 0;
}
