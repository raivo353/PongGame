
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif

#define STATE_DISABLED 00
#define STATE_INITIALIZING 10
#define STATE_IDLE 20
#define STATE_RUNNING 30
#define STATE_STOPPING 40

#define PongGame inst->PongGame
#define BallControl inst->BallControl
#define FieldControl inst->FieldControl

/* TODO: Add your comment here */
void FB_PongGame(struct FB_PongGame* inst)
{
	/*TODO: Add your code here*/
	if(PongGame->CS.StopGame || PongGame->HMI.StopGame)
	{
		PongGame->STS.StateInt = STATE_STOPPING;
	}

	switch(PongGame->STS.StateInt)
	{
		case STATE_DISABLED:
		{
			if(PongGame->STS.Initializing)
			{
				PongGame->STS.StateInt = STATE_INITIALIZING;
			}
			break;
		}
		case STATE_INITIALIZING:
		{
			if(PongGame->STS.Idle)
			{
				PongGame->STS.StateInt = STATE_IDLE;
			}
			break;
		}
		case STATE_IDLE:
		{
			if(PongGame->STS.Running)
			{
				PongGame->STS.StateInt = STATE_RUNNING;
			}
			break;
		}
		case STATE_RUNNING:
		{
			break;
		}
		case STATE_STOPPING:
		{
			if(PongGame->STS.Disabled)
			{
				PongGame->STS.StateInt = STATE_DISABLED;
			}
			break;
		}
	}

	BallControl->CS.Initialize = PongGame->HMI.Initialize | PongGame->CS.Initialize;
	BallControl->CS.StopGame = PongGame->HMI.StopGame | PongGame->CS.StopGame;
	BallControl->CS.Start = PongGame->HMI.Start | PongGame->CS.Start;
	BallControl->CS.AutoMode = PongGame->HMI.AutoMode | PongGame->CS.AutoMode;
	BallControl->CS.ErrorAcknowledge = PongGame->HMI.ErrorAcknowledge | PongGame->CS.ErrorAcknowledge;

	FieldControl->CS.Initialize = PongGame->HMI.Initialize | PongGame->CS.Initialize;
	FieldControl->CS.StopGame = PongGame->HMI.StopGame | PongGame->CS.StopGame;
	FieldControl->CS.Start = PongGame->HMI.Start | PongGame->CS.Start;
	FieldControl->STS.AutoActive = PongGame->HMI.AutoMode | PongGame->CS.AutoMode;
	
	PongGame->STS.AutoActive = BallControl->STS.AutoActive & FieldControl->STS.AutoActive;
	PongGame->STS.Initializing = BallControl->STS.Initializing & FieldControl->STS.Initializing;
	PongGame->STS.AlarmActive = BallControl->STS.AlarmActive | FieldControl->STS.AlarmActive;
	PongGame->STS.Disabled = BallControl->STS.Disabled & FieldControl->STS.Disabled;
	PongGame->STS.Idle = BallControl->STS.Idle & FieldControl->STS.Idle;
	PongGame->STS.Running = BallControl->STS.Running & FieldControl->STS.Running;
}
