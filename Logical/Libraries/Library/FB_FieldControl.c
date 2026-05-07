/*********************************************************************************
 * Copyright: MyAutomation-IT
 * Author:    raivo 
 * Created:   April 22, 2026/5:57 PM 
 *********************************************************************************/ 
#include <bur/plctypes.h>
#include "CommonTypes.h"
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif

#define MAX_ANGLE 18
#define MIN_ANGLE 3

#define FieldMotor inst->FieldMotor
#define FieldControl inst->FieldControl
#define InclinoSensor inst->InclinoSensor

#define STOPPING_SLOPE -0.068
#define STOPPING_OFFSET_BASE 1.3
#define STOPPING_OFFSET ((FieldControl->PAR.Angle * STOPPING_SLOPE) + STOPPING_OFFSET_BASE)

void FB_FieldControl(struct FB_FieldControl* inst)
{
	/* immediate stop override */
	if(FieldControl->CS.StopGame && !FieldControl->STS.AlarmActive && !FieldControl->STS.Interlocked)
	{
    	FieldControl->STS.StateInt = STATE_STOPPING;
	}

	switch(FieldControl->STS.StateInt)
	{
		case STATE_DISABLED:
		{
			FieldControl->STS.AtTargetPosition = 0;

			/* manual angle adjust */
			if(FieldControl->HMI.IncreaseAngle && FieldControl->PAR.Angle < MAX_ANGLE)
			{
				FieldControl->PAR.Angle += 0.002;
			}
			else if(FieldControl->HMI.DecreaseAngle && FieldControl->PAR.Angle > MIN_ANGLE)
			{
				FieldControl->PAR.Angle -= 0.002;
			}
			if(FieldControl->STS.Initializing)
			{
				FieldControl->STS.StateInt = STATE_INITIALIZING;
			}
			break;
		}
		case STATE_INITIALIZING:
		{
			if(FieldControl->STS.Idle)
			{
				FieldControl->STS.StateInt = STATE_IDLE;
			}
			/* target alignment detect */
			else if((FieldControl->STS.CurrentAngle + STOPPING_OFFSET >= FieldControl->PAR.Angle) && !FieldControl->STS.AtTargetPosition && FieldMotor->STS.EndButtonHit)
			{	
				FieldControl->STS.AtTargetPosition = 1;
			}
			break;
		}
		case STATE_IDLE:
		{
			if(FieldControl->STS.Running)
			{
				FieldControl->STS.StateInt = STATE_RUNNING;
			}
			break;
		}
		case STATE_RUNNING:
		{
			/* motor safety clamp */
			FieldMotor->CS.Stop = 0;

			if(FieldControl->STS.CurrentAngle >= MAX_ANGLE)
			{
				FieldMotor->HMI.MoveJogNeg = 0;
			}
			else if(FieldControl->STS.CurrentAngle <= MIN_ANGLE)
			{
				FieldMotor->HMI.MoveJogPos = 0;
			}

			break;
		}
		case STATE_STOPPING:
		{
			if(FieldControl->STS.Disabled)
			{
				FieldControl->STS.StateInt = STATE_DISABLED;
			}
			break;
		}
	}

	/* command forwarding */
	FieldMotor->CS.Initialize = FieldControl->CS.Initialize;
	FieldMotor->CS.Start = FieldControl->CS.Start;
	FieldMotor->CS.StopGame = FieldControl->CS.StopGame;
	FieldMotor->CS.ErrorAcknowledge = FieldControl->CS.ErrorAcknowledge;
	FieldMotor->STS.AtTargetPosition = FieldControl->STS.AtTargetPosition;
	
	/* sensor mapping */
	FieldControl->STS.CurrentAngle = InclinoSensor->STS.CurrentAngle;

	/* subsystem state mapping */
	FieldControl->STS.Disabled = FieldMotor->STS.Disabled;
	FieldControl->STS.AlarmActive = FieldMotor->STS.AlarmActive || InclinoSensor->STS.AlarmActive;
	FieldControl->STS.Interlocked = FieldMotor->STS.Interlocked;
	FieldControl->STS.Idle = FieldMotor->STS.Idle;
	FieldControl->STS.Running = FieldMotor->STS.Running;
	FieldControl->STS.Moving = FieldMotor->STS.Moving;
	FieldControl->STS.Initializing = FieldMotor->STS.Initializing;

	/* shared calibration command */
	FieldControl->CS.SetCenterPoint = FieldMotor->CS.SetCenterPoint;
	InclinoSensor->CS.SetCenterPoint = FieldMotor->CS.SetCenterPoint;

}
