/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Timer
 * File: IECTonTimer.hpp
 *******************************************************************/
#pragma once

#include <standard.h>
#include "ITimer.hpp"

/* The class IECTonTimer wraps a B&R TP (pulse generator) function block.
*/
class IECTpTimer : public ITimer
{
	private:
		TP_typ fubTP;
	
	public:
		IECTpTimer();
		IECTpTimer(signed long time);
		virtual ~IECTpTimer() {};
		virtual void start(bool start = 1);
		virtual void reset(bool reset = 1);
		virtual bool output(); 
		virtual void setTime(signed long time);
		virtual signed long getElapsedTime();
		
		virtual void cyclic();
};
