
#include <bur/plctypes.h>
#include "variables.h"
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// amount of memory to be allocated for heap storage must be specified for every ANSI C++ program with the bur_heap_size variable
unsigned long bur_heap_size = 0xFFFF; 

void _CYCLIC ProgramCyclic(void)
{
	INT distLeft = DistanceSensor(DistanceSensorInputsVar.LeftMSB, DistanceSensorInputsVar.LeftLSB);
	INT distMiddle = DistanceSensor(DistanceSensorInputsVar.MiddleMSB, DistanceSensorInputsVar.MiddleLSB);
	INT distRight = DistanceSensor(DistanceSensorInputsVar.RightMSB, DistanceSensorInputsVar.RightLSB);
	

	DistanceSensorLeft = (distLeft >= 30 && distLeft <= 300) ? distLeft : DistanceSensorLeft;
	DistanceSensorMiddle = (distMiddle >= 30 && distMiddle <= 300) ? distMiddle : DistanceSensorMiddle;
	DistanceSensorRight = (distRight >= 30 && distRight <= 300) ? distRight : DistanceSensorRight;
}
