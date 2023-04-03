/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 30-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     timer.cpp            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "core/timer.hpp"
#include "platform/platform.hpp"

//****************************************************************************//
//**       						Constructors                            	**//
//****************************************************************************//

Timer::Timer(void)
{
	
}

Timer::~Timer(void)
{
	
}

Timer::Timer(const Timer &copy)
{
	*this = copy;
}

Timer	&Timer::operator=(const Timer &copy)
{
	if (this != &copy)
	{
		// Copy the timer
	}
	return (*this);
}

//****************************************************************************//
//**       						PUBLIC METHODS                          	**//
//****************************************************************************//

// Start or restart the timer
void	Timer::TimerStart(void)
{
	_timer.startTime = PlatformGetAbsoluteTime();
	_timer.elapsedTime = 0.0;
}

// Update the timer
void	Timer::TimerUpdate(void)
{
	if (_timer.startTime != 0)
	{
		_timer.elapsedTime = PlatformGetAbsoluteTime() - _timer.startTime;
	}
}

// Stop and don't restart the timer
void	Timer::TimerStop(void)
{
	_timer.startTime = 0;
}
