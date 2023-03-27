/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 26-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	    structs.hpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef STRUCTS_HPP
# define STRUCTS_HPP

# include "../core/defines.hpp"

// x, y signed int 32 bits
typedef	struct Vector2si16
{
	sint16	x;
	sint16	y;
}	Vector2si16;

// x, y signed int 32 bits
typedef	struct Vector2si
{
	sint32	x;
	sint32	y;
}	Vector2si;

// x, y unsigned int 32 bits
typedef	struct Vector2ui
{
	uint32	x;
	uint32	y;
}	Vector2ui;

// x, y float 32 bits
typedef	struct Vector2f
{
	fl32	x;
    fl32    y;
}	Vector2f;

// x, y double 64 bits
typedef	struct Vector2d
{
	dbl64	x;
	dbl64	y;
}	Vector2d;

#endif