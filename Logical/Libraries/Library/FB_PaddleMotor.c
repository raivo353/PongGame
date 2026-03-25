
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
void FB_PaddleMotor(struct FB_PaddleMotor* inst)
{
	/*TODO: Add your code here*/
	inst->PaddleMotor->IO.EndButton = !((inst->digitalInput & 0x2) >> 1);
	
	if(inst->PaddleMotor->HMI.IncreaseJogSpeed && inst->PaddleMotor->PAR.JogVelocity < 4000)
	{
		inst->PaddleMotor->PAR.JogVelocity++;
	}
	if(inst->PaddleMotor->HMI.DecreaseJogSpeed && inst->PaddleMotor->PAR.JogVelocity > 0)
	{
		inst->PaddleMotor->PAR.JogVelocity--;
	}
	if(inst->PaddleMotor->HMI.IncreaseAccDec && inst->PaddleMotor->PAR.Acceleration < 20000)
	{
		inst->PaddleMotor->PAR.Acceleration += 10;
		inst->PaddleMotor->PAR.Deceleration += 10;
	}
	if(inst->PaddleMotor->HMI.DecreaseAccDec && inst->PaddleMotor->PAR.Deceleration > 100)
	{
		inst->PaddleMotor->PAR.Acceleration -= 10;
		inst->PaddleMotor->PAR.Deceleration -= 10;
	}
	
	inst->PaddleMotor->ALM.ErrorText[0][79] = '\0'; 
}
