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

# include <defines.hpp>
# include <stdarg.h>
# include <cstring>
# include <iostream>

// Returns the length of the given string.
DE_API uint64   StrLen(const char* str);

DE_API char*    StrDup(const char* str);

// Case-sensitive string comparison. true if the same, otherwise false.
DE_API bl8 StrCmp(const char *str0, const char *str1);



// Performs string formatting to dest given format string and parameters.
DE_API sint32	StringFormat(char *dest, const char *format, ...);

//
/**
 * Performs variadic string formatting to dest given format string and va_list.
 * @param dest The destination for the formatted string.
 * @param format The string to be formatted.
 * @param va_list The variadic argument list.
 * @returns The size of the data written.
 */
DE_API sint32	StringFormatV(char *dest, const char *format, va_list vaList);

#endif
