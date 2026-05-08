/*********************************************************************************
 * Copyright: MyAutomation-IT
 * Author:    raivo 
 * Created:   April 22, 2026/5:57 PM 
 *********************************************************************************/ 
#include <bur/plctypes.h>
#include <standard.h>
#include "CommonTypes.h"
#include <string.h>
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

void FB_PongGame(struct FB_PongGame* inst)
{
	if((PongGame->CS.StopGame ^ PongGame->HMI.StopGame) && !PongGame->STS.Interlocked)
	{
		/* immediate stop override */
		PongGame->STS.StateInt = STATE_STOPPING;
	}
	
	if(PongGame->STS.AlarmActive)
	{
		/* prevent repeated stop triggers */
		PongGame->CS.StopGame = !PongGame->STS.GameStopped;

		if(PongGame->CS.StopGame && !PongGame->STS.GameStopped)
		{
    		PongGame->STS.GameStopped = 1;
		}
		
		/* 1s blink generator */
		AlarmTimer.IN = 1;
		AlarmTimer.PT = MS_1000;
		TON(&AlarmTimer);

		if(AlarmTimer.Q)
		{
			BlinkState = !BlinkState;

			AlarmTimer.IN = 0;
			TON(&AlarmTimer);
		}

		PongGame->STS.AlarmActiveColour = BlinkState ? RED_COLOUR : BLACK_COLOUR;
	}
	else
	{
		PongGame->STS.AlarmActiveColour = BLACK_COLOUR;

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
			PongGame->PAR.Score = 0;
			strncpy(PongGame->STS.StateString, "Disabled", sizeof(PongGame->STS.StateString));
			if(PongGame->STS.Initializing)
			{
				PongGame->STS.StateInt = STATE_INITIALIZING;
			}
			break;
		}
		case STATE_INITIALIZING:
		{
			strncpy(PongGame->STS.StateString, "Initializing...", sizeof(PongGame->STS.StateString));
			if(PongGame->STS.Idle)
			{
				PongGame->STS.StateInt = STATE_IDLE;
			}
			break;
		}
		case STATE_IDLE:
		{
			strncpy(PongGame->STS.StateString, "Idle", sizeof(PongGame->STS.StateString));
			if(PongGame->STS.Running)
			{
				PongGame->STS.StateInt = STATE_RUNNING;
			}
			break;
		}
		case STATE_RUNNING:
		{
			if(BallControl->STS.ShootCycleCompleted)
			{	
				PongGame->PAR.Score += 1;
			}
			if(BallControl->STS.GameOver)
			{
				PongGame->CS.StopGame = 1;
			}
			strncpy(PongGame->STS.StateString, "Running", sizeof(PongGame->STS.StateString));
			break;
		}
		case STATE_STOPPING:
		{
			PongGame->CS.StopGame = 0;
			if(PongGame->PAR.Score > PongGame->PAR.Highscore)
			{
				PongGame->PAR.Highscore = PongGame->PAR.Score;
			}
			strncpy(PongGame->STS.StateString, "Stopping...", sizeof(PongGame->STS.StateString));
			if(PongGame->STS.Disabled)
			{
				PongGame->STS.StateInt = STATE_DISABLED;
			}
			break;
		}
	}

	if(!PongGame->STS.AlarmActive && !PongGame->STS.Interlocked)
	{
		/*Signals can only be sent from HMI or CS, not both */
		BallControl->CS.Initialize = PongGame->HMI.Initialize ^ PongGame->CS.Initialize;
		BallControl->CS.StopGame = PongGame->HMI.StopGame ^ PongGame->CS.StopGame;
		BallControl->CS.Start = PongGame->HMI.Start ^ PongGame->CS.Start;
		FieldControl->CS.Initialize = PongGame->HMI.Initialize ^ PongGame->CS.Initialize;
		
		FieldControl->CS.Start = PongGame->HMI.Start ^ PongGame->CS.Start;
	}
	
	/*Signals can only be sent from HMI or CS, not both */
	FieldControl->CS.StopGame = PongGame->HMI.StopGame ^ PongGame->CS.StopGame;
	BallControl->CS.AutoMode = PongGame->HMI.AutoMode ^ PongGame->CS.AutoMode;
	BallControl->CS.ErrorAcknowledge = PongGame->HMI.ErrorAcknowledge ^ PongGame->CS.ErrorAcknowledge;

	FieldControl->STS.AutoActive = PongGame->HMI.AutoMode || PongGame->CS.AutoMode;
	
	/* subsystem state mapping */
	PongGame->STS.AutoActive = BallControl->STS.AutoActive && FieldControl->STS.AutoActive;
	PongGame->STS.Initializing = BallControl->STS.Initializing && FieldControl->STS.Initializing;
	PongGame->STS.AlarmActive = BallControl->STS.AlarmActive || FieldControl->STS.AlarmActive;
	PongGame->STS.Disabled = BallControl->STS.Disabled && FieldControl->STS.Disabled;
	PongGame->STS.Idle = BallControl->STS.Idle && FieldControl->STS.Idle;
	PongGame->STS.Running = BallControl->STS.Running && FieldControl->STS.Running;
	PongGame->STS.Interlocked = BallControl->STS.Interlocked || FieldControl->STS.Interlocked;
}
