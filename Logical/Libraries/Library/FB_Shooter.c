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


#define STATE_SHOOTING 50

#define Shooter inst->Shooter

/* TODO: Add your comment here */
void FB_Shooter(struct FB_Shooter* inst)
{
	if(Shooter->CS.StopGame)
	{
		Shooter->STS.StateInt = STATE_DISABLED;
	}

	Shooter->STS.AlarmActiveColour = GREEN_COLOUR;
	if(Shooter->STS.AlarmActive)
	{
		Shooter->STS.AlarmActiveColour = RED_COLOUR;
	}
	
	switch (Shooter->STS.StateInt)
	{
		case STATE_DISABLED:
			Shooter->STS.Disabled = 1;
			Shooter->STS.Idle = 0;

			Shooter->HMI.Shoot = 0;
			Shooter->HMI.EnableFan = 0;

			Shooter->CS.Shoot = 0;
			Shooter->CS.EnableFan = 0;
			Shooter->CS.Interlock = 0;

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
				Shooter->HMI.Shoot = 0;
			}	
			else
			{
				if(!Shooter->HMI.EnableFan)
				{
					Shooter->CS.Interlock = 1;
				}
				Shooter->CS.Shoot = 0;
			}

			if((Shooter->HMI.Shoot ^ Shooter->CS.Shoot) == 1 && !Shooter->STS.AlarmActive && !Shooter->STS.Interlocked)
			{
				Shooter->STS.StateInt = STATE_SHOOTING;
			}
			break;
		case STATE_SHOOTING:
			Shooter->STS.Shooting = 1;

			if(!Shooter->CS.Shoot && !Shooter->HMI.Shoot)
			{
				Shooter->STS.StateInt = STATE_IDLE;
			}
			break;
	}

	if(!Shooter->STS.Interlocked && !Shooter->STS.AlarmActive)
	{
		Shooter->IO.Shoot = Shooter->HMI.Shoot != Shooter->CS.Shoot;
	}
	
	Shooter->IO.EnableFan = Shooter->HMI.EnableFan != Shooter->CS.EnableFan;

	Shooter->STS.Interlocked = Shooter->CS.Interlock;
	Shooter->STS.AutoActive = Shooter->CS.AutoMode;

	
	inst->digitalOutput = 0;
	inst->digitalOutput |= (Shooter->IO.Shoot << 3);
	inst->digitalOutput |= Shooter->IO.EnableFan;
	
}
