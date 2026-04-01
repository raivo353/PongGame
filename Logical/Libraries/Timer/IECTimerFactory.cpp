/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Timer
 * File: IECTimerFactory.cpp
 *******************************************************************/

#include "ITimer.hpp"
#include "IECTimerFactory.hpp"

/* Create a concrete IEC factory */
TimerFactory* TimerFactory::getInstance()
{
	static IECTimerFactory theIECTimerFactory;
	return &theIECTimerFactory;
}
