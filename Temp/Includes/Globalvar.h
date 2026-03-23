/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1774280074_2_
#define _BUR_1774280074_2_

#include <bur/plctypes.h>

/* Constants */
#ifdef _REPLACE_CONST
#else
#endif


/* Variables */
_GLOBAL struct ACP10VAXIS_typ gVAxis01;
_GLOBAL struct ACP10AXIS_typ gAxis02;
_GLOBAL struct ACP10AXIS_typ gAxis01;
_GLOBAL signed short gStpAxis_MotorStep0;
_GLOBAL struct SdcDiDoIf_typ gStpAxis_DiDoIf;
_GLOBAL struct SdcEncIf16_typ gStpAxis_EncIf1;
_GLOBAL struct SdcDrvIf16_typ gStpAxis_DrvIf;
_GLOBAL struct SdcHwCfg_typ gStpAxis_HW;
_GLOBAL struct ACP10AXIS_typ gStpAxis;
_GLOBAL plcbit isTrapperButtonNotPressed;
_GLOBAL plcbit isVeldButtonNotPressed;
_GLOBAL unsigned char digitalInput;
_GLOBAL plcbit isTrapperButtonPressed;
_GLOBAL plcbit isVeldButtonPressed;





__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/Global.var\\\" scope \\\"global\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1774280074_2_ */

