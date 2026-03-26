#include <bur/plctypes.h>

#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif

#define TO_ANGLE 100
#define SHIFT_BYTE 8
/* TODO: Add your comment here */
void FB_InclinoSensor(struct FB_InclinoSensor* inst)
{
	/*TODO: Add your code here*/
	inst->InclinoSensor->STS.CurrentAngle = (float)((INT)((inst->InclinoSensor->IO.DataMSB << SHIFT_BYTE) | inst->InclinoSensor->IO.DataLSB)) / TO_ANGLE;
}
