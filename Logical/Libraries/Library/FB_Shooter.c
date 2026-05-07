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


#define STATE_SHOOTING 30
#define SHOOT_OUTPUT_BIT 3
#define FAN_OUTPUT_BIT 0

#define Shooter inst->Shooter

void FB_Shooter(struct FB_Shooter* inst)
{
	/* stop request handling */
	if(Shooter->CS.StopGame && !Shooter->STS.Interlocked)
	{
		Shooter->STS.StateInt = STATE_DISABLED;
	}

	Shooter->STS.AlarmActiveColour = Shooter->STS.Interlocked ? RED_COLOUR : GREEN_COLOUR;
	
	switch (Shooter->STS.StateInt)
	{
		case STATE_DISABLED:
			/* Reset outputs and states */
			Shooter->STS.Disabled = 1;
			Shooter->STS.Idle = 0;

			Shooter->HMI.Shoot = 0;
			Shooter->HMI.EnableFan = 0;

			Shooter->CS.Shoot = 0;
			Shooter->CS.EnableFan = 0;
			Shooter->CS.Interlock = 0;

			/* Allow parameter tuning only when inactive */
			if(Shooter->HMI.IncreaseIntensity)
			{
				Shooter->PAR.Intensity += 0.1;
			}
			else if(Shooter->HMI.DecreaseIntensity)
			{
				Shooter->PAR.Intensity -= 0.1;
			}
			if(Shooter->CS.Start && !Shooter->STS.AlarmActive && !Shooter->STS.Interlocked)
			{
				Shooter->STS.StateInt = STATE_IDLE;
			}
			break;

		case STATE_IDLE:
			Shooter->STS.Idle = 1;
			Shooter->STS.Disabled = 0;
			Shooter->STS.Shooting = 0;
			
			Shooter->CS.Interlock = 0;

			if(Shooter->STS.AutoActive)
			{
				/* Ignore HMI in auto mode */
				Shooter->HMI.Shoot = 0;
			}	
			else
			{
				/* Fan required before shooting */
				if(!Shooter->HMI.EnableFan)
				{
					Shooter->CS.Interlock = 1;
				}
				Shooter->CS.Shoot = 0;
			}

			/* XOR detects difference between HMI and control command */
			if((Shooter->HMI.Shoot ^ Shooter->CS.Shoot) && !Shooter->STS.AlarmActive && !Shooter->STS.Interlocked)
			{
				Shooter->STS.StateInt = STATE_SHOOTING;
			}
			break;

		case STATE_SHOOTING:
			Shooter->STS.Shooting = 1;

			/* Return when no shoot request remains */
			if(!Shooter->CS.Shoot && !Shooter->HMI.Shoot && !Shooter->STS.AlarmActive && !Shooter->STS.Interlocked)
			{
				Shooter->STS.StateInt = STATE_IDLE;
			}
			break;
	}

	/* Block output if unsafe */
	if(!Shooter->STS.Interlocked && !Shooter->STS.AlarmActive)
	{
		Shooter->IO.Shoot = Shooter->HMI.Shoot ^ Shooter->CS.Shoot;
	}
	
	Shooter->IO.EnableFan = Shooter->HMI.EnableFan ^ Shooter->CS.EnableFan;

	/* Map control state to status */
	Shooter->STS.Interlocked = Shooter->CS.Interlock;
	Shooter->STS.AutoActive = Shooter->CS.AutoMode;

	/* Map logical outputs to physical bits */
	inst->digitalOutput = 0;
	inst->digitalOutput |= (Shooter->IO.Shoot << SHOOT_OUTPUT_BIT);
	inst->digitalOutput |= (Shooter->IO.EnableFan << FAN_OUTPUT_BIT);
	
}
