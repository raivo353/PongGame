
#include <bur/plctypes.h>
#include <standard.h>
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
#define MAX_JOG_VELOCITY 4000
#define MAX_ACC_DEC 20000
#define MIN_ACC_DEC 100
#define MAX_POSITION 220

#define STATE_DISABLED 00
#define STATE_INITIALIZING 10
#define STATE_IDLE 20
#define STATE_RUNNING 30
#define STATE_STOPPING 40

_LOCAL TON_typ TON_01;

/* TODO: Add your comment here */
void FB_PaddleMotor(struct FB_PaddleMotor* inst)
{
	
	/*TODO: Add your code here*/
	inst->PaddleMotor->IO.EndButton = !((inst->digitalInput & ENDBUTTON_BITMASK) >> 1);
	//inst->PaddleMotor->STS.ActPosition = inst->PaddleMotor->STS.ActPosition;
	
	switch(inst->PaddleMotor->STS.StateInt)
	{
		case STATE_DISABLED:
			inst->PaddleMotor->CS.Power = 0;
			inst->PaddleMotor->CS.Home = 0;
			inst->PaddleMotor->STS.EndButtonHit = 0;
			inst->PaddleMotor->CS.MoveJogNeg = 0;
			inst->PaddleMotor->CS.MoveJogPos = 0;
			inst->PaddleMotor->CS.MoveAbsolute = 0;
			inst->TimerStarted = 0;
			TON_01.IN = 0;
			TON(&TON_01);
			if(inst->PaddleMotor->CS.Initialize)
			{
				inst->PaddleMotor->STS.StateInt = STATE_INITIALIZING;
			}
			
			inst->PaddleMotor->IO.MoveJogNeg = inst->PaddleMotor->CS.MoveJogNeg;
			inst->PaddleMotor->IO.MoveJogPos = inst->PaddleMotor->CS.MoveJogPos;
			inst->PaddleMotor->IO.MoveAbsolute = inst->PaddleMotor->CS.MoveAbsolute;
			break;
		case STATE_INITIALIZING:
			inst->PaddleMotor->CS.Power = 1;
			inst->PaddleMotor->STS.AutoActive = 0;
			inst->PaddleMotor->CS.Initialize = 0;
			
			if(inst->PaddleMotor->CS.StopGame)
			{
				inst->PaddleMotor->STS.StateInt = STATE_STOPPING;
			}

			if(!inst->PaddleMotor->IO.EndButton && !inst->PaddleMotor->STS.EndButtonHit)
			{
				inst->PaddleMotor->CS.Home = 1;
			
				if(inst->TimerStarted == 0)
				{
					TON_01.IN = 1;
					inst->TimerStarted = 1;
				}
				TON_01.PT = 1000;
				TON(&TON_01);
			
				if(TON_01.Q)
				{
					inst->PaddleMotor->CS.Home = 0;
					inst->PaddleMotor->CS.MoveJogPos = 1;
				}
			}
			else if(inst->PaddleMotor->IO.EndButton && !inst->PaddleMotor->STS.EndButtonHit)
			{
				TON_01.IN = 0;
				inst->TimerStarted = 0;
			
				inst->PaddleMotor->CS.MoveJogPos = 0;
				inst->PaddleMotor->STS.EndButtonHit = 1;
				inst->PaddleMotor->CS.Home = 1;
	
				TON_01.PT = 1000;
				TON_01.IN = 1;
				inst->TimerStarted = 1;
			}
			else if(inst->PaddleMotor->STS.EndButtonHit)
			{
				if(TON_01.Q)
				{
					inst->PaddleMotor->CS.Home = 0;
					inst->PaddleMotor->PAR.Position = inst->PaddleMotor->STS.ActPosition - 1400;
					inst->PaddleMotor->CS.MoveAbsolute = 1;
				}
				if(inst->PaddleMotor->STS.ActPosition >= inst->PaddleMotor->PAR.Position)
				{
					inst->PaddleMotor->STS.StateInt = STATE_IDLE;
				}
			}
			
			
			break;
		case STATE_IDLE:
			inst->PaddleMotor->IO.MoveAbsolute = 0;
			inst->PaddleMotor->IO.MoveJogNeg = 0;
			inst->PaddleMotor->IO.MoveJogPos = 0;
			
			inst->PaddleMotor->STS.Initializing = 0;
			
			if(inst->PaddleMotor->CS.StopGame)
			{
				inst->PaddleMotor->STS.StateInt = STATE_STOPPING;
			}
			if(inst->PaddleMotor->CS.Start && !inst->PaddleMotor->STS.AlarmActive && !inst->PaddleMotor->STS.Interlocked)
			{
				inst->PaddleMotor->STS.StateInt = STATE_RUNNING;
			}
			break;
		case STATE_RUNNING:
			if(inst->PaddleMotor->CS.StopGame)
			{
				inst->PaddleMotor->STS.StateInt = STATE_STOPPING;
			}

			if(!inst->PaddleMotor->STS.AutoActive)
			{
				inst->PaddleMotor->CS.MoveAbsolute = 0;
				//control parameters
				if(inst->PaddleMotor->HMI.IncreaseJogSpeed && inst->PaddleMotor->PAR.JogVelocity < MAX_JOG_VELOCITY)
				{
					inst->PaddleMotor->PAR.JogVelocity++;
				}
				else if(inst->PaddleMotor->HMI.DecreaseJogSpeed && inst->PaddleMotor->PAR.JogVelocity > 0)
				{
					inst->PaddleMotor->PAR.JogVelocity--;
				}
				else if(inst->PaddleMotor->HMI.IncreaseAccDec && inst->PaddleMotor->PAR.Acceleration < MAX_ACC_DEC)
				{
					inst->PaddleMotor->PAR.Acceleration += 10;
					inst->PaddleMotor->PAR.Deceleration += 10;
				}
				else if(inst->PaddleMotor->HMI.DecreaseAccDec && inst->PaddleMotor->PAR.Deceleration > MIN_ACC_DEC)
				{
					inst->PaddleMotor->PAR.Acceleration -= 10;
					inst->PaddleMotor->PAR.Deceleration -= 10;
				}

				//moving controls
				if(inst->PaddleMotor->STS.ActPosition < MAX_POSITION)
				{
					inst->PaddleMotor->IO.MoveJogNeg = inst->PaddleMotor->HMI.MoveJogNeg;
				}
				if(inst->PaddleMotor->STS.ActPosition >= 0 && !inst->PaddleMotor->IO.EndButton)
				{
					inst->PaddleMotor->IO.MoveJogPos = inst->PaddleMotor->HMI.MoveJogPos;
				}
				
				//inst->PaddleMotor->IO.MoveAbsolute = inst->PaddleMotor->HMI.MoveAbsolute;
			}			
			else
			{
				if(inst->PaddleMotor->STS.ActPosition < MAX_POSITION)
				{
					inst->PaddleMotor->IO.MoveJogPos = inst->PaddleMotor->CS.MoveJogPos;
				}
				if(inst->PaddleMotor->STS.ActPosition >= 0 && !inst->PaddleMotor->IO.EndButton)
				{
					inst->PaddleMotor->IO.MoveJogNeg = inst->PaddleMotor->CS.MoveJogNeg;
				}
				inst->PaddleMotor->IO.MoveAbsolute = inst->PaddleMotor->CS.MoveAbsolute;
			}
			break;
		case STATE_STOPPING:
			inst->PaddleMotor->IO.MoveAbsolute = 0;
			inst->PaddleMotor->CS.MoveAbsolute = 0;
			inst->PaddleMotor->IO.MoveJogNeg = 0;
			inst->PaddleMotor->CS.MoveJogNeg = 0;
			inst->PaddleMotor->IO.MoveJogPos = 0;
			inst->PaddleMotor->CS.MoveJogPos = 0;
			inst->PaddleMotor->STS.StateInt = STATE_DISABLED;
			break;
	}
	 
	//io mapping

	inst->PaddleMotor->IO.Power = inst->PaddleMotor->CS.Power;
	inst->PaddleMotor->IO.Home = inst->PaddleMotor->CS.Home;
	
	inst->PaddleMotor->IO.JogVelocity = inst->PaddleMotor->PAR.JogVelocity;
	inst->PaddleMotor->IO.Acceleration = inst->PaddleMotor->PAR.Acceleration;
	inst->PaddleMotor->IO.Deceleration = inst->PaddleMotor->PAR.Deceleration;
	inst->PaddleMotor->IO.Velocity = inst->PaddleMotor->PAR.Velocity;
	inst->PaddleMotor->IO.Position = inst->PaddleMotor->PAR.Position;
	inst->PaddleMotor->IO.ErrorAcknowledge = inst->PaddleMotor->HMI.ErrorAcknowledge;
	inst->PaddleMotor->IO.MoveJogPos = inst->PaddleMotor->CS.MoveJogPos;
	inst->PaddleMotor->IO.MoveJogNeg = inst->PaddleMotor->CS.MoveJogNeg;
	inst->PaddleMotor->IO.MoveAbsolute = inst->PaddleMotor->CS.MoveAbsolute;


	



}
