/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Timer
 * File: IECTonTimer.cpp
 *******************************************************************/

#include <bur/plctypes.h>
#include <string.h>
#include "IECTonTimer.hpp"

IECTonTimer::IECTonTimer()
{
	memset(&fubTON,0,sizeof(fubTON));
}

IECTonTimer::IECTonTimer(signed long time)
{
	memset(&fubTON,0,sizeof(fubTON));
	this->setTime(time);
}

void IECTonTimer::start(bool start)
{
	this->fubTON.IN = start;
}
	
void IECTonTimer::reset(bool reset)
{
	this->fubTON.IN = !reset;	
}

void IECTonTimer::setTime(signed long time)
{
	this->fubTON.PT = time;
}

bool IECTonTimer::output()
{
	return this->fubTON.Q;
}

signed long IECTonTimer::getElapsedTime()
{
	return this->fubTON.ET;
}

/* This method has to be called cyclically in programms. */
void IECTonTimer::cyclic()
{
	TON(&fubTON);
}
