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

#define InclinoSensor inst->InclinoSensor

void FB_InclinoSensor(struct FB_InclinoSensor* inst)
{
	/* Combine MSB + LSB into signed raw value, then scale to degrees, sensor sends value as integer * 100 */
	InclinoSensor->STS.CurrentAngle = (float)((INT)((InclinoSensor->IO.DataMSB << SHIFT_BYTE) | InclinoSensor->IO.DataLSB)) / TO_DEGREES;

	InclinoSensor->STS.AlarmActiveColour = InclinoSensor->STS.AlarmActive ? RED_COLOUR : GREEN_COLOUR;

	// Setpoint selection for calibration mode vs normal operation
	InclinoSensor->IO.SetCenterPoint = InclinoSensor->CS.SetCenterPoint ? CENTERPOINT_SET : CENTERPOINT_NORMAL;
}
