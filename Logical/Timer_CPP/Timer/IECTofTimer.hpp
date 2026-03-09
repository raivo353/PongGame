/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Timer
 * File: IECTonTimer.hpp
 *******************************************************************/
#pragma once

#include <standard.h>
#include "ITimer.hpp"

/* The class IECTonTimer wraps a B&R TOF function block.*/
class IECTofTimer : public ITimer
{
	private:
		TOF_typ fubTOF;
	
	public:
		IECTofTimer();
		IECTofTimer(signed long time);
		virtual ~IECTofTimer() {};
		virtual void start(bool start = 1);
		virtual void reset(bool reset = 1);
		virtual bool output(); 
		virtual void setTime(signed long time);
		virtual signed long getElapsedTime();
		
		virtual void cyclic();
};
