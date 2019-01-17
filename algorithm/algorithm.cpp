// algorithm.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "algorithm.h"
#include <cstdio>


// Core function of generate key.
static UINT32 GenKeyFromSeed(UINT32 Seed, UINT32 Variant, UINT32 SAAlg)
{
	UINT32 Key = 0UL;

	if (LEVEL_EXTEND == SAAlg)
	{
		Key = Seed;	// Add security access function here.
	}
	else if (LEVEL_PROGRAM == SAAlg)
	{
		Key = Seed;	// Add security access function here.
	}
	else if (LEVEL_EOL == SAAlg)
	{
		Key = Seed;	// Add security access function here.
	}
	else
	{
		Key = 0xEEEEEEEEUL;
	}

	return Key;
}

/// Export function for 'ETS'
SA_API BOOL WINAPIV Seed2Key(ULONG VendorCode, BYTE* Seed, UINT SeedSize, BYTE* Key, UINT* KeySize, USHORT SAAlg)
{
	UINT32 tempSeed = 0;
	UINT32 tempKey = 0;

	SeedSize = SeedSize;

	tempSeed = (UINT32)Seed[0] << 24 | (UINT32)Seed[1] << 16 | (UINT32)Seed[2] << 8 | (UINT32)Seed[3];
	tempKey = GenKeyFromSeed(tempSeed, VendorCode, SAAlg);

	Key[3] = (BYTE)(tempKey & 0xff);
	Key[2] = (BYTE)((tempKey & 0xff00) >> 8);
	Key[1] = (BYTE)((tempKey & 0xff0000) >> 16);
	Key[0] = (BYTE)((tempKey & 0xff000000) >> 24);

	*KeySize = 4;

	return true;
}

/// Export function for 'CANoe'
SA_API VKeyGenResultEx GenerateKeyEx(
	const unsigned char*  iSeedArray,     /* Array for the seed [in] */
	unsigned short          iSeedArraySize, /* Length of the array for the seed [in] */
	const unsigned int    iSecurityLevel, /* Security level [in] */
	const char*           iVariant,       /* Name of the active variant [in] */
	unsigned char*        ioKeyArray,     /* Array for the key [in, out] */
	unsigned int          iKeyArraySize,  /* Maximum length of the array for the key [in] */
	unsigned int&         oSize           /* Length of the key [out] */
)
{
	unsigned int Seed;
	unsigned int Key;
	unsigned int Variant = 0;
	unsigned int SAAlg = 0;

	if (iSeedArraySize>iKeyArraySize)
		return KGRE_BufferToSmall;

	Seed = ((unsigned int)iSeedArray[0] << 24)
		| ((unsigned int)iSeedArray[1] << 16)
		| ((unsigned int)iSeedArray[2] << 8)
		| ((unsigned int)iSeedArray[3]);

	if (iVariant[0] == '0')
	{
		Variant = 0;
	}

	Key = GenKeyFromSeed(Seed, Variant, iSecurityLevel);

	ioKeyArray[0] = (unsigned char)(Key >> 24);
	ioKeyArray[1] = (unsigned char)(Key >> 16);
	ioKeyArray[2] = (unsigned char)(Key >> 8);
	ioKeyArray[3] = (unsigned char)(Key);
	oSize = iSeedArraySize;

	return KGRE_Ok;
}

// For "Vehicle Spy3"
SA_API bool __stdcall ES_CalculateKeyFromSeed(unsigned char ucSecurityLevel,
	int iSeedKeySize, int iExtraBytesSize,
	unsigned char* pucSeed, unsigned char* pucKey,
	unsigned char* pucExtraBytes)
{
	UINT32 tempSeed = 0;
	UINT32 tempKey = 0;
	UINT32 SAAlg = 0;

	tempSeed = (UINT32)pucSeed[0] << 24 | (UINT32)pucSeed[1] << 16 | (UINT32)pucSeed[2] << 8 | (UINT32)pucSeed[3];

	tempKey = GenKeyFromSeed(tempSeed, 0, SAAlg);

	pucKey[3] = (BYTE)(tempKey & 0xff);
	pucKey[2] = (BYTE)((tempKey & 0xff00) >> 8);
	pucKey[1] = (BYTE)((tempKey & 0xff0000) >> 16);
	pucKey[0] = (BYTE)((tempKey & 0xff000000) >> 24);

	return true;
}
