#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif
#include <string.h>

#define STATE_WAIT              0 

void _INIT ProgramInit(void)
{
	/* get axis object */
	Axis1Obj = (UDINT)&gAxis01;

	AxisStep = STATE_WAIT;  /* start step */

	//BasicControl.Command.Home = 1;
	BasicControl.Parameter.Velocity              = 400;  /*velocity for movement*/
	BasicControl.Parameter.Acceleration          = 40000;  /*acceleration for movement*/
	BasicControl.Parameter.Deceleration          = 40000;  /*deceleration for movement*/
	BasicControl.Parameter.JogVelocity           = 400;   /*velocity for jogging */
	

}