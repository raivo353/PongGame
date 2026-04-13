
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


#define BallControl inst->BallControl
#define PaddleMotor inst->PaddleMotor
#define Shooter inst->Shooter

/* TODO: Add your comment here */
void FB_BallControl(struct FB_BallControl* inst)
{
	/*TODO: Add your code here*/

	if(BallControl->CS.StopGame)
	{
		BallControl->STS.StateInt = STATE_STOPPING;
	}

	switch(BallControl->STS.StateInt)
	{
		case STATE_DISABLED:
		{
			BallControl->STS.Disabled = 1;
			BallControl->STS.Idle = 0;
			BallControl->STS.Initializing = 0;
			BallControl->STS.Running = 0;

			if(BallControl->STS.Initializing)
			{
				BallControl->STS.StateInt = STATE_INITIALIZING;
			}
			break;
		}
		case STATE_INITIALIZING:
		{
			if(BallControl->STS.Idle)
			{
				BallControl->STS.StateInt = STATE_IDLE;
			}
			break;
		}
		case STATE_IDLE:
		{
			if(BallControl->STS.Running)
			{
				BallControl->STS.StateInt = STATE_RUNNING;
			}
			break;
		}
		case STATE_RUNNING:
		{
			break;
		}
		case STATE_STOPPING:
		{
			if(BallControl->STS.Disabled)
			{
				BallControl->STS.StateInt = STATE_DISABLED;
			}
			break;
		}
	}

	PaddleMotor->CS.Initialize = BallControl->CS.Initialize;
	PaddleMotor->CS.Start = BallControl->CS.Start;
	PaddleMotor->CS.StopGame = BallControl->CS.StopGame;
	PaddleMotor->CS.AutoMode = BallControl->CS.AutoMode;
	PaddleMotor->CS.ErrorAcknowledge = BallControl->CS.ErrorAcknowledge;

	Shooter->CS.Start = BallControl->CS.Start;
	Shooter->CS.StopGame = BallControl->CS.StopGame;
	Shooter->CS.AutoMode = BallControl->CS.AutoMode;

	BallControl->STS.Idle = PaddleMotor->STS.Idle;
	BallControl->STS.AutoActive = PaddleMotor->STS.AutoActive && Shooter->STS.AutoActive;
	BallControl->STS.Disabled = PaddleMotor->STS.Disabled && Shooter->STS.Disabled;
	BallControl->STS.Initializing = PaddleMotor->STS.Initializing;
	BallControl->STS.Running = PaddleMotor->STS.Running;
	BallControl->STS.Interlocked = PaddleMotor->STS.Interlocked || Shooter->STS.Interlocked;
	BallControl->STS.AlarmActive = PaddleMotor->STS.AlarmActive || Shooter->STS.AlarmActive;
}
