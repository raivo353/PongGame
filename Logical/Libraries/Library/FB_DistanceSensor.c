/*********************************************************************************
 * Copyright: MyAutomation-IT
 * Author:    raivo 
 * Created:   April 22, 2026/5:57 PM 
 *********************************************************************************/ 
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
#define DEVICE_STATUS_BITMASK 0xF0
#define SENSOR_FAILURE 4

#define BALL_MIN_DISTANCE 50
#define BALL_MAX_DISTANCE 300

void FB_DistanceSensor(struct FB_DistanceSensor* inst)
{
	/* sensor list abstraction */
	UDT_DistanceSensor* sensors[NUM_SENSORS] = 
	{
		inst->DistanceSensorLeft,
		inst->DistanceSensorMiddle,
		inst->DistanceSensorRight
	};

	int i;
	for(i = 0; i < NUM_SENSORS; i++)
	{
		/* combine MSB/LSB */
		INT Distance = ((sensors[i]->IO.DataMSB << SHIFT_BYTE) | sensors[i]->IO.DataLSB);

		/* clamp invalid sensor range */
		if(Distance >= OVERLOAD || Distance <= UNDERLOAD)
		{
			sensors[i]->STS.Distance = 0;
		}
		else
		{
			sensors[i]->STS.Distance = Distance;
		}
		
		/* decode sensor IO bits */
		sensors[i]->IO.OUT1 = sensors[i]->IO.SensorInfo & OUT1_BITMASK;
		sensors[i]->IO.OUT2 = (sensors[i]->IO.SensorInfo & OUT2_BITMASK) >> 1;
		sensors[i]->STS.BallDetected = sensors[i]->STS.Distance >= BALL_MIN_DISTANCE && sensors[i]->STS.Distance <= BALL_MAX_DISTANCE;
		sensors[i]->STS.DeviceStatus = (sensors[i]->IO.SensorInfo & DEVICE_STATUS_BITMASK) >> 4; 
		
		/* alarm indication */
		sensors[i]->STS.AlarmActiveColour = sensors[i]->STS.AlarmActive ? RED_COLOUR : GREEN_COLOUR;

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

		if(sensors[i]->STS.DeviceStatus == SENSOR_FAILURE || sensors[i]->ALM.OutOfBounds)
		{
			sensors[i]->STS.AlarmActive = 1;
		}
		else if(sensors[i]->STS.DeviceStatus == 0)
		{
			sensors[i]->STS.AlarmActive = 0;
		}
	}



}
