
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

#define POSITION_TO_MM 0.0784
#define ENDBUTTON_BITMASK 0x2
#define MIN_ACC_DEC 100
#define MIN_POSITION PaddleMotor->STS.ReferencePosition - 2800
#define MIDDLE_POSITION 1450
#define STOPPING_OFFSET PaddleMotor->PAR.JogVelocity * PaddleMotor->PAR.JogVelocity * 0.0000216
#define REFERENCE_OFFSET 25


#define PaddleMotor inst->PaddleMotor

_LOCAL TON_typ PaddleMotorTimer;

/* TODO: Add your comment here */
void FB_PaddleMotor(struct FB_PaddleMotor* inst)
{
	/*TODO: Add your code here*/
	PaddleMotor->IO.EndButton = !((inst->digitalInput & ENDBUTTON_BITMASK) >> 1);

	if(PaddleMotor->CS.StopGame)
	{
		PaddleMotor->STS.StateInt = STATE_STOPPING;
	}

	PaddleMotor->STS.AlarmActiveColour = GREEN_COLOUR;
	if(PaddleMotor->STS.AlarmActive)
	{
		PaddleMotor->STS.AlarmActiveColour = RED_COLOUR;
	}

	switch(PaddleMotor->STS.StateInt)
	{
		case STATE_DISABLED:
			PaddleMotor->STS.Disabled = 1;
			PaddleMotor->STS.ReferenceSet = 0;
			PaddleMotor->CS.Power = 0;
			PaddleMotor->CS.Home = 0;
			PaddleMotor->STS.EndButtonHit = 0;
			PaddleMotor->CS.MoveJogNeg = 0;
			PaddleMotor->CS.MoveJogPos = 0;
			PaddleMotor->CS.MoveAbsolute = 0;
			PaddleMotor->HMI.MoveJogNeg = 0;
			PaddleMotor->HMI.MoveJogPos = 0;
			PaddleMotor->STS.TimerStarted = 0;
			PaddleMotor->STS.TimerEnded = 0;
			PaddleMotor->STS.ReferencePosition = 0;

			PaddleMotorTimer.IN = 0;
			TON(&PaddleMotorTimer);

			if(PaddleMotor->CS.Initialize && !PaddleMotor->STS.AlarmActive && !PaddleMotor->STS.Interlocked)
			{
				PaddleMotor->STS.StateInt = STATE_INITIALIZING;
			}
			break;
		case STATE_INITIALIZING:
			PaddleMotor->STS.Initializing = 1;
			PaddleMotor->STS.Disabled = 0;
			PaddleMotor->PAR.Acceleration = MAX_ACC_DEC;
			PaddleMotor->PAR.Deceleration = MAX_ACC_DEC;
			PaddleMotor->PAR.JogVelocity = 1000;
			PaddleMotor->PAR.Velocity = 1000;

			PaddleMotor->CS.Power = 1;	
			PaddleMotor->CS.Stop = 0;

			PaddleMotor->HMI.MoveJogNeg = 0;
			PaddleMotor->HMI.MoveJogPos = 0;
			
			if(!PaddleMotor->IO.EndButton && !PaddleMotor->STS.EndButtonHit) 
			{ 
				PaddleMotor->CS.Home = 1; 
				if(!PaddleMotor->STS.TimerStarted) 
				{ 
					PaddleMotorTimer.IN = 1; 
					PaddleMotor->STS.TimerStarted = 1; 
				} 
				PaddleMotorTimer.PT = MS_100; 
				TON(&PaddleMotorTimer); 
			
				if(PaddleMotorTimer.Q) 
				{ 
					PaddleMotor->CS.Home = 0; 
					PaddleMotor->CS.MoveJogPos = 1; 
				} 
			}
			else if(PaddleMotor->IO.EndButton && !PaddleMotor->STS.EndButtonHit)
			{
				PaddleMotorTimer.IN = 0;
				PaddleMotor->STS.TimerStarted = 0;
			
				PaddleMotor->CS.MoveJogPos = 0;
				PaddleMotor->STS.EndButtonHit = 1;
				PaddleMotor->CS.Home = 1;
	
				PaddleMotorTimer.IN = 1;
				PaddleMotor->STS.TimerStarted = 1;
			}
			else if(PaddleMotor->STS.EndButtonHit)
			{
				if(PaddleMotorTimer.Q && !PaddleMotor->STS.TimerEnded)
				{
					PaddleMotor->STS.TimerEnded = 1;
					
				}
				if(PaddleMotor->STS.TimerEnded && !PaddleMotor->STS.ReferenceSet)
				{
					PaddleMotor->STS.ReferenceSet = 1;
					PaddleMotor->CS.Home = 0;
					
					PaddleMotor->STS.ReferencePosition = PaddleMotor->STS.ActPosition + 25;
					PaddleMotor->PAR.Position = PaddleMotor->STS.ReferencePosition - MIDDLE_POSITION;
					PaddleMotor->CS.MoveAbsolute = 1;
				}
				if(PaddleMotor->STS.ActPosition <= PaddleMotor->PAR.Position && !PaddleMotor->STS.AlarmActive && !PaddleMotor->STS.Interlocked)
				{
					PaddleMotor->CS.MoveAbsolute = 0;
					PaddleMotor->STS.StateInt = STATE_IDLE;
				}
			}
			break;
		case STATE_IDLE:
			PaddleMotor->STS.Initializing = 0;
			PaddleMotor->STS.Idle = 1;

			PaddleMotor->CS.MoveAbsolute = 0;
			PaddleMotor->CS.MoveJogNeg = 0;
			PaddleMotor->CS.MoveJogPos = 0;
			
			if(PaddleMotor->CS.Start && !PaddleMotor->STS.AlarmActive && !PaddleMotor->STS.Interlocked)
			{
				PaddleMotor->STS.StateInt = STATE_RUNNING;			
			}
			break;
		case STATE_RUNNING:
			PaddleMotor->STS.Running = 1;
			PaddleMotor->STS.Idle = 0;

			if(!PaddleMotor->STS.AutoActive)
			{
				PaddleMotor->CS.MoveAbsolute = 0;
				PaddleMotor->CS.MoveJogNeg = 0;
				PaddleMotor->CS.MoveJogPos = 0;
				//control parameters
				if(PaddleMotor->HMI.IncreaseJogSpeed && PaddleMotor->PAR.JogVelocity < MAX_VELOCITY)
				{
					PaddleMotor->PAR.JogVelocity++;
				}
				else if(PaddleMotor->HMI.DecreaseJogSpeed && PaddleMotor->PAR.JogVelocity > MIN_VELOCITY)
				{
					PaddleMotor->PAR.JogVelocity--;
				}
				else if(PaddleMotor->HMI.IncreaseAccDec && PaddleMotor->PAR.Acceleration < MAX_ACC_DEC)
				{
					PaddleMotor->PAR.Acceleration += 10;
					PaddleMotor->PAR.Deceleration += 10;
				}
				else if(PaddleMotor->HMI.DecreaseAccDec && PaddleMotor->PAR.Deceleration > MIN_ACC_DEC)
				{
					PaddleMotor->PAR.Acceleration -= 10;
					PaddleMotor->PAR.Deceleration -= 10;
				}
			}			
			else
			{
				PaddleMotor->HMI.MoveAbsolute = 0;
				PaddleMotor->HMI.MoveJogNeg = 0;
				PaddleMotor->HMI.MoveJogPos = 0;
			}
			if(PaddleMotor->STS.ActPosition < MIN_POSITION + STOPPING_OFFSET)
			{
				PaddleMotor->CS.MoveJogNeg = 0;
				PaddleMotor->HMI.MoveJogNeg = 0;
				PaddleMotor->CS.MoveAbsolute = 0;
			}
			else if(PaddleMotor->IO.EndButton || PaddleMotor->STS.ActPosition >= (PaddleMotor->STS.ReferencePosition - STOPPING_OFFSET))
			{
				PaddleMotor->CS.MoveJogPos = 0;
				PaddleMotor->HMI.MoveJogPos = 0;
				PaddleMotor->CS.MoveAbsolute = 0;
			}
			break;
		case STATE_STOPPING:
			PaddleMotor->STS.Running = 0;
			PaddleMotor->STS.Initializing = 0;
			PaddleMotor->STS.Idle = 0;

			PaddleMotor->CS.MoveAbsolute = 0;
			PaddleMotor->CS.MoveJogNeg = 0;
			PaddleMotor->CS.MoveJogPos = 0;
			PaddleMotor->CS.Stop = 1;

			PaddleMotor->HMI.MoveJogNeg = 0;
			PaddleMotor->HMI.MoveJogPos = 0;

			if(PaddleMotor->STS.StandStill)
			{
				PaddleMotor->STS.StateInt = STATE_DISABLED;
			}	
			break;
	}
	
	//io mapping

	PaddleMotor->IO.Power = PaddleMotor->CS.Power;
	PaddleMotor->IO.Home = PaddleMotor->CS.Home;
	
	PaddleMotor->IO.JogVelocity = PaddleMotor->PAR.JogVelocity;
	PaddleMotor->IO.Acceleration = PaddleMotor->PAR.Acceleration;
	PaddleMotor->IO.Deceleration = PaddleMotor->PAR.Deceleration;
	PaddleMotor->IO.Velocity = PaddleMotor->PAR.Velocity;
	PaddleMotor->IO.Position = PaddleMotor->PAR.Position;
	PaddleMotor->IO.ErrorAcknowledge = PaddleMotor->HMI.ErrorAcknowledge;
	PaddleMotor->IO.MoveJogPos = PaddleMotor->CS.MoveJogPos ^ PaddleMotor->HMI.MoveJogPos;
	PaddleMotor->IO.MoveJogNeg = PaddleMotor->CS.MoveJogNeg ^ PaddleMotor->HMI.MoveJogNeg;
	PaddleMotor->IO.MoveAbsolute = PaddleMotor->CS.MoveAbsolute ^ PaddleMotor->HMI.MoveAbsolute;


	PaddleMotor->STS.AlarmActive = PaddleMotor->ALM.MotorError;
	PaddleMotor->STS.StandStill = (int)PaddleMotor->STS.ActVelocity == 0;
	PaddleMotor->STS.Moving = !PaddleMotor->STS.StandStill;
	PaddleMotor->STS.AutoActive = PaddleMotor->CS.AutoMode;
	
}
