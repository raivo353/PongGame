
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif

#define ENDBUTTON_BITMASK 0x4
#define MAX_JOG_VELOCITY 4000

/* TODO: Add your comment here */
void FB_FieldMotor(struct FB_FieldMotor* inst)
{
	/*TODO: Add your code here*/
	inst->FieldMotor->IO.EndButton = !((inst->digitalInput & ENDBUTTON_BITMASK) >> 2);
	
	if(inst->FieldMotor->HMI.IncreaseJogSpeed && inst->FieldMotor->PAR.JogVelocity < MAX_JOG_VELOCITY)
	{
		inst->FieldMotor->PAR.JogVelocity++;
	}
	else if(inst->FieldMotor->HMI.DecreaseJogSpeed && inst->FieldMotor->PAR.JogVelocity > 0)
	{
		inst->FieldMotor->PAR.JogVelocity--;
	}
	
	//io mapping
	inst->FieldMotor->IO.Power = inst->FieldMotor->HMI.Power;
	inst->FieldMotor->IO.Home = inst->FieldMotor->HMI.Home;
	inst->FieldMotor->IO.MoveJogNeg = inst->FieldMotor->HMI.MoveJogNeg;
	inst->FieldMotor->IO.MoveJogPos = inst->FieldMotor->HMI.MoveJogPos;
	inst->FieldMotor->IO.ErrorAcknowledge = inst->FieldMotor->HMI.ErrorAcknowledge;
	
	inst->FieldMotor->IO.Acceleration = inst->FieldMotor->PAR.Acceleration;
	inst->FieldMotor->IO.Deceleration = inst->FieldMotor->PAR.Deceleration;
	inst->FieldMotor->IO.JogVelocity = inst->FieldMotor->PAR.JogVelocity;
	inst->FieldMotor->IO.Velocity = inst->FieldMotor->PAR.Velocity;
	inst->FieldMotor->IO.Position = inst->FieldMotor->PAR.Position;
}
