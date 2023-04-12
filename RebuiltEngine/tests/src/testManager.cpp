/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 11-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  TestManager.cpp         *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "testManager.hpp"

#include <containers/arrayDinamic.hpp>
#include <core/logger.hpp>
#include <core/deString.hpp>
#include <core/timer.hpp>

typedef struct	testEntry
{
	PFN_test	func;
	char		*desc;
}	testEntry;

static testEntry	*tests;

void	TestManagerInit(void)
{
	tests = (testEntry *)DE_ArrayCreate(DE_ARRAY_DIN_DEFAULT_CAPACITY, sizeof(testEntry));
}

void	TestManagerRegisterTest(uint8 (*PFN_test)(), char *desc)
{
	testEntry e;
	e.func = PFN_test;
	e.desc = desc;
	DE_ArrayPush2(tests, e);
}

void	TestManagerRunTests(void)
{
	uint32 passed = 0;
	uint32 failed = 0;
	uint32 skipped = 0;

	uint32 count = DE_ArrayLength(tests);

	Timer totalTime;
	totalTime.TimerStart();

	for (uint32 i = 0; i < count; ++i)
	{
		Timer testTime;
		testTime.TimerStart();
		uint8 result = tests[i].func();
		testTime.TimerUpdate();

		if (result == true)
		{
			++passed;
		}
		else if (result == BYPASS)
		{
			DE_WARNING("[SKIPPED]: %s", tests[i].desc);
			++skipped;
		}
		else
		{
			DE_ERROR("[FAILED]: %s", tests[i].desc);
			++failed;
		}
		char status[20];
		StringFormat(status, failed ? "*** %d FAILED ***" : "SUCCESS", failed);
		totalTime.TimerUpdate();
		DE_INFO("Executed %d of %d (skipped %d) %s (%.6f sec / %.6f sec total", i + 1, count, skipped, status, testTime._timer.elapsedTime, totalTime._timer.elapsedTime);
	}

	totalTime.TimerStop();

	DE_INFO("Results: %d passed, %d failed, %d skipped.", passed, failed, skipped);
}
