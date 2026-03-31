
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif

#define OVERLOAD 32760
#define UNDERLOAD -32760
#define SHIFT_BYTE 8
#define NUM_SENSORS 3

/* TODO: Add your comment here */
void FB_DistanceSensor(struct FB_DistanceSensor* inst)
{
	/*TODO: Add your code here*/
	UDT_DistanceSensor* sensors[NUM_SENSORS] = 
	{
		inst->DistanceSensorLeft,
		inst->DistanceSensorMiddle,
		inst->DistanceSensorRight
	};

	int i;
	for(i = 0; i < NUM_SENSORS; i++)
	{
		sensors[i]->STS.Distance = (INT)((sensors[i]->IO.DataMSB << SHIFT_BYTE) | sensors[i]->IO.DataLSB);
		
		if(sensors[i]->STS.Distance == OVERLOAD)
		{
			sensors[i]->STS.TooFar = 1;
			sensors[i]->STS.TooClose = 0;
			sensors[i]->ALM.OutOfBounds = 1;
		}
		else if(sensors[i]->STS.Distance == UNDERLOAD)
		{
			sensors[i]->STS.TooClose = 1;
			sensors[i]->STS.TooFar = 0;
			sensors[i]->ALM.OutOfBounds = 1;
		}
		else
		{
			sensors[i]->STS.TooClose = 0;
			sensors[i]->STS.TooFar = 0;
			sensors[i]->ALM.OutOfBounds = 0;
		}
		
		
	}
}
