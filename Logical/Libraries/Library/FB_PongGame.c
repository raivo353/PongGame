
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
	inst->BallControl->CS.Initialize = inst->PongGame->HMI.Initialize;
	inst->BallControl->CS.StopGame = inst->PongGame->HMI.StopGame;
	inst->BallControl->CS.Start = inst->PongGame->HMI.Start;

	inst->FieldControl->CS.Initialize = inst->PongGame->HMI.Initialize;
	inst->FieldControl->CS.StopGame = inst->PongGame->HMI.StopGame;
	inst->FieldControl->CS.Start = inst->PongGame->HMI.Start;
}
