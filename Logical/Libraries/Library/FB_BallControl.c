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

#define BallControl inst->BallControl
#define PaddleMotor inst->PaddleMotor
#define Shooter inst->Shooter

#define LEFT_SENSOR 1
#define MIDDLE_SENSOR 2
#define RIGHT_SENSOR 3

#define MM_TO_POSITION 11.2
#define MIN_POSITION PaddleMotor->STS.ReferencePosition - 2800
#define MAX_POSITION PaddleMotor->STS.ReferencePosition - 100
#define AUTOMODE_VELOCITY 5000
#define MIN_FIELD_DISTANCE 50

#define DISTANCE_BETWEEN_SENSORS_MM 24
#define DISTANCE_SENSOR_LEFT_TO_PADDLE_MM 75

_LOCAL TON_typ SpeedTimer;
_LOCAL TON_typ ShootTimer;
_LOCAL TON_typ ShootDelayTimer;
_LOCAL TON_typ NewShootCycleTimer;
_LOCAL BOOL firstRun;



/* TODO: Add your comment here */
void FB_BallControl(struct FB_BallControl* inst)
{
	BallControl->STS.ShootCycleCompleted = 0;

	if(BallControl->CS.StopGame)
	{
		BallControl->STS.StateInt = STATE_STOPPING;
	}

	switch(BallControl->STS.StateInt)
	{
		case STATE_DISABLED:
		{
			BallControl->CS.Shoot = 0;
			//BallControl->CS.StopGame = 0;
			if(BallControl->STS.Initializing)
			{
				BallControl->STS.StateInt = STATE_INITIALIZING;
			}
			break;
		}
		case STATE_INITIALIZING:
		{
			BallControl->STS.PrevShootState = 0;
			BallControl->STS.ShootState = 0;
			BallControl->STS.GameOver = 0;
			firstRun = 1;
			if(BallControl->STS.Idle)
			{
				BallControl->STS.StateInt = STATE_IDLE;
			}
			break;
		}
		case STATE_IDLE:
		{
			NewShootCycleTimer.IN = 0;
			if(BallControl->STS.Running)
			{
				BallControl->STS.StateInt = STATE_RUNNING;
			}
			break;
		}
		case STATE_RUNNING:
		{
			if(BallControl->STS.AutoActive)
			{
				PaddleMotor->CS.MoveAbsolute = 0;
				Shooter->CS.EnableFan = 1;
				
				PaddleMotor->PAR.Velocity = AUTOMODE_VELOCITY;

				if(ShootDelayTimer.Q)
				{
					BallControl->CS.Shoot = 0;
					ShootDelayTimer.IN = 0;
				}

				BallControl->STS.NewShootCycleTimerET = NewShootCycleTimer.ET;
				switch(BallControl->STS.ShootState)
				{
					case 0:
					{
						SpeedTimer.IN = 0;

						if(firstRun)
						{
							if(inst->DistanceSensorRight->STS.BallDetected)
							{
								BallControl->PAR.DesiredPosition = MIN_POSITION + ((inst->DistanceSensorRight->STS.Distance - MIN_FIELD_DISTANCE) * MM_TO_POSITION);

								BallControl->STS.ShootState = 5;
								firstRun = 0;
							}
						}
						else
						{
							if(NewShootCycleTimer.Q)
							{
								NewShootCycleTimer.IN = 0;
								BallControl->STS.GameOver = 1;
							}
							else if(NewShootCycleTimer.ET >= 500)
							{
								if(inst->DistanceSensorRight->STS.BallDetected)
								{
									BallControl->PAR.DesiredPosition = MIN_POSITION + ((inst->DistanceSensorRight->STS.Distance - MIN_FIELD_DISTANCE) * MM_TO_POSITION);

									NewShootCycleTimer.IN = 0;
									BallControl->STS.ShootState = 5;
								}
							}
							
						}
					}
					break;

					case 5:
						SpeedTimer.PT = 5000;
						SpeedTimer.IN = 1; 
						BallControl->STS.ShootState = 10;
					break;

					case 10:
						if(inst->DistanceSensorMiddle->STS.BallDetected)
						{
							BallControl->PAR.DesiredPosition = MIN_POSITION + ((inst->DistanceSensorMiddle->STS.Distance - MIN_FIELD_DISTANCE) * MM_TO_POSITION);
							if(BallControl->PAR.DesiredPosition >= MIN_POSITION && BallControl->PAR.DesiredPosition <= MAX_POSITION)
								{
									//PaddleMotor->PAR.Position = BallControl->PAR.DesiredPosition;
									//PaddleMotor->CS.MoveAbsolute = 1;
								}
							BallControl->STS.ShootState = 20;
						}
						break;

					case 20:
						if(inst->DistanceSensorLeft->STS.BallDetected)
						{
							SpeedTimer.IN = 0;

							if(SpeedTimer.ET > 0)
							{
								BallControl->STS.BallVelocity = (DISTANCE_BETWEEN_SENSORS_MM * 2.0f) / (float)SpeedTimer.ET;

								
								BallControl->STS.TimeToPaddleMS = SpeedTimer.ET;//(DISTANCE_SENSOR_LEFT_TO_PADDLE_MM / BallControl->STS.BallVelocity);

								ShootTimer.PT = BallControl->STS.TimeToPaddleMS;
							}
							else
							{
								BallControl->STS.BallVelocity = 0.0f;
								ShootTimer.PT = 0;
							}

							ShootTimer.IN = 1;

							BallControl->PAR.DesiredPosition = MIN_POSITION + ((inst->DistanceSensorLeft->STS.Distance - MIN_FIELD_DISTANCE) * MM_TO_POSITION);
							
							if(BallControl->PAR.DesiredPosition >= MIN_POSITION && BallControl->PAR.DesiredPosition <= MAX_POSITION)
							{
								//PaddleMotor->PAR.Position = BallControl->PAR.DesiredPosition;
								//PaddleMotor->CS.MoveAbsolute = 1;
							}

							BallControl->STS.ShootState = 30;
						}
					break;

					case 30: 
						if(ShootTimer.Q)
						{
							BallControl->CS.Shoot = 1;

							ShootTimer.IN = 0;

							BallControl->STS.ShootState = 0;
							ShootDelayTimer.PT = 300;
							ShootDelayTimer.IN = 1;
						}
					break;
				}

				if (BallControl->STS.PrevShootState == 30 && BallControl->STS.ShootState == 0)
				{
					NewShootCycleTimer.IN = 1;
					NewShootCycleTimer.PT = 5000;
					BallControl->STS.ShootCycleCompleted = 1;
				}

				TON(&ShootTimer);
				TON(&SpeedTimer);
				TON(&ShootDelayTimer);
				TON(&NewShootCycleTimer);
			}
			else
			{
				BallControl->CS.Shoot = 0;
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

	BallControl->STS.PrevShootState = BallControl->STS.ShootState;

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
