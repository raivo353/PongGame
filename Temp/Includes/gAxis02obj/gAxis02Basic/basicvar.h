/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1774280074_9_
#define _BUR_1774280074_9_

#include <bur/plctypes.h>

/* Constants */
#ifdef _REPLACE_CONST
#else
#endif


/* Variables */
_BUR_LOCAL unsigned short oldErrorID;
_BUR_LOCAL plcstring firstErrorMessage[81];
_BUR_LOCAL plcbit decrementKantelSpeed;
_BUR_LOCAL plcbit incrementKantelSpeed;
_BUR_LOCAL struct MC_Halt MC_Halt_0;
_BUR_LOCAL struct MC_BR_ReadDriveStatus MC_BR_ReadDriveStatus_0;
_BUR_LOCAL struct MC_ReadActualVelocity MC_ReadActualVelocity_0;
_BUR_LOCAL struct MC_ReadActualPosition MC_ReadActualPosition_0;
_BUR_LOCAL struct MC_ReadStatus MC_ReadStatus_0;
_BUR_LOCAL struct MC_Reset MC_Reset_0;
_BUR_LOCAL struct MC_ReadAxisError MC_ReadAxisError_0;
_BUR_LOCAL struct MC_MoveAdditive MC_MoveAdditive_0;
_BUR_LOCAL struct MC_MoveAbsolute MC_MoveAbsolute_0;
_BUR_LOCAL struct MC_MoveVelocity MC_MoveVelocity_0;
_BUR_LOCAL struct MC_Stop MC_Stop_0;
_BUR_LOCAL struct MC_Home MC_Home_0;
_BUR_LOCAL struct MC_Power MC_Power_0;
_BUR_LOCAL unsigned char AxisStep;
_BUR_LOCAL unsigned long Axis1Obj;
_BUR_LOCAL struct basic_typ BasicControl;
_BUR_LOCAL struct color_datapoints_typ ColorDatapoints;





__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/gAxis02obj/gAxis02Basic/basic.var\\\" scope \\\"local\\\"\\n\"");
__asm__(".ascii \"iecfile \\\"Logical/Libraries/Acp10_MC/acp10_mc.fun\\\" scope \\\"global\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1774280074_9_ */

