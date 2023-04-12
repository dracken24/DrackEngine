/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 11-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	      main.cpp            *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "testManager.hpp"
#include "memory/linearAllocatorTest.hpp"

#include <core/logger.hpp>

int main()
{
	// Always initalize the test manager first.
	TestManagerInit();

	// TODO: add test registrations here.
	LinearAllocatorRegisterTests();

	DE_DEBUG("Starting tests...");

	// Execute tests
	TestManagerRunTests();

	return 0;
}
