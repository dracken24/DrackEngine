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

#include <core/deString.hpp>
#include <core/deMemory.hpp>

#include <string.h>

uint64 StrLen(const char* str)
{
	return (strlen(str));
}

char* StrDup(const char* str)
{
	uint64 length = StrLen(str);
	char *copy = (char *)Mallocate(length + 1, DE_MEMORY_TAG_STRING);

	CopyMemory(copy, str, length + 1);

	return (copy);
}

// Case-sensitive string comparison. true if the same, otherwise false.
bl8 StrCmp(const char* str0, const char* str1)
{
	return (strcmp(str0, str1) == 0);
}

sint32	StringFormat(char *dest, const char *format, ...)
{
	if (dest)
	{
		__builtin_va_list arg_ptr;
		va_start(arg_ptr, format);
		sint32 written = StringFormatV(dest, format, arg_ptr);
		va_end(arg_ptr);
		
		return written;
	}

	return -1;
}

sint32 	StringFormatV(char *dest, const char *format, va_list vaList)
{
	if (dest)
	{
		// Big, but can fit on the stack.
		char buffer[32000];
		sint32 written = vsnprintf(buffer, 32000, format, vaList);
		buffer[written] = 0;
		CopyMemory(dest, buffer, written + 1);

		return written;
	}

	return -1;
}
