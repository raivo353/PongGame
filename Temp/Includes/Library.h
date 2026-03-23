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



/* Prototyping of functions and function blocks */
_BUR_PUBLIC unsigned short ActPositionToMM(float ActPosition);
_BUR_PUBLIC unsigned char SetOutputs(unsigned char digitalOutputs, plcbit ventilator, plcbit solenoid);
_BUR_PUBLIC signed short DistanceSensor(unsigned char DistanceMSB, unsigned char DistanceLSB);


#ifdef __cplusplus
};
#endif
#endif /* _LIBRARY_ */

