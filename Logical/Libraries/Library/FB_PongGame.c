
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
void FB_PongGame(struct FB_PongGame* inst)
{
	/*TODO: Add your code here*/
	inst->BallControl->CS.Initialize = inst->PongGame->HMI.Initialize | inst->PongGame->CS.Initialize;
	inst->BallControl->CS.StopGame = inst->PongGame->HMI.StopGame | inst->PongGame->CS.StopGame;
	inst->BallControl->CS.Start = inst->PongGame->HMI.Start | inst->PongGame->CS.Start;
	inst->BallControl->CS.AutoMode = inst->PongGame->HMI.AutoMode | inst->PongGame->CS.AutoMode;
	inst->BallControl->CS.ErrorAcknowledge = inst->PongGame->HMI.ErrorAcknowledge | inst->PongGame->CS.ErrorAcknowledge;

	inst->FieldControl->CS.Initialize = inst->PongGame->HMI.Initialize | inst->PongGame->CS.Initialize;
	inst->FieldControl->CS.StopGame = inst->PongGame->HMI.StopGame | inst->PongGame->CS.StopGame;
	inst->FieldControl->CS.Start = inst->PongGame->HMI.Start | inst->PongGame->CS.Start;
	inst->FieldControl->STS.AutoActive = inst->PongGame->HMI.AutoMode | inst->PongGame->CS.AutoMode;
	
	inst->PongGame->STS.AutoActive = inst->BallControl->STS.AutoActive & inst->FieldControl->STS.AutoActive;
	inst->PongGame->STS.Initializing = inst->BallControl->STS.Initializing & inst->FieldControl->STS.Initializing;
	inst->PongGame->STS.AlarmActive = inst->BallControl->STS.AlarmActive | inst->FieldControl->STS.AlarmActive;
	inst->PongGame->STS.Disabled = inst->BallControl->STS.Disabled & inst->FieldControl->STS.Disabled;
	inst->PongGame->STS.Idle = inst->BallControl->STS.Idle & inst->FieldControl->STS.Idle;
	inst->PongGame->STS.Running = inst->BallControl->STS.Running & inst->FieldControl->STS.Running;
		
}
