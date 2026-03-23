
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif

	/*TODO: Add your code here*/
#define ACTPOSITION_TO_MM 0.0784

/* TODO: Add your comment here */
unsigned short ActPositionToMM(float ActPosition)
{
	return (UINT)((-ActPosition) * ACTPOSITION_TO_MM);
}

unsigned char SetOutputs(unsigned char digitalOutputs, plcbit ventilator, plcbit solenoid)
{
	digitalOutputs &= ~((1 << 0) | (1 << 3));
	digitalOutputs |= ((USINT)ventilator << 0) | ((USINT)solenoid << 3);

	return digitalOutputs;
}

short DistanceSensor(unsigned char DistanceMSB, unsigned char DistanceLSB)
{
	return (INT)((DistanceMSB << 8) | DistanceLSB);
}



