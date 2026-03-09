/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Timer
 * File: ITimer.hpp
 *******************************************************************/
#pragma once

/* Interface timer class */
class ITimer
{
	public:
		ITimer() {};
		ITimer(signed long time);
		virtual ~ITimer() {};
		virtual void start(bool start = 1) = 0;
		virtual void reset(bool reset = 1) = 0;
		virtual bool output() = 0;
		virtual void setTime(signed long time) = 0;
		virtual signed long getElapsedTime() = 0;
		virtual void cyclic() = 0;
};

/* Superclass for concrete timer factory classes */
class TimerFactory
{
	public:
		TimerFactory() {};
		virtual ~TimerFactory(){};   
		virtual ITimer* createTON(signed long time = 0) const = 0;
		virtual ITimer* createTOF(signed long time = 0) const = 0;
		virtual ITimer* createTP(signed long time = 0)  const = 0;			
		static TimerFactory* getInstance();
};
