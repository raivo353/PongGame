
#include <bur/plctypes.h>
#include "CommonTypes.h"
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

#define OUT1_BITMASK 0x1
#define OUT2_BITMASK 0x2

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
		sensors[i]->IO.OUT1 = sensors[i]->IO.SensorInfo & OUT1_BITMASK;
		sensors[i]->IO.OUT2 = (sensors[i]->IO.SensorInfo & OUT2_BITMASK) >> 1;
		sensors[i]->STS.BallDetected = sensors[i]->IO.OUT1 && !sensors[i]->IO.OUT2;
		
		sensors[i]->STS.AlarmActiveColour = GREEN_COLOUR;
		if(sensors[i]->STS.AlarmActive)
		{
			sensors[i]->STS.AlarmActiveColour = RED_COLOUR;
		}

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
