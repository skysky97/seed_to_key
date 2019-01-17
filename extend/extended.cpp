// sample.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../algorithm/algorithm.h"


typedef unsigned int uint32;
typedef unsigned char uint8;



int main()
{
	uint32 Seed;
	uint32 Key;
	int result;

	printf("Security Access Key Calculator for project: %s\n", PROJECT_NAME);
	printf("Security Access Level: 0x%02X\n", LEVEL_EXTEND);

	while (1)
	{
		printf("\nSeed: ");
		result = scanf_s("%X", &Seed);
		if (1 == result)
		{
			//printf("%08X\n", Seed);
			uint8 temp[4];
			uint8 temp_key[4];
			UINT keysize = 4;
			temp[0] = (uint8)(Seed >> 24);
			temp[1] = (uint8)(Seed >> 16);
			temp[2] = (uint8)(Seed >> 8);
			temp[3] = (uint8)(Seed);
			
			Seed2Key(0, temp, 4, temp_key, &keysize, LEVEL_EXTEND);

			Key = ((uint32)temp_key[0]) << 24 |
				((uint32)temp_key[1]) << 16 |
				((uint32)temp_key[2]) << 8 |
				((uint32)temp_key[3]);

			printf("Key: %08X\n", Key);
		}
		else
		{
			printf(">>Input invalid\n");
			int ch;
			while ((ch = fgetc(stdin)) != EOF && ch != '\n');
		}
	}
    return 0;
}

