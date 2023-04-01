/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    deString.cpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "core/deString.hpp"
#include "core/deMemory.hpp"

#include <string.h>

uint64 StrLen(const char *str)
{
	return strlen(str);
}

char *StrDup(const char *str)
{
	uint64 length = StrLen(str);
	char *copy = (char *)DE_Malloc(length + 1, DE_MEMORY_TAG_STRING);

	DE_CopyMemory(copy, str, length + 1);

	return (copy);
}

// Case-sensitive string comparison. True if the same, otherwise false.
bl8 StrEqual(const char *str0, const char *str1)
{
	return (strcmp(str0, str1) == 0);
}
