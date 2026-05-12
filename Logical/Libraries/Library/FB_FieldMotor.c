/*********************************************************************************
 * Copyright: MyAutomation-IT
 * Author:    raivo 
 * Created:   April 22, 2026/5:57 PM 
 *********************************************************************************/ 
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

#define FieldMotor inst->FieldMotor

_LOCAL TON_typ FieldMotorTimer;

/* TODO: Add your comment here */
void FB_FieldMotor(struct FB_FieldMotor* inst)
{
	/* alarm visual */
	FieldMotor->STS.AlarmActiveColour = FieldMotor->STS.AlarmActive ? RED_COLOUR : GREEN_COLOUR;

	/* input decoding */
	FieldMotor->IO.EndButton = !((inst->digitalInput & ENDBUTTON_BITMASK_FIELD) >> 2);
	
	/* stop request handling */
	if(FieldMotor->CS.StopGame && !FieldMotor->STS.Interlocked)
	{
		FieldMotor->STS.StateInt = STATE_STOPPING;
	}

	switch(FieldMotor->STS.StateInt)
	{
		case STATE_DISABLED:
			/* full reset of outputs and internal flags */
			FieldMotor->CS.Power = 0;
			FieldMotor->CS.Home = 0;
			FieldMotor->CS.MoveJogNeg = 0;
			FieldMotor->CS.MoveJogPos = 0;
			FieldMotor->CS.MoveAbsolute = 0;

			FieldMotor->STS.Disabled = 1;
			FieldMotor->STS.EndButtonHit = 0;
			FieldMotor->STS.TimerStarted = 0;
			FieldMotor->STS.TimerEnded = 0;
			FieldMotor->STS.ReferencePosition = 0;
			FieldMotor->STS.AtTargetPosition = 0;

			if(FieldMotor->CS.Initialize && !FieldMotor->STS.AlarmActive && !FieldMotor->STS.Interlocked)
			{
				FieldMotor->STS.StateInt = STATE_INITIALIZING;
			}
			break;
		case STATE_INITIALIZING:
			/* enable drive for homing */
			FieldMotor->CS.Power = 1;
			FieldMotor->CS.Stop = 0;

			FieldMotor->STS.Initializing = 1;
			FieldMotor->STS.Disabled = 0;

			/* default motion parameters */
			FieldMotor->PAR.Acceleration = MAX_ACC_DEC;
			FieldMotor->PAR.Deceleration = MAX_ACC_DEC;
			FieldMotor->PAR.JogVelocity = STD_VELOCITY;
			FieldMotor->PAR.Velocity = STD_VELOCITY;

			/* homing timer base */
			FieldMotorTimer.PT = MS_100; 
			TON(&FieldMotorTimer);

			/* homing start condition */
			if(!FieldMotor->IO.EndButton && !FieldMotor->STS.EndButtonHit) 
			{
				if(!FieldMotor->STS.TimerStarted) 
				{ 
					FieldMotor->CS.Home = 1;
					FieldMotorTimer.IN = 1; 
					FieldMotor->STS.TimerStarted = 1;
				} 			
				else if(FieldMotorTimer.Q) 
				{ 
					FieldMotorTimer.IN = 0;
					FieldMotor->CS.Home = 0; 
					FieldMotor->CS.MoveJogPos = 1;
				} 
			}
			/* end switch reached */
			else if(FieldMotor->IO.EndButton && !FieldMotor->STS.EndButtonHit)
			{			
				FieldMotor->CS.MoveJogPos = 0;
				FieldMotor->STS.EndButtonHit = 1;
				FieldMotor->CS.Home = 1;
				FieldMotor->CS.SetCenterPoint = 1;
	
				FieldMotorTimer.IN = 1;
			}
			/* post homing alignment */
			else if(FieldMotor->STS.EndButtonHit)
			{
				if(FieldMotorTimer.Q)
				{
					FieldMotorTimer.IN = 0;
					FieldMotor->STS.TimerStarted = 0;
					FieldMotor->CS.Home = 0;
					FieldMotor->CS.SetCenterPoint = 0;
					FieldMotor->CS.MoveJogNeg = 1;
				}
				if(FieldMotor->STS.AtTargetPosition && !FieldMotor->STS.AlarmActive && !FieldMotor->STS.Interlocked)
				{
					FieldMotor->CS.MoveJogNeg = 0;
					FieldMotor->STS.StateInt = STATE_IDLE;
				}

			}
			break;
		case STATE_IDLE:
			/* idle state reset */
			FieldMotor->STS.Initializing = 0;
			FieldMotor->STS.Idle = 1;

			FieldMotor->CS.MoveAbsolute = 0;
			FieldMotor->CS.MoveJogNeg = 0;
			FieldMotor->CS.MoveJogPos = 0;
			FieldMotor->CS.Power = 0;
			
			/* start condition */
			if(FieldMotor->CS.Start && !FieldMotor->STS.AlarmActive && !FieldMotor->STS.Interlocked)
			{
				FieldMotor->STS.StateInt = STATE_RUNNING;
			}
			break;
		case STATE_RUNNING:
			/* active motion state */
			FieldMotor->STS.Running = 1;
			FieldMotor->STS.Idle = 0;
			FieldMotor->CS.Power = 1;

			if(!FieldMotor->STS.AutoActive)
			{
				/* manual jog control */
				FieldMotor->CS.MoveAbsolute = 0;
				FieldMotor->CS.MoveJogNeg = 0;
				FieldMotor->CS.MoveJogPos = 0;

				/* jog speed tuning */
				if(FieldMotor->HMI.IncreaseJogSpeed && FieldMotor->PAR.JogVelocity < MAX_VELOCITY)
				{
					FieldMotor->PAR.JogVelocity++;
				}
				else if(FieldMotor->HMI.DecreaseJogSpeed && FieldMotor->PAR.JogVelocity > MIN_VELOCITY)
				{
					FieldMotor->PAR.JogVelocity--;
				}
			}			

			/* end switch safety override */
			if(FieldMotor->IO.EndButton)
			{
				FieldMotor->CS.MoveJogPos = 0;
				FieldMotor->HMI.MoveJogPos = 0;
				FieldMotor->CS.MoveAbsolute = 0;
			}
			break;
		case STATE_STOPPING:
			/* safe stop sequence */
			FieldMotor->STS.Running = 0;
			FieldMotor->STS.Idle = 0;
			FieldMotor->STS.Initializing = 0;
			
			FieldMotor->CS.MoveAbsolute = 0;
			FieldMotor->CS.MoveJogNeg = 0;
			FieldMotor->CS.MoveJogPos = 0;
			FieldMotor->CS.Stop = 1;

			if(FieldMotor->STS.StandStill && !FieldMotor->STS.Interlocked)
			{
				FieldMotor->STS.StateInt = STATE_DISABLED;
			}
			break;
	}
	 
	/* IO mapping */
	FieldMotor->IO.Power = FieldMotor->CS.Power;
	FieldMotor->IO.Home = FieldMotor->CS.Home;
	FieldMotor->IO.Stop = FieldMotor->CS.Stop;
	
	FieldMotor->IO.JogVelocity = FieldMotor->PAR.JogVelocity;
	FieldMotor->IO.Acceleration = FieldMotor->PAR.Acceleration;
	FieldMotor->IO.Deceleration = FieldMotor->PAR.Deceleration;
	FieldMotor->IO.Velocity = FieldMotor->PAR.Velocity;
	FieldMotor->IO.Position = FieldMotor->PAR.Position;


	FieldMotor->IO.ErrorAcknowledge = FieldMotor->HMI.ErrorAcknowledge ^ FieldMotor->CS.ErrorAcknowledge;
	FieldMotor->IO.MoveJogPos = FieldMotor->CS.MoveJogPos ^ FieldMotor->HMI.MoveJogPos;
	FieldMotor->IO.MoveJogNeg = FieldMotor->CS.MoveJogNeg ^ FieldMotor->HMI.MoveJogNeg;
	FieldMotor->IO.MoveAbsolute = FieldMotor->CS.MoveAbsolute ^ FieldMotor->HMI.MoveAbsolute;

	/* alarm source */
	FieldMotor->STS.AlarmActive = FieldMotor->ALM.MotorError;

	/* derived motion states */
	FieldMotor->STS.StandStill = (int)FieldMotor->STS.ActVelocity == 0;
	FieldMotor->STS.Moving = !FieldMotor->STS.StandStill;

}
