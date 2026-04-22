
#include <bur/plctypes.h>
#include <standard.h>
#include "CommonTypes.h"
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif


#define PongGame inst->PongGame
#define BallControl inst->BallControl
#define FieldControl inst->FieldControl

_LOCAL TON_typ AlarmTimer;
_LOCAL BOOL BlinkState;

/* TODO: Add your comment here */
void FB_PongGame(struct FB_PongGame* inst)
{
	if(PongGame->CS.StopGame || PongGame->HMI.StopGame)
	{
		PongGame->STS.StateInt = STATE_STOPPING;
	}
	PongGame->STS.AlarmActiveColour = BLACK_COLOUR;
	if(PongGame->STS.AlarmActive)
	{
		PongGame->CS.StopGame = !PongGame->STS.GameStopped;

		if(PongGame->CS.StopGame && !PongGame->STS.GameStopped)
		{
    		PongGame->STS.GameStopped = 1;
			//PongGame->CS.StopGame = 0;
		}
		
		AlarmTimer.IN = 1;
		AlarmTimer.PT = 1000;
		TON(&AlarmTimer);

		if(AlarmTimer.Q)
		{
			BlinkState = !BlinkState;

			AlarmTimer.IN = 0;
			TON(&AlarmTimer);
		}
		if(BlinkState)
		{
			PongGame->STS.AlarmActiveColour = RED_COLOUR;
		}
		else
		{
			PongGame->STS.AlarmActiveColour = BLACK_COLOUR;
		}
	}
	else
	{
		AlarmTimer.IN = 0;
		TON(&AlarmTimer);
		BlinkState = 0;
	}
	

	switch(PongGame->STS.StateInt)
	{
		case STATE_DISABLED:
		{
			PongGame->STS.GameStopped = 0;
			PongGame->CS.StopGame = 0;
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

	BallControl->CS.Initialize = PongGame->HMI.Initialize ^ PongGame->CS.Initialize;
	BallControl->CS.StopGame = PongGame->HMI.StopGame ^ PongGame->CS.StopGame;
	BallControl->CS.Start = PongGame->HMI.Start ^ PongGame->CS.Start;
	BallControl->CS.AutoMode = PongGame->HMI.AutoMode ^ PongGame->CS.AutoMode;
	BallControl->CS.ErrorAcknowledge = PongGame->HMI.ErrorAcknowledge ^ PongGame->CS.ErrorAcknowledge;

	FieldControl->CS.Initialize = PongGame->HMI.Initialize ^ PongGame->CS.Initialize;
	FieldControl->CS.StopGame = PongGame->HMI.StopGame ^ PongGame->CS.StopGame;
	FieldControl->CS.Start = PongGame->HMI.Start ^ PongGame->CS.Start;
	
	FieldControl->STS.AutoActive = PongGame->HMI.AutoMode || PongGame->CS.AutoMode;
	
	PongGame->STS.AutoActive = BallControl->STS.AutoActive && FieldControl->STS.AutoActive;
	PongGame->STS.Initializing = BallControl->STS.Initializing && FieldControl->STS.Initializing;
	PongGame->STS.AlarmActive = BallControl->STS.AlarmActive || FieldControl->STS.AlarmActive;
	PongGame->STS.Disabled = BallControl->STS.Disabled && FieldControl->STS.Disabled;
	PongGame->STS.Idle = BallControl->STS.Idle && FieldControl->STS.Idle;
	PongGame->STS.Running = BallControl->STS.Running && FieldControl->STS.Running;
}
