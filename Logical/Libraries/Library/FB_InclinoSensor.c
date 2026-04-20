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


/* TODO: Add your comment here */
void FB_InclinoSensor(struct FB_InclinoSensor* inst)
{
	/*TODO: Add your code here*/
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
