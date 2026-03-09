/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Timer
 * File: IECTofTimer.cpp
 *******************************************************************/

#include <bur/plctypes.h>
#include <string.h>
#include "IECTofTimer.hpp"

IECTofTimer::IECTofTimer()
{
	memset(&fubTOF,0,sizeof(fubTOF));
}

IECTofTimer::IECTofTimer(signed long time)
{
	memset(&fubTOF,0,sizeof(fubTOF));
	this->setTime(time);
}

void IECTofTimer::start(bool start)
{
	this->fubTOF.IN = start;
}
	
void IECTofTimer::reset(bool reset)
{
	this->fubTOF.IN = !reset;	
}

void IECTofTimer::setTime(signed long time)
{
	this->fubTOF.PT = time;
}

bool IECTofTimer::output()
{
	return this->fubTOF.Q;
}

signed long IECTofTimer::getElapsedTime()
{
	return this->fubTOF.ET;
}

/* This method has to be called cyclically in programms. */
void IECTofTimer::cyclic()
{
	TOF(&fubTOF);
}
