#include <bur/plctypes.h>

#define STATE_DISABLED 0
#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	g_PaddleMotor.STS.StateInt = STATE_DISABLED;
	g_FieldMotor.STS.StateInt = STATE_DISABLED;
	g_FieldControl.STS.StateInt = STATE_DISABLED;
	g_Shooter.STS.StateInt = STATE_DISABLED;
	
	PaddleMotor.PaddleMotor = &g_PaddleMotor;
	
	Shooter.Shooter = &g_Shooter;
	
	DistanceSensors.DistanceSensorLeft = &g_DistanceSensorLeft;
	DistanceSensors.DistanceSensorMiddle = &g_DistanceSensorMiddle;
	DistanceSensors.DistanceSensorRight = &g_DistanceSensorRight;
	
	FieldMotor.FieldMotor = &g_FieldMotor;
	FieldMotor.digitalInput = digitalInput;
	
	InclinoSensor.InclinoSensor = &g_InclinoSensor;
	
	FieldControl.FieldControl = &g_FieldControl;
	FieldControl.FieldMotor = &g_FieldMotor;
	FieldControl.InclinoSensor = &g_InclinoSensor;
	
	BallControl.BallControl = &g_BallControl;
	BallControl.DistanceSensorLeft = &g_DistanceSensorLeft;
	BallControl.DistanceSensorMiddle = &g_DistanceSensorMiddle;
	BallControl.DistanceSensorRight = &g_DistanceSensorRight;
	BallControl.PaddleMotor = &g_PaddleMotor;
	BallControl.Shooter = &g_Shooter;
	
	PongGame.PongGame = &g_PongGame;
	PongGame.BallControl = &g_BallControl;
	PongGame.FieldControl = &g_FieldControl;
}
