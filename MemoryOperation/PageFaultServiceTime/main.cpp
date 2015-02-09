//
//  main.cpp
//  PageFaultServiceTime
//
//  Created by Shao ChunTse on 11/23/14.
//  Copyright (c) 2014 Shao ChunTse. All rights reserved.
//
//  Description:
//      Estimate Page fault serivce time for ASUS N550JV
//      Must run on Windows platform

#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <intrin.h>
#include <ctime>

#define GIGA 1073741824
#define MEGA 1048576
#define KILO 1024
#define MEMORYLIMIT 700
#define CLOCKS_PER_SEC 3292140000

typedef struct node node;

int main() {

	// initilaize, fill up all main memory space
	uint8_t **array = (uint8_t **)malloc(sizeof(uint8_t *) * MEMORYLIMIT);
	for (int i = 0; i < MEMORYLIMIT; i++)
	{
		array[i] = (uint8_t *)malloc(sizeof(uint8_t) * MEGA);
	}

    for (int i = 0; i < MEMORYLIMIT; i++)
    {
		for (int j = 0; j < MEGA; j++)
		{
			array[i][j] = (i + j) % sizeof(uint8_t);
		}
    }
    
    // set clock
	double totalTicks = 0;
    
    for (int i = 0; i < MEGA; i += 4 * KILO)
    {
		double startTick = __rdtsc();
		uint8_t temp = array[0][i] + array[0][i];
		double endTick = __rdtsc();
		totalTicks += endTick - startTick;
    }
	
	printf("Ticks per page fault: %d", (totalTicks / (MEGA / 4096)));

	free(array);

	system("PAUSE");

	return 0;
}
