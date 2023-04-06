/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	   application.hpp        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef APPLICATION_HPP
# define APPLICATION_HPP

# include <defines.hpp>

# include <string>

struct game;

// Application configuration.
typedef struct	appConfig
{
	sint16		x;	   // Window starting x position, if applicable.
	sint16		y;	   // Window starting y position, if applicable.
	sint16		width;  // Window starting width, if applicable.
	sint16		height; // Window starting height, if applicable.

	std::string	name; // The application name used in windowing, if applicable.
}	appConfig;

DE_API bl8		ApplicationCreate(struct game* gameInst);

DE_API bl8		ApplicationRun();

DE_API void		ApplicationGetFramebufferSize(uint32 *width, uint32 *height);

#endif // APPLICATION_HPP
