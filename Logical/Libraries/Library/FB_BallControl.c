
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

#define BallControl inst->BallControl
#define PaddleMotor inst->PaddleMotor
#define Shooter inst->Shooter

#define LEFT_SENSOR 1
#define MIDDLE_SENSOR 2
#define RIGHT_SENSOR 3

#define MM_TO_POSITION 10
#define MIN_POSITION PaddleMotor->STS.ReferencePosition - 2800

_LOCAL TON_typ SpeedTimer;
_LOCAL TON_typ ShootTimer;

/* TODO: Add your comment here */
void FB_BallControl(struct FB_BallControl* inst)
{
	if(BallControl->CS.StopGame)
	{
		BallControl->STS.StateInt = STATE_STOPPING;
	}

	switch(BallControl->STS.StateInt)
	{
		case STATE_DISABLED:
		{
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
			Shooter->CS.EnableFan = 1;
			if(BallControl->STS.AutoActive)
			{
				switch(BallControl->STS.ShootState)
				{
					case 0: 
					BallControl->CS.Shoot = 0;
					ShootTimer.IN = 0;
					SpeedTimer.IN = 0;
					if(inst->DistanceSensorRight->STS.BallDetected)
					{
						PaddleMotor->PAR.Position = MIN_POSITION + ((inst->DistanceSensorRight->STS.Distance - 50) * MM_TO_POSITION);
						PaddleMotor->CS.MoveAbsolute = 1;
						PaddleMotor->PAR.Velocity = 5000;
						BallControl->STS.SpeedTimeElapsed = 0;
						BallControl->STS.ShootState = 5;  // eerst naar 5
					}
					break;

					case 5:
						SpeedTimer.PT = 5000;
						SpeedTimer.IN = 1;  // volgende cyclus pikt TON dit op
						BallControl->STS.ShootState = 20;
						break;

					case 20:
						if(inst->DistanceSensorLeft->STS.BallDetected)
						{
							PaddleMotor->PAR.Position = MIN_POSITION + ((inst->DistanceSensorLeft->STS.Distance - 50) * MM_TO_POSITION);
							BallControl->CS.Shoot = 1;
							ShootTimer.IN = 1;
							ShootTimer.PT = 300;
							BallControl->STS.SpeedTimeElapsed = SpeedTimer.ET;
							BallControl->STS.ShootState = 30;
						}
						break;

					case 30: 
						BallControl->CS.Shoot = 1;
						ShootTimer.IN = 1;

						if(ShootTimer.Q)
						{
							BallControl->CS.Shoot = 0;
							ShootTimer.IN = 0;

							BallControl->STS.ShootState = 0;
						}
						break;

					default:
						// fallback veiligheid
						BallControl->CS.Shoot = 0;
						ShootTimer.IN = 0;
						BallControl->STS.ShootState = 0;
						break;
				}
				TON(&ShootTimer);
				TON(&SpeedTimer);
			}
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

	Shooter->CS.Start = BallControl->CS.Initialize;
	Shooter->CS.StopGame = BallControl->CS.StopGame;
	Shooter->CS.AutoMode = BallControl->CS.AutoMode;
	Shooter->CS.Shoot = BallControl->CS.Shoot;

	BallControl->STS.Idle = PaddleMotor->STS.Idle && Shooter->STS.Idle;
	BallControl->STS.AutoActive = PaddleMotor->STS.AutoActive && Shooter->STS.AutoActive;
	BallControl->STS.Disabled = PaddleMotor->STS.Disabled && Shooter->STS.Disabled;
	BallControl->STS.Initializing = PaddleMotor->STS.Initializing;
	BallControl->STS.Running = PaddleMotor->STS.Running;
	BallControl->STS.Interlocked = PaddleMotor->STS.Interlocked || Shooter->STS.Interlocked;
	BallControl->STS.AlarmActive = PaddleMotor->STS.AlarmActive || Shooter->STS.AlarmActive 
																|| inst->DistanceSensorLeft->STS.AlarmActive 															
																|| inst->DistanceSensorMiddle->STS.AlarmActive 
																|| inst->DistanceSensorRight->STS.AlarmActive;
	
}
