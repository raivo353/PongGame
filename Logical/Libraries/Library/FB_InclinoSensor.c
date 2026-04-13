#include <bur/plctypes.h>
#include <standard.h>
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

_LOCAL TON_typ InclinoTimer;

/* TODO: Add your comment here */
void FB_InclinoSensor(struct FB_InclinoSensor* inst)
{
	/*TODO: Add your code here*/
	InclinoSensor->STS.CurrentAngle = (float)((INT)((InclinoSensor->IO.DataMSB << SHIFT_BYTE) | InclinoSensor->IO.DataLSB)) / TO_DEGREES;
	
	BOOL start = InclinoSensor->CS.SetCenterPoint && !InclinoSensor->STS.CenterPointSet;

	InclinoTimer.IN = start;
	InclinoTimer.PT = 100;
	TON(&InclinoTimer);

	if(start)
	{
    	InclinoSensor->IO.SetCenterPoint = 3;
	}
	else
	{
    	InclinoSensor->IO.SetCenterPoint = 0;
	}
	if(InclinoTimer.Q)
	{
    	InclinoSensor->STS.CenterPointSet = 1;
	}
}
