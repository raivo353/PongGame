
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
}
