
#include <bur/plctypes.h>
#include "variables.h"
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#define SENSOR_OVERLOAD 32760
#define SENSOR_UNDERLOAD -32760
// amount of memory to be allocated for heap storage must be specified for every ANSI C++ program with the bur_heap_size variable
unsigned long bur_heap_size = 0xFFFF; 

void _CYCLIC ProgramCyclic(void)
{
	INT distLeft = SensorDataConverter(DistanceSensorInputsVar.LeftMSB, DistanceSensorInputsVar.LeftLSB);
	INT distMiddle = SensorDataConverter(DistanceSensorInputsVar.MiddleMSB, DistanceSensorInputsVar.MiddleLSB);
	INT distRight = SensorDataConverter(DistanceSensorInputsVar.RightMSB, DistanceSensorInputsVar.RightLSB);
	INT InclineSensorData = SensorDataConverter(InclineSensorInputsVar.MSB, InclineSensorInputsVar.LSB);
	

	DistanceSensorLeft = (distLeft >= 30 && distLeft <= 300) ? distLeft : 0;
	DistanceSensorMiddle = (distMiddle >= 30 && distMiddle <= 300) ? distMiddle : 0;
	DistanceSensorRight = (distRight >= 30 && distRight <= 300) ? distRight : 0;
	
	
	FieldAngle = InclineSensorDataToAngle(InclineSensorData);
}