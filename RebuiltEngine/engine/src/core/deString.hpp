/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    deString.hpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef DESTRING_HPP
# define DESTRING_HPP

#include "defines.hpp"

// Returns the length of the given string.
DE_API uint64	StrLen(const char *str);

DE_API char		*StrDup(const char *str);

// Case-sensitive string comparison. True if the same, otherwise false.
DE_API bl8		StrEqual(const char *str0, const char *str1);

#endif
