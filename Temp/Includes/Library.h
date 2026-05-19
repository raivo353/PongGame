/* Automation Studio generated header file */
/* Do not edit ! */
/* Library  */

#ifndef _LIBRARY_
#define _LIBRARY_
#ifdef __cplusplus
extern "C" 
{
#endif

#include <bur/plctypes.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
/* Datatypes and datatypes of function blocks */
typedef struct UDT_PongGame_ALM
{	plcbit dummy;
} UDT_PongGame_ALM;

typedef struct UDT_PongGame_CS
{	plcbit AutoMode;
	plcbit ErrorAcknowledge;
	plcbit Initialize;
	plcbit Start;
	plcbit StopGame;
} UDT_PongGame_CS;

typedef struct UDT_PongGame_HMI
{	plcbit AutoMode;
	plcbit ErrorAcknowledge;
	plcbit Initialize;
	plcbit Start;
	plcbit StopGame;
} UDT_PongGame_HMI;

typedef struct UDT_PongGame_PAR
{	unsigned short Highscore;
	unsigned short Score;
} UDT_PongGame_PAR;

typedef struct UDT_PongGame_STS
{	plcbit Disabled;
	plcbit AlarmActive;
	plcbit Idle;
	plcbit Initializing;
	plcbit Running;
	unsigned char StateInt;
	plcbit AutoActive;
	plcbit Interlocked;
	unsigned char AlarmActiveColour;
	plcbit GameStopped;
	plcstring StateString[81];
} UDT_PongGame_STS;

typedef struct UDT_PongGame
{	struct UDT_PongGame_ALM ALM;
	struct UDT_PongGame_CS CS;
	struct UDT_PongGame_HMI HMI;
	struct UDT_PongGame_PAR PAR;
	struct UDT_PongGame_STS STS;
} UDT_PongGame;

typedef struct UDT_FieldControl_ALM
{	plcbit dummy;
} UDT_FieldControl_ALM;

typedef struct UDT_FieldControl_CS
{	plcbit MoveToAngle;
	plcbit Initialize;
	plcbit Stop;
	plcbit StopGame;
	plcbit Start;
	plcbit ErrorAcknowledge;
	plcbit Interlock;
	plcbit SetCenterPoint;
} UDT_FieldControl_CS;

typedef struct UDT_FieldControl_HMI
{	plcbit IncreaseAngle;
	plcbit DecreaseAngle;
} UDT_FieldControl_HMI;

typedef struct UDT_FieldControl_PAR
{	float Angle;
} UDT_FieldControl_PAR;

typedef struct UDT_FieldControl_STS
{	plcbit Disabled;
	plcbit Idle;
	plcbit Running;
	plcbit AlarmActive;
	plcbit Initializing;
	plcbit Moving;
	unsigned char StateInt;
	plcbit Interlocked;
	plcbit AutoActive;
	float CurrentAngle;
	plcbit AtTargetPosition;
} UDT_FieldControl_STS;

typedef struct UDT_FieldControl
{	struct UDT_FieldControl_ALM ALM;
	struct UDT_FieldControl_CS CS;
	struct UDT_FieldControl_HMI HMI;
	struct UDT_FieldControl_PAR PAR;
	struct UDT_FieldControl_STS STS;
} UDT_FieldControl;

typedef struct UDT_BallControl_ALM
{	plcbit dummy;
} UDT_BallControl_ALM;

typedef struct UDT_BallControl_CS
{	plcbit AutoMode;
	plcbit Initialize;
	plcbit Shoot;
	plcbit Start;
	plcbit Stop;
	plcbit Interlock;
	plcbit ChangePosition;
	plcbit ErrorAcknowledge;
	plcbit StopGame;
} UDT_BallControl_CS;

typedef struct UDT_BallControl_HMI
{	plcbit dummy;
} UDT_BallControl_HMI;

typedef struct UDT_BallControl_PAR
{	float Position;
	float DesiredPosition;
} UDT_BallControl_PAR;

typedef struct UDT_BallControl_STS
{	plcbit Disabled;
	plcbit Idle;
	plcbit AlarmActive;
	plcbit Initializing;
	plcbit Running;
	plcbit Interlocked;
	unsigned char StateInt;
	plcbit AutoActive;
	float BallVelocity;
	unsigned char ShootState;
	signed long TimeToPaddleMS;
	plcbit ShootCycleCompleted;
	unsigned char PrevShootState;
	plcbit GameOver;
	signed short PaddlePositionMM;
	plcbit FirstRun;
} UDT_BallControl_STS;

typedef struct UDT_BallControl
{	struct UDT_BallControl_ALM ALM;
	struct UDT_BallControl_CS CS;
	struct UDT_BallControl_HMI HMI;
	struct UDT_BallControl_PAR PAR;
	struct UDT_BallControl_STS STS;
} UDT_BallControl;

typedef struct UDT_InclinoSensor_ALM
{	unsigned char dummy;
} UDT_InclinoSensor_ALM;

typedef struct UDT_InclinoSensor_CS
{	plcbit Power;
	plcbit Reset;
	plcbit SetCenterPoint;
} UDT_InclinoSensor_CS;

typedef struct UDT_InclinoSensor_HMI
{	plcbit Power;
	plcbit Reset;
} UDT_InclinoSensor_HMI;

typedef struct UDT_InclinoSensor_PAR
{	unsigned char dummy;
} UDT_InclinoSensor_PAR;

typedef struct UDT_InclinoSensor_STS
{	float CurrentAngle;
	plcbit PowerOn;
	plcbit AlarmActive;
	unsigned char AlarmActiveColour;
} UDT_InclinoSensor_STS;

typedef struct UDT_InclinoSensor_IO
{	unsigned char DataMSB;
	unsigned char DataLSB;
	unsigned char SetCenterPoint;
} UDT_InclinoSensor_IO;

typedef struct UDT_InclinoSensor
{	struct UDT_InclinoSensor_ALM ALM;
	struct UDT_InclinoSensor_CS CS;
	struct UDT_InclinoSensor_HMI HMI;
	struct UDT_InclinoSensor_PAR PAR;
	struct UDT_InclinoSensor_STS STS;
	struct UDT_InclinoSensor_IO IO;
} UDT_InclinoSensor;

typedef struct UDT_FieldMotor_ALM
{	plcbit MotorError;
	unsigned short ErrorID;
	plcstring ErrorText[4][80];
} UDT_FieldMotor_ALM;

typedef struct UDT_FieldMotor_CS
{	plcbit Home;
	plcbit MoveAbsolute;
	plcbit MoveJogNeg;
	plcbit MoveJogPos;
	plcbit Power;
	plcbit Stop;
	plcbit StopGame;
	plcbit ErrorAcknowledge;
	plcbit Start;
	plcbit Interlock;
	plcbit Initialize;
	plcbit SetCenterPoint;
} UDT_FieldMotor_CS;

typedef struct UDT_FieldMotor_HMI
{	plcbit MoveAbsolute;
	plcbit MoveJogNeg;
	plcbit MoveJogPos;
	plcbit Power;
	plcbit IncreaseJogSpeed;
	plcbit DecreaseJogSpeed;
	plcbit ErrorAcknowledge;
} UDT_FieldMotor_HMI;

typedef struct UDT_FieldMotor_IO
{	plcbit EndButton;
	plcbit Power;
	plcbit Home;
	plcbit ErrorAcknowledge;
	plcbit MoveJogNeg;
	plcbit MoveJogPos;
	plcbit Stop;
	plcbit MoveAbsolute;
	float Acceleration;
	float Deceleration;
	float JogVelocity;
	float Velocity;
	float Position;
} UDT_FieldMotor_IO;

typedef struct UDT_FieldMotor_PAR
{	float Acceleration;
	float Deceleration;
	float JogVelocity;
	float Velocity;
	float Position;
} UDT_FieldMotor_PAR;

typedef struct UDT_FieldMotor_STS
{	plcbit Disabled;
	plcbit Idle;
	plcbit Initializing;
	plcbit Running;
	plcbit Moving;
	plcbit StandStill;
	plcbit AtTargetPosition;
	plcbit AutoActive;
	unsigned char StateInt;
	plcbit AlarmActive;
	float ActPosition;
	float ActVelocity;
	plcbit Interlocked;
	plcbit PowerOn;
	plcbit EndButtonHit;
	plcbit TimerStarted;
	plcbit TimerEnded;
	float ReferencePosition;
	unsigned char AlarmActiveColour;
} UDT_FieldMotor_STS;

typedef struct UDT_FieldMotor
{	struct UDT_FieldMotor_ALM ALM;
	struct UDT_FieldMotor_CS CS;
	struct UDT_FieldMotor_HMI HMI;
	struct UDT_FieldMotor_IO IO;
	struct UDT_FieldMotor_PAR PAR;
	struct UDT_FieldMotor_STS STS;
} UDT_FieldMotor;

typedef struct UDT_Shooter_ALM
{	plcbit dummy;
} UDT_Shooter_ALM;

typedef struct UDT_Shooter_CS
{	plcbit Interlock;
	plcbit EnableFan;
	plcbit Shoot;
	plcbit StopGame;
	plcbit Start;
	plcbit AutoMode;
} UDT_Shooter_CS;

typedef struct UDT_Shooter_HMI
{	plcbit EnableFan;
	plcbit Shoot;
	plcbit IncreaseIntensity;
	plcbit DecreaseIntensity;
} UDT_Shooter_HMI;

typedef struct UDT_Shooter_IO
{	plcbit EnableFan;
	plcbit Shoot;
} UDT_Shooter_IO;

typedef struct UDT_Shooter_PAR
{	float Intensity;
} UDT_Shooter_PAR;

typedef struct UDT_Shooter_STS
{	plcbit Disabled;
	plcbit Idle;
	plcbit Interlocked;
	plcbit AlarmActive;
	plcbit AutoActive;
	plcbit Shooting;
	unsigned char StateInt;
	unsigned char AlarmActiveColour;
} UDT_Shooter_STS;

typedef struct UDT_Shooter
{	struct UDT_Shooter_ALM ALM;
	struct UDT_Shooter_CS CS;
	struct UDT_Shooter_HMI HMI;
	struct UDT_Shooter_IO IO;
	struct UDT_Shooter_PAR PAR;
	struct UDT_Shooter_STS STS;
} UDT_Shooter;

typedef struct UDT_DistanceSensor_ALM
{	plcbit OutOfBounds;
} UDT_DistanceSensor_ALM;

typedef struct UDT_DistanceSensor_CS
{	plcbit Power;
} UDT_DistanceSensor_CS;

typedef struct UDT_DistanceSensor_HMI
{	plcbit dummy;
} UDT_DistanceSensor_HMI;

typedef struct UDT_DistanceSensor_IO
{	plcbit OUT1;
	plcbit OUT2;
	unsigned char DataMSB;
	unsigned char DataLSB;
	unsigned char SensorInfo;
} UDT_DistanceSensor_IO;

typedef struct UDT_DistanceSensor_PAR
{	unsigned char dummy;
} UDT_DistanceSensor_PAR;

typedef struct UDT_DistanceSensor_STS
{	signed short Distance;
	signed short Reflectivity;
	plcbit TooClose;
	plcbit TooFar;
	plcbit Valid;
	unsigned short DeviceStatus;
	plcbit PowerOn;
	unsigned char StateInt;
	plcbit AlarmActive;
	unsigned char AlarmActiveColour;
	plcbit BallDetected;
} UDT_DistanceSensor_STS;

typedef struct UDT_DistanceSensor
{	struct UDT_DistanceSensor_ALM ALM;
	struct UDT_DistanceSensor_CS CS;
	struct UDT_DistanceSensor_HMI HMI;
	struct UDT_DistanceSensor_IO IO;
	struct UDT_DistanceSensor_PAR PAR;
	struct UDT_DistanceSensor_STS STS;
} UDT_DistanceSensor;

typedef struct UDT_PaddleMotor_ALM
{	plcbit MotorError;
	unsigned short ErrorID;
	plcstring ErrorText[4][80];
} UDT_PaddleMotor_ALM;

typedef struct UDT_PaddleMotor_CS
{	plcbit Home;
	plcbit MoveAbsolute;
	plcbit MoveJogNeg;
	plcbit MoveJogPos;
	plcbit Power;
	plcbit Stop;
	plcbit ErrorAcknowledge;
	plcbit Start;
	plcbit Interlock;
	plcbit AutoMode;
	plcbit Initialize;
	plcbit StopGame;
} UDT_PaddleMotor_CS;

typedef struct UDT_PaddleMotor_HMI
{	plcbit MoveAbsolute;
	plcbit MoveJogNeg;
	plcbit MoveJogPos;
	plcbit IncreaseJogSpeed;
	plcbit DecreaseJogSpeed;
	plcbit ErrorAcknowledge;
} UDT_PaddleMotor_HMI;

typedef struct UDT_PaddleMotor_IO
{	plcbit EndButton;
	plcbit Power;
	plcbit Home;
	plcbit ErrorAcknowledge;
	plcbit MoveJogNeg;
	plcbit MoveJogPos;
	plcbit Stop;
	plcbit MoveAbsolute;
	float Acceleration;
	float Deceleration;
	float JogVelocity;
	float Velocity;
	float Position;
} UDT_PaddleMotor_IO;

typedef struct UDT_PaddleMotor_PAR
{	float Acceleration;
	float Deceleration;
	float JogVelocity;
	float Velocity;
	float Position;
} UDT_PaddleMotor_PAR;

typedef struct UDT_PaddleMotor_STS
{	plcbit Disabled;
	plcbit Initializing;
	plcbit Idle;
	plcbit Running;
	plcbit AlarmActive;
	plcbit Moving;
	plcbit StandStill;
	plcbit AtTargetPosition;
	float ActPosition;
	float ActVelocity;
	plcbit Interlocked;
	plcbit PowerOn;
	plcbit AutoActive;
	unsigned char StateInt;
	plcbit EndButtonHit;
	plcbit TimerStarted;
	plcbit TimerEnded;
	float ReferencePosition;
	plcbit ReferenceSet;
	unsigned char AlarmActiveColour;
} UDT_PaddleMotor_STS;

typedef struct UDT_PaddleMotor
{	struct UDT_PaddleMotor_ALM ALM;
	struct UDT_PaddleMotor_CS CS;
	struct UDT_PaddleMotor_HMI HMI;
	struct UDT_PaddleMotor_IO IO;
	struct UDT_PaddleMotor_PAR PAR;
	struct UDT_PaddleMotor_STS STS;
} UDT_PaddleMotor;

typedef struct FB_PaddleMotor
{
	/* VAR_INPUT (analog) */
	unsigned char digitalInput;
	/* VAR_IN_OUT (analog and digital) */
	struct UDT_PaddleMotor* PaddleMotor;
} FB_PaddleMotor_typ;

typedef struct FB_DistanceSensor
{
	/* VAR_IN_OUT (analog and digital) */
	struct UDT_DistanceSensor* DistanceSensorLeft;
	struct UDT_DistanceSensor* DistanceSensorMiddle;
	struct UDT_DistanceSensor* DistanceSensorRight;
} FB_DistanceSensor_typ;

typedef struct FB_Shooter
{
	/* VAR_OUTPUT (analog) */
	unsigned char digitalOutput;
	/* VAR_IN_OUT (analog and digital) */
	struct UDT_Shooter* Shooter;
} FB_Shooter_typ;

typedef struct FB_FieldMotor
{
	/* VAR_INPUT (analog) */
	unsigned char digitalInput;
	/* VAR_IN_OUT (analog and digital) */
	struct UDT_FieldMotor* FieldMotor;
} FB_FieldMotor_typ;

typedef struct FB_InclinoSensor
{
	/* VAR_IN_OUT (analog and digital) */
	struct UDT_InclinoSensor* InclinoSensor;
} FB_InclinoSensor_typ;

typedef struct FB_BallControl
{
	/* VAR_IN_OUT (analog and digital) */
	struct UDT_BallControl* BallControl;
	struct UDT_PaddleMotor* PaddleMotor;
	struct UDT_Shooter* Shooter;
	struct UDT_DistanceSensor* DistanceSensorLeft;
	struct UDT_DistanceSensor* DistanceSensorMiddle;
	struct UDT_DistanceSensor* DistanceSensorRight;
} FB_BallControl_typ;

typedef struct FB_FieldControl
{
	/* VAR_IN_OUT (analog and digital) */
	struct UDT_FieldMotor* FieldMotor;
	struct UDT_FieldControl* FieldControl;
	struct UDT_InclinoSensor* InclinoSensor;
} FB_FieldControl_typ;

typedef struct FB_PongGame
{
	/* VAR_IN_OUT (analog and digital) */
	struct UDT_PongGame* PongGame;
	struct UDT_BallControl* BallControl;
	struct UDT_FieldControl* FieldControl;
} FB_PongGame_typ;



/* Prototyping of functions and function blocks */
_BUR_PUBLIC void FB_PaddleMotor(struct FB_PaddleMotor* inst);
_BUR_PUBLIC void FB_DistanceSensor(struct FB_DistanceSensor* inst);
_BUR_PUBLIC void FB_Shooter(struct FB_Shooter* inst);
_BUR_PUBLIC void FB_FieldMotor(struct FB_FieldMotor* inst);
_BUR_PUBLIC void FB_InclinoSensor(struct FB_InclinoSensor* inst);
_BUR_PUBLIC void FB_BallControl(struct FB_BallControl* inst);
_BUR_PUBLIC void FB_FieldControl(struct FB_FieldControl* inst);
_BUR_PUBLIC void FB_PongGame(struct FB_PongGame* inst);


#ifdef __cplusplus
};
#endif
#endif /* _LIBRARY_ */

