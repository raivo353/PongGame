#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif
#include <string.h>

#define STATE_WAIT              0 

void _INIT ProgramInit(void)
{
	/* get axis object */
	Axis1Obj = (UDINT)&gAxis02;

	AxisStep = STATE_WAIT;  /* start step */

	BasicControl.Parameter.Velocity              = 1000;  /*velocity for movement*/
	BasicControl.Parameter.Acceleration          = 5000;  /*acceleration for movement*/
	BasicControl.Parameter.Deceleration          = 5000;  /*deceleration for movement*/
	BasicControl.Parameter.JogVelocity           = 400;   /*velocity for jogging */
}