/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 30-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     clock.hpp            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef CLOCK_HPP
# define CLOCK_HPP

# include "defines.hpp"
# include "platform/Platform.hpp"

class Clock
{
	public:
		// Clock structure
		typedef struct myClock
		{
			dbl64		startTime;		// Time when the clock started
			dbl64		elapsedTime;	// Time elapsed since the clock started
		}	myClock;

	//****************************************************************************//
	//**       						Constructors                            	**//
	//****************************************************************************//
		Clock(void);
		~Clock(void);
		Clock(const Clock &copy);
		
		Clock	&operator=(const Clock &copy);

	//****************************************************************************//
	//**       						PUBLIC METHODS                          	**//
	//****************************************************************************//

		// Start or restart the clock
		void	ClockStart(void);

		// Update the clock
		void	ClockUpdate(void);

		// Stop and don't restart the clock
		void	ClockStop(void);

		myClock		_clock;
		Platform	_platform;
};

#endif
