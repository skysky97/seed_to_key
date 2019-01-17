# Introduce
This project is consist of a dll which used by CANoe/VSpy3/ETS to generate security access key automatically and a set of demo programs that use the dll to generate special keys.

- algorithm: The Dll used by CANoe/VSpy3/ETS.
- eol: A console program to generate EOL mode key.
- programe: A console program to generate programming mode key.
- extend: A console program to generate extended mode key.

# Files
**algorithm.h: Defines the prototype of export functions and security access levels.** 
  
Project settings:  
```
#define PROJECT_NAME	"Undefined Project"
#define LEVEL_EXTEND	0x01
#define LEVEL_PROGRAM	0x11
#define LEVEL_EOL		0x61
```
Prototypes:  
```
SA_API VKeyGenResultEx  GenerateKeyEx(
	const unsigned char*  ipSeedArray, unsigned short  iSeedArraySize,
	const unsigned int    iSecurityLevel, const char*   ipVariant,
	unsigned char*        iopKeyArray, unsigned int  iMaxKeyArraySize,
	unsigned int&         oActualKeyArraySize);
```
  
**algorithm.cpp:  Implementation of security access algorithm.**   
```
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
```
