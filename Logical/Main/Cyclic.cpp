
#include <bur/plctypes.h>
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// amount of memory to be allocated for heap storage must be specified for every ANSI C++ program with the bur_heap_size variable
unsigned long bur_heap_size = 0xFFFF; 

void _CYCLIC ProgramCyclic(void)
{	
	PaddleMotor.digitalInput = digitalInput;
	FieldMotor.digitalInput = digitalInput;
	
	FB_PaddleMotor(&PaddleMotor);
	FB_Shooter(&Shooter);
	FB_DistanceSensor(&DistanceSensors);
	FB_FieldMotor(&FieldMotor);
	FB_InclinoSensor(&InclinoSensor);
	FB_FieldControl(&FieldControl);
	FB_BallControl(&BallControl);
	FB_PongGame(&PongGame);
	
	digitalOutput = Shooter.digitalOutput;
}