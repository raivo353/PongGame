
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif

#define STATE_DISABLED 00
#define STATE_INITIALIZING 10
#define STATE_IDLE 20
#define STATE_RUNNING 30
#define STATE_STOPPING 40

#define MAX_ANGLE 19
#define MIN_ANGLE 3

#define FieldMotor inst->FieldMotor
#define FieldControl inst->FieldControl
#define InclinoSensor inst->InclinoSensor

/* TODO: Add your comment here */
void FB_FieldControl(struct FB_FieldControl* inst)
{

	if(FieldControl->CS.StopGame)
	{
		FieldControl->STS.StateInt = STATE_STOPPING;
	}

	switch(FieldControl->STS.StateInt)
	{
		case STATE_DISABLED:
		{
			FieldControl->STS.AtTargetPosition = 0;

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
			else if((FieldControl->STS.CurrentAngle + 0.65 >= FieldControl->PAR.Angle) && !FieldControl->STS.AtTargetPosition && FieldMotor->STS.EndButtonHit)
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



	/*TODO: Add your code here*/
	FieldMotor->CS.Initialize = FieldControl->CS.Initialize;
	FieldMotor->CS.Start = FieldControl->CS.Start;
	FieldMotor->CS.StopGame = FieldControl->CS.StopGame;
	FieldMotor->CS.ErrorAcknowledge = FieldControl->CS.ErrorAcknowledge;
	FieldMotor->STS.AtTargetPosition = FieldControl->STS.AtTargetPosition;
	
	FieldControl->STS.CurrentAngle = InclinoSensor->STS.CurrentAngle;
	FieldControl->STS.Disabled = FieldMotor->STS.Disabled;
	FieldControl->STS.AlarmActive = FieldMotor->STS.AlarmActive;
	FieldControl->STS.Idle = FieldMotor->STS.Idle;
	FieldControl->STS.Running = FieldMotor->STS.Running;
	FieldControl->STS.Moving = FieldMotor->STS.Moving;
	FieldControl->STS.Initializing = FieldMotor->STS.Initializing;

	FieldControl->CS.SetCenterPoint = FieldMotor->CS.SetCenterPoint;
	InclinoSensor->CS.SetCenterPoint = FieldControl->CS.SetCenterPoint;
}
