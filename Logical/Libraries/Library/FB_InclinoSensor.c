/*********************************************************************************
 * Copyright: MyAutomation-IT
 * Author:    raivo 
 * Created:   April 22, 2026/5:57 PM 
 *********************************************************************************/ 
#include <bur/plctypes.h>
#include <standard.h>
#include "CommonTypes.h"
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif

#define TO_DEGREES 100
#define SHIFT_BYTE 8

#define InclinoSensor inst->InclinoSensor

void FB_InclinoSensor(struct FB_InclinoSensor* inst)
{
	//Combining MSB and LSB with bitwise operators to show the value. Dividing by 100 to convert to degrees and explicit casting to float to show CurrentAngle as accurate as possible.
	InclinoSensor->STS.CurrentAngle = (float)((INT)((InclinoSensor->IO.DataMSB << SHIFT_BYTE) | InclinoSensor->IO.DataLSB)) / TO_DEGREES;
	
	InclinoSensor->STS.AlarmActiveColour = GREEN_COLOUR;
	if(InclinoSensor->STS.AlarmActive)
	{
		InclinoSensor->STS.AlarmActiveColour = RED_COLOUR;
	}
	InclinoSensor->IO.SetCenterPoint = 7;
	if(InclinoSensor->CS.SetCenterPoint)
	{
    	
		InclinoSensor->IO.SetCenterPoint = 3;
	}
}
