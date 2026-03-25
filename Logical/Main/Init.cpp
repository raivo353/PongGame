
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	
	g_PaddleMotor.PAR.Velocity = 1000;
	g_PaddleMotor.PAR.Acceleration = 5000;
	g_PaddleMotor.PAR.Deceleration = 5000;
	g_PaddleMotor.PAR.JogVelocity = 400;
}
