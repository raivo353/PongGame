/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1774280074_8_
#define _BUR_1774280074_8_

#include <bur/plctypes.h>

/* Datatypes and datatypes of function blocks */
typedef struct color_datapoints_typ
{	signed short color_power;
	signed short color_homing;
} color_datapoints_typ;

typedef struct basic_command_typ
{	plcbit Power;
	plcbit Home;
	plcbit MoveAbsolute;
	plcbit MoveAdditive;
	plcbit MoveVelocity;
	plcbit Halt;
	plcbit Stop;
	plcbit MoveJogPos;
	plcbit MoveJogNeg;
	plcbit ErrorAcknowledge;
} basic_command_typ;

typedef struct basic_parameter_typ
{	float Position;
	float Distance;
	float Velocity;
	unsigned char Direction;
	float Acceleration;
	float Deceleration;
	float HomePosition;
	unsigned char HomeMode;
	float JogVelocity;
} basic_parameter_typ;

typedef struct basic_status_typ
{	unsigned short ErrorID;
	plcstring ErrorText[4][80];
	float ActPosition;
	float ActVelocity;
	struct MC_DRIVESTATUS_TYP DriveStatus;
} basic_status_typ;

typedef struct basic_axisState_typ
{	plcbit Disabled;
	plcbit StandStill;
	plcbit Homing;
	plcbit Stopping;
	plcbit DiscreteMotion;
	plcbit ContinuousMotion;
	plcbit SynchronizedMotion;
	plcbit ErrorStop;
} basic_axisState_typ;

typedef struct basic_typ
{	struct basic_command_typ Command;
	struct basic_parameter_typ Parameter;
	struct basic_status_typ Status;
	struct basic_axisState_typ AxisState;
} basic_typ;






__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/gAxis02obj/gAxis02Basic/basic.typ\\\" scope \\\"local\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1774280074_8_ */

