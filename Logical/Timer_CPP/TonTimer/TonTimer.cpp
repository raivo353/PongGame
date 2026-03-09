/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Program: TonTimer
 * File: TonTimer.cpp
 ********************************************************************
 * Implementation of program TonTimer
 ********************************************************************/

#include <bur/plctypes.h>
#include <string.h>

#include "..\Timer\Timer.hpp"

/* Heap size for this program */
unsigned long bur_heap_size = 0xFFFF; 

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#define TRAPPER_BITMASK 0x02
#define KANTELMECHANISME_BITMASK 0x04

void _INIT TonTimerINIT(void)
{
}

void _CYCLIC TonTimerCYCLIC(void)
{
	/* set and reset timer */

	isTrapperButtonPressed = ((digitalInput & TRAPPER_BITMASK) == 0);
	isVeldButtonPressed = ((digitalInput & KANTELMECHANISME_BITMASK) == 0);
	isTrapperButtonNotPressed = !isTrapperButtonPressed;
	isVeldButtonNotPressed = !isVeldButtonPressed;
	/* read output values to process variables */
	/* Cyclic call. This is needed because the TON Function block is used in the class IECTonTimer */
}

void _EXIT TonTimerEXIT(void)
{

}
