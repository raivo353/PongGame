/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Timer
 * File: IECTonTimer.hpp
 *******************************************************************/
#pragma once

#include <standard.h>
#include "ITimer.hpp"

/* The class IECTonTimer wraps a B&R TON function block.*/
class IECTonTimer : public ITimer
{
	private:
		TON_typ fubTON;
	
	public:
		IECTonTimer();
		IECTonTimer(signed long time);
		virtual ~IECTonTimer() {};
		virtual void start(bool start = 1);
		virtual void reset(bool reset = 0);
		virtual bool output(); 
		virtual void setTime(signed long time);
		virtual signed long getElapsedTime();
		
		virtual void cyclic();
};
