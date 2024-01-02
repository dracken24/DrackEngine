/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 10-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     deMath.cpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include "deMath.hpp"

#include <math.h>
#include <stdlib.h>
#include <time.h>

static bl8 randSeeded = false;

/**
 * Note that these are here in order to prevent having to import the
 * entire <math.h> everywhere.
 */
fl32    DE_Sin(fl32 x)
{
    return sinf(x);
}

fl32    DE_Cos(fl32 x)
{
    return cosf(x);
}

fl32    DE_Tan(fl32 x)
{
    return tanf(x);
}

fl32    DE_Acos(fl32 x)
{
    return acosf(x);
}

fl32    DE_Sqirt(fl32 x)
{
    return sqrtf(x);
}

fl32    DE_Abs(fl32 x)
{
    return fabsf(x);
}

dbl64	PlatformGetAbsoluteTime()
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);

	return now.tv_sec + now.tv_nsec * 0.000000001;
}

sint32  DE_Random()
{
    if (!randSeeded)
    {
        srand((uint32)PlatformGetAbsoluteTime());
        randSeeded = true;
    }

    return rand();
}

sint32  DE_RandomInRange(sint32 min, sint32 max)
{
    if (!randSeeded)
    {
        srand((uint32)PlatformGetAbsoluteTime());

        randSeeded = true;
    }

    return ((rand() % (max - min + 1)) + min);
}

fl32    DE_Fl_Random()
{
    return ((float)DE_Random() / (fl32)RAND_MAX);
}

fl32    DE_Fl_Random_in_range(fl32 min, fl32 max)
{
    return (min + ((float)DE_Random() / ((fl32)RAND_MAX / (max - min))));
}
