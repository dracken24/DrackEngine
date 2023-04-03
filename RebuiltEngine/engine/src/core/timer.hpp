/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 30-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     timer.hpp            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef TIMER_HPP
# define TIMER_HPP

# include "defines.hpp"
# include "platform/platform.hpp"

class Timer
{
	public:
		// timer structure
		typedef struct mytimer
		{
			dbl64		startTime;		// Time when the timer started
			dbl64		elapsedTime;	// Time elapsed since the timer started
		}	mytimer;

	//****************************************************************************//
	//**       						Constructors                            	**//
	//****************************************************************************//
		Timer(void);
		~Timer(void);
		Timer(const Timer &copy);
		
		Timer	&operator=(const Timer &copy);

	//****************************************************************************//
	//**       						PUBLIC METHODS                          	**//
	//****************************************************************************//

		// Start or restart the timer
		void	TimerStart(void);

		// Update the timer
		void	TimerUpdate(void);

		// Stop and don't restart the timer
		void	TimerStop(void);

		mytimer		_timer;
		// platform	_platform;
};

#endif
