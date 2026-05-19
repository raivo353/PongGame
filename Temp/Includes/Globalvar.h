/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1779179374_1_
#define _BUR_1779179374_1_

#include <bur/plctypes.h>

/* Constants */
#ifdef _REPLACE_CONST
#else
#endif


/* Variables */
_GLOBAL_RETAIN unsigned short g_Highscore;
_GLOBAL unsigned char digitalOutput;
_GLOBAL unsigned char digitalInput;
_GLOBAL struct UDT_Shooter g_Shooter;
_GLOBAL struct UDT_PongGame g_PongGame;
_GLOBAL struct UDT_PaddleMotor g_PaddleMotor;
_GLOBAL struct UDT_InclinoSensor g_InclinoSensor;
_GLOBAL struct UDT_FieldMotor g_FieldMotor;
_GLOBAL struct UDT_DistanceSensor g_DistanceSensorRight;
_GLOBAL struct UDT_FieldControl g_FieldControl;
_GLOBAL struct UDT_DistanceSensor g_DistanceSensorMiddle;
_GLOBAL struct UDT_DistanceSensor g_DistanceSensorLeft;
_GLOBAL struct UDT_BallControl g_BallControl;
_GLOBAL struct ACP10AXIS_typ gAxis02;
_GLOBAL struct ACP10AXIS_typ gAxis01;





__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/Global.var\\\" scope \\\"global\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1779179374_1_ */

