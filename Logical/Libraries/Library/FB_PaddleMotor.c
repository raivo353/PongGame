
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif

#define ACTPOSITION_TO_MM 0.0784
#define ENDBUTTON_BITMASK 0x2
#define MAX_JOG_VELOCITY 4000
#define MAX_ACC_DEC 20000
#define MIN_ACC_DEC 100

/* TODO: Add your comment here */
void FB_PaddleMotor(struct FB_PaddleMotor* inst)
{
	/*TODO: Add your code here*/
	inst->PaddleMotor->IO.EndButton = !((inst->digitalInput & ENDBUTTON_BITMASK) >> 1);
	inst->PaddleMotor->STS.ActPosition = -inst->PaddleMotor->STS.ActPosition * ACTPOSITION_TO_MM;
	
	if(inst->PaddleMotor->HMI.IncreaseJogSpeed && inst->PaddleMotor->PAR.JogVelocity < MAX_JOG_VELOCITY)
	{
		inst->PaddleMotor->PAR.JogVelocity++;
	}
	else if(inst->PaddleMotor->HMI.DecreaseJogSpeed && inst->PaddleMotor->PAR.JogVelocity > 0)
	{
		inst->PaddleMotor->PAR.JogVelocity--;
	}
	if(inst->PaddleMotor->HMI.IncreaseAccDec && inst->PaddleMotor->PAR.Acceleration < MAX_ACC_DEC)
	{
		inst->PaddleMotor->PAR.Acceleration += 10;
		inst->PaddleMotor->PAR.Deceleration += 10;
	}
	else if(inst->PaddleMotor->HMI.DecreaseAccDec && inst->PaddleMotor->PAR.Deceleration > MIN_ACC_DEC)
	{
		inst->PaddleMotor->PAR.Acceleration -= 10;
		inst->PaddleMotor->PAR.Deceleration -= 10;
	}
	 
	//io mapping
	inst->PaddleMotor->IO.Power = inst->PaddleMotor->HMI.Power;
	inst->PaddleMotor->IO.Home = inst->PaddleMotor->HMI.Home;
	inst->PaddleMotor->IO.MoveJogNeg = inst->PaddleMotor->HMI.MoveJogNeg;
	inst->PaddleMotor->IO.MoveJogPos = inst->PaddleMotor->HMI.MoveJogPos;
	inst->PaddleMotor->IO.ErrorAcknowledge = inst->PaddleMotor->HMI.ErrorAcknowledge;

	inst->PaddleMotor->IO.JogVelocity = inst->PaddleMotor->PAR.JogVelocity;
	inst->PaddleMotor->IO.Acceleration = inst->PaddleMotor->PAR.Acceleration;
	inst->PaddleMotor->IO.Deceleration = inst->PaddleMotor->PAR.Deceleration;
	inst->PaddleMotor->IO.Velocity = inst->PaddleMotor->PAR.Velocity;
	inst->PaddleMotor->IO.Position = inst->PaddleMotor->PAR.Position;
}
