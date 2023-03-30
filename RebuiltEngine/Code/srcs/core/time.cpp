/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 30-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     clock.cpp            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "../../includes/core/time.hpp"
#include "../../includes/platform/Platform.hpp"

//****************************************************************************//
//**       						Constructors                            	**//
//****************************************************************************//

Clock::Clock(void)
{
	
}

Clock::~Clock(void)
{
	
}

Clock::Clock(const Clock &copy)
{
	*this = copy;
}

Clock	&Clock::operator=(const Clock &copy)
{
	if (this != &copy)
	{
		// Copy the clock
	}
	return (*this);
}

//****************************************************************************//
//**       						PUBLIC METHODS                          	**//
//****************************************************************************//

// Start or restart the clock
void	Clock::ClockStart(void)
{
	_clock.startTime = _platform.PlatGetAbsoluteTime();
	_clock.elapsedTime = 0.0;
}

// Update the clock
void	Clock::ClockUpdate(void)
{
	if (_clock.startTime != 0)
	{
		_clock.elapsedTime = _platform.PlatGetAbsoluteTime() - _clock.startTime;
	}
}

// Stop and don't restart the clock
void	Clock::ClockStop(void)
{
	_clock.startTime = 0;
}
