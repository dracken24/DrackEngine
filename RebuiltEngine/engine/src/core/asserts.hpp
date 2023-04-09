/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 25-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    asserts.cpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

/*
An assertion is a statement that checks for a specific condition at a given
point in code and reports an error if that condition is not true.

If an assertion fails, the program usually stops and displays a detailed error
message that indicates where the assertion failed.

assertion functions are used to verify the validity of user input, the state of
game objects, function return values, and more. For example, an assertion function
could be used to check if a texture was loaded correctly or if the function's
input parameters are valid. If the assertion fails, it means there is an error
somewhere in the code and action needs to be taken to correct the error.
*/

#ifndef ASSERTS_HPP
#define ASSERTS_HPP

#include <string>

#include "defines.hpp"

// Disable all asserts by commenting out this line
#define DE_ASSERTS_ENABLED

#ifdef DE_ASSERTS_ENABLED
#if _MSC_VER // Windows
#include <intrin.h>
#define DE_DEB_BREAK() __debugbreak()
#else // Linux
#define DE_DEB_BREAK() __builtin_trap()
#endif
#endif

// Asserts that the given expression is true. If it is not, the program will
// stop and display an error message.
DE_API void ReportAssertionFailure(std::string const expression, std::string const message,
				std::string const file, sint32 line);

// Asserts that the given expression is true. If it is not,
// the program will stop and display an error message.
#define DE_ASSERT(expression)                                            \
	{                                                                    \
		if (expression)                                                  \
		{                                                                \
		}                                                                \
		else                                                             \
		{                                                                \
			ReportAssertionFailure(#expression, "", __FILE__, __LINE__); \
			DE_DEB_BREAK();                                              \
		}                                                                \
	}

#define DE_ASSERT_MSG(expression, message)                                    \
	{                                                                         \
		if (expression)                                                       \
		{                                                                     \
		}                                                                     \
		else                                                                  \
		{                                                                     \
			ReportAssertionFailure(#expression, message, __FILE__, __LINE__); \
			DE_DEB_BREAK();                                                   \
		}                                                                     \
	}

#ifdef _DEBUG
#define DE_ASSERT_DEBUG(expression)                                      \
	{                                                                    \
		if (expression)                                                  \
		{                                                                \
		}                                                                \
		else                                                             \
		{                                                                \
			ReportAssertionFailure(#expression, "", __FILE__, __LINE__); \
			DebugBreak();                                                \
		}                                                                \
	}
#else
#define DE_ASSERT_DEBUG(expr) // Does nothing at all
#endif

#else
#define DE_ASSERT(expression)              // Does nothing at all
#define DE_ASSERT_MSG(expression, message) // Does nothing at all
#define DE_ASSERT_DEBUG(expression)        // Does nothing at all

#endif
