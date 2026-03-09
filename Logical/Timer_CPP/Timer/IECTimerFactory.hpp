/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Timer
 * File: IECTimerFactory.hpp
 *******************************************************************/
#pragma once

#include "IECTonTimer.hpp"
#include "IECTofTimer.hpp"
#include "IECTpTimer.hpp"

/* Concrete factory for IEC timer */
class IECTimerFactory : public TimerFactory
{
	public:
		IECTimerFactory() {};
	
		virtual ~IECTimerFactory(){};
	   
		virtual ITimer* createTON(signed long time = 0) const
		{
			return new IECTonTimer(time);
		}
	
		virtual ITimer* createTOF(signed long time = 0) const
		{
			return new IECTofTimer(time);
		}
	
		virtual ITimer* createTP(signed long time = 0)  const
		{
			return new IECTpTimer(time);
		}	
				
		static TimerFactory* getInstance();
};
