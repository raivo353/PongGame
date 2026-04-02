
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

#define ENDBUTTON_BITMASK 0x4
#define MAX_JOG_VELOCITY 1000
#define MIN_POSITION FieldMotor->STS.ReferencePosition - 2800

#define STATE_DISABLED 00
#define STATE_INITIALIZING 10
#define STATE_IDLE 20
#define STATE_RUNNING 30
#define STATE_STOPPING 40

#define FieldMotor inst->FieldMotor

_LOCAL TON_typ TON_02;

/* TODO: Add your comment here */
void FB_FieldMotor(struct FB_FieldMotor* inst)
{
	/*TODO: Add your code here*/
	FieldMotor->IO.EndButton = !((inst->digitalInput & ENDBUTTON_BITMASK) >> 2);
	

	if(FieldMotor->CS.StopGame)
	{
		FieldMotor->STS.StateInt = STATE_STOPPING;
	}

	switch(FieldMotor->STS.StateInt)
	{
		case STATE_DISABLED:
			FieldMotor->STS.Disabled = 1;

			FieldMotor->CS.Power = 0;
			FieldMotor->CS.Home = 0;
			FieldMotor->STS.EndButtonHit = 0;
			FieldMotor->CS.MoveJogNeg = 0;
			FieldMotor->CS.MoveJogPos = 0;
			FieldMotor->CS.MoveAbsolute = 0;
			FieldMotor->STS.TimerStarted = 0;
			FieldMotor->STS.TimerEnded = 0;
			FieldMotor->STS.ReferencePosition = 0;

			TON_02.IN = 0;
			TON(&TON_02);

			if(FieldMotor->CS.Initialize && !FieldMotor->STS.AlarmActive && !FieldMotor->STS.Interlocked)
			{
				FieldMotor->STS.StateInt = STATE_INITIALIZING;
			}
			break;
		case STATE_INITIALIZING:
			FieldMotor->STS.Initializing = 1;
			FieldMotor->STS.Disabled = 0;

			FieldMotor->CS.Power = 1;

			if(!FieldMotor->IO.EndButton && !FieldMotor->STS.EndButtonHit) 
			{
				FieldMotor->CS.Home = 1; 
				if(!FieldMotor->STS.TimerStarted) 
				{ 
					TON_02.IN = 1; 
					FieldMotor->STS.TimerStarted = 1;
					FieldMotor->CS.SetCenterPoint = 1; 
				} 
				TON_02.PT = 100; 
				TON(&TON_02); 
			
				if(TON_02.Q) 
				{ 
					FieldMotor->CS.Home = 0; 
					FieldMotor->CS.MoveJogPos = 1;
					FieldMotor->CS.SetCenterPoint = 0;
				} 
			}
			else if(FieldMotor->IO.EndButton && !FieldMotor->STS.EndButtonHit)
			{
				TON_02.IN = 0;
				FieldMotor->STS.TimerStarted = 0;
			
				FieldMotor->CS.MoveJogPos = 0;
				FieldMotor->STS.EndButtonHit = 1;
				FieldMotor->CS.Home = 1;
	
				TON_02.IN = 1;
				FieldMotor->STS.TimerStarted = 1;
			}
			else if(FieldMotor->STS.EndButtonHit)
			{
				if(TON_02.Q && !FieldMotor->STS.TimerEnded)
				{
					FieldMotor->STS.TimerEnded = 1;
					FieldMotor->CS.Home = 0;
					//FieldMotor->PAR.Position = FieldMotor->STS.ActPosition - 1400;
					//FieldMotor->STS.ReferencePosition = FieldMotor->STS.ActPosition;
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
			FieldMotor->STS.Initializing = 0;
			FieldMotor->STS.Idle = 1;

			FieldMotor->CS.MoveAbsolute = 0;
			FieldMotor->CS.MoveJogNeg = 0;
			FieldMotor->CS.MoveJogPos = 0;
			
			if(FieldMotor->CS.Start && !FieldMotor->STS.AlarmActive && !FieldMotor->STS.Interlocked)
			{
				FieldMotor->STS.StateInt = STATE_RUNNING;
			}
			break;
		case STATE_RUNNING:
			FieldMotor->STS.Running = 1;
			FieldMotor->STS.Idle = 0;


			// else if(!FieldMotor->STS.AutoActive)
			// {
			// 	FieldMotor->CS.MoveAbsolute = 0;
			// 	FieldMotor->CS.MoveJogNeg = 0;
			// 	FieldMotor->CS.MoveJogPos = 0;
			// 	//control parameters
			// 	if(FieldMotor->HMI.IncreaseJogSpeed && FieldMotor->PAR.JogVelocity < MAX_JOG_VELOCITY)
			// 	{
			// 		FieldMotor->PAR.JogVelocity++;
			// 	}
			// 	else if(FieldMotor->HMI.DecreaseJogSpeed && FieldMotor->PAR.JogVelocity > 0)
			// 	{
			// 		FieldMotor->PAR.JogVelocity--;
			// 	}
			// }			
			// else
			// {
			// 	FieldMotor->HMI.MoveAbsolute = 0;
			// 	FieldMotor->HMI.MoveJogNeg = 0;
			// 	FieldMotor->HMI.MoveJogPos = 0;
			// }
			// if(FieldMotor->STS.ActPosition < MIN_POSITION)
			// {
			// 	FieldMotor->CS.MoveJogNeg = 0;
			// 	FieldMotor->HMI.MoveJogNeg = 0;
			// 	FieldMotor->CS.MoveAbsolute = 0;
			// }
			// else if(FieldMotor->IO.EndButton || FieldMotor->STS.ActPosition >= FieldMotor->STS.ReferencePosition - 50)
			// {
			// 	FieldMotor->CS.MoveJogPos = 0;
			// 	FieldMotor->HMI.MoveJogPos = 0;
			// 	FieldMotor->CS.MoveAbsolute = 0;
			// }
			break;
		case STATE_STOPPING:
			FieldMotor->STS.Running = 0;
			FieldMotor->STS.Idle = 0;
			FieldMotor->STS.Initializing = 0;
			
			FieldMotor->CS.MoveAbsolute = 0;
			FieldMotor->CS.MoveJogNeg = 0;
			FieldMotor->CS.MoveJogPos = 0;

			FieldMotor->STS.StateInt = STATE_DISABLED;
			break;
	}
	 
	//io mapping

	FieldMotor->IO.Power = FieldMotor->CS.Power;
	FieldMotor->IO.Home = FieldMotor->CS.Home;
	
	FieldMotor->IO.JogVelocity = FieldMotor->PAR.JogVelocity;
	FieldMotor->IO.Acceleration = FieldMotor->PAR.Acceleration;
	FieldMotor->IO.Deceleration = FieldMotor->PAR.Deceleration;
	FieldMotor->IO.Velocity = FieldMotor->PAR.Velocity;
	FieldMotor->IO.Position = FieldMotor->PAR.Position;
	FieldMotor->IO.ErrorAcknowledge = FieldMotor->HMI.ErrorAcknowledge;
	FieldMotor->IO.MoveJogPos = FieldMotor->CS.MoveJogPos ^ FieldMotor->HMI.MoveJogPos;
	FieldMotor->IO.MoveJogNeg = FieldMotor->CS.MoveJogNeg ^ FieldMotor->HMI.MoveJogNeg;
	FieldMotor->IO.MoveAbsolute = FieldMotor->CS.MoveAbsolute ^ FieldMotor->HMI.MoveAbsolute;
}
