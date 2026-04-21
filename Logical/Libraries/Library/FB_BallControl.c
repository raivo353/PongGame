
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

_LOCAL TON_typ SpeedTimer;
_LOCAL TON_typ ShootTimer;
//_LOCAL BOOL prevBallDetected;

/* TODO: Add your comment here */
void FB_BallControl(struct FB_BallControl* inst)
{
	BallControl->STS.ShootTimeElapsed = ShootTimer.ET;
	BallControl->STS.DelayTimeElapsed = SpeedTimer.ET;
	/*TODO: Add your code here*/
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
				TON(&ShootTimer);

				switch(BallControl->STS.ShootState)
				{
					case 0: 
						BallControl->CS.Shoot = 0;
						ShootTimer.IN = 0;

						if(inst->DistanceSensorRight->STS.BallDetected)
						{
							BallControl->STS.ShootState = 1;
						}
						break;

					case 1: 
						if(!inst->DistanceSensorRight->STS.BallDetected)
						{
							BallControl->STS.ShootState = 10;
						}
						break;

					case 10:
						if(inst->DistanceSensorMiddle->STS.BallDetected)
						{
							BallControl->STS.ShootState = 11;
						}
						break;

					case 11:
						if(!inst->DistanceSensorMiddle->STS.BallDetected)
						{
							BallControl->STS.ShootState = 20;
						}
						break;

					case 20:
						if(inst->DistanceSensorLeft->STS.BallDetected)
						{
							BallControl->CS.Shoot = 1;
							ShootTimer.IN = 1;
							ShootTimer.PT = 500; // 500 ms

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
