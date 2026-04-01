
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
void FB_BallControl(struct FB_BallControl* inst)
{
	/*TODO: Add your code here*/
	inst->PaddleMotor->CS.Initialize = inst->BallControl->CS.Initialize;
	inst->PaddleMotor->CS.Start = inst->BallControl->CS.Start;
	inst->PaddleMotor->CS.StopGame = inst->BallControl->CS.StopGame;
	inst->PaddleMotor->CS.AutoMode = inst->BallControl->CS.AutoMode;
	inst->PaddleMotor->CS.ErrorAcknowledge = inst->BallControl->CS.ErrorAcknowledge;

	inst->BallControl->STS.Idle = inst->PaddleMotor->STS.Idle;
	inst->BallControl->STS.AutoActive = inst->PaddleMotor->STS.AutoActive;
	inst->BallControl->STS.Disabled = inst->PaddleMotor->STS.Disabled;
	inst->BallControl->STS.Initializing = inst->PaddleMotor->STS.Initializing;
	inst->BallControl->STS.Running = inst->PaddleMotor->STS.Running;
	inst->BallControl->STS.Interlocked = inst->PaddleMotor->STS.Interlocked & inst->Shooter->STS.Interlocked;

}
