/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Timer
 * File: IECTpTimer.cpp
 *******************************************************************/

#include <string.h>
#include "IECTpTimer.hpp"

IECTpTimer::IECTpTimer()
{
	memset(&fubTP,0,sizeof(fubTP));
}

IECTpTimer::IECTpTimer(signed long time)
{
	memset(&fubTP,0,sizeof(fubTP));
	this->setTime(time);
}

void IECTpTimer::start(bool start)
{
	this->fubTP.IN = start;
}
	
void IECTpTimer::reset(bool reset)
{
	this->fubTP.IN = !reset;	
}

void IECTpTimer::setTime(signed long time)
{
	this->fubTP.PT = time;
}

bool IECTpTimer::output()
{
	return this->fubTP.Q;
}

signed long IECTpTimer::getElapsedTime()
{
	return this->fubTP.ET;
}

/* This method has to be called cyclically in programms.*/
void IECTpTimer::cyclic()
{
	TP(&fubTP);
}
