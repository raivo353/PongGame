
#include <bur/plctypes.h>
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

// amount of memory to be allocated for heap storage must be specified for every ANSI C++ program with the bur_heap_size variable
unsigned long bur_heap_size = 0xFFFF; 

void _CYCLIC ProgramCyclic(void)
{	
	//creating FieldMotor function block
	FieldMotor.FieldMotor = &g_FieldMotor;
	FieldMotor.digitalInput = digitalInput;
	FB_FieldMotor(&FieldMotor);
	
	//creating PaddleMotor function block
	PaddleMotor.PaddleMotor = &g_PaddleMotor;
	PaddleMotor.digitalInput = digitalInput;
	FB_PaddleMotor(&PaddleMotor);
	
	//creating Shooter function block
	Shooter.Shooter = &g_Shooter;
	digitalOutput = Shooter.digitalOutput;
	FB_Shooter(&Shooter);
	
	//creating DistanceSensors function block
	DistanceSensors.DistanceSensorLeft = &g_DistanceSensorLeft;
	DistanceSensors.DistanceSensorMiddle = &g_DistanceSensorMiddle;
	DistanceSensors.DistanceSensorRight = &g_DistanceSensorRight;
	FB_DistanceSensor(&DistanceSensors);
	
	//creating InclinoSensor function block
	InclinoSensor.InclinoSensor = &g_InclinoSensor;
	FB_InclinoSensor(&InclinoSensor);
}