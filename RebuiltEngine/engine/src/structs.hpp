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

# include "defines.hpp"

// x, y signed int 32 bits
typedef	struct Vector2ssint16
{
	sint16	x;
	sint16	y;
}	Vector2ssint16;

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

// x, y unsigned int 32 bits
typedef struct Vector2ui16
{
	uint16 x;
	uint16 y;
} Vector2ui16;

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

//***************************************************************************************//
// Vector3

// x, y, z signed int 32 bits
typedef	struct Vector3ssint16
{
	sint16	x;
	sint16	y;
	sint16	z;
}	Vector3ssint16;

// x, y, z signed int 32 bits
typedef	struct Vector3si
{
	sint32	x;
	sint32	y;
	sint32	z;
}	Vector3si;

// x, y, z unsigned int 32 bits
typedef	struct Vector3ui
{
	uint32	x;
	uint32	y;
	uint32	z;
}	Vector3ui;

// x, y, z unsigned int 32 bits
typedef struct Vector3ui16
{
	uint16 x;
	uint16 y;
	uint16 z;
} Vector3ui16;

// x, y, z float 32 bits
typedef	struct Vector3f
{
	fl32	x;
	fl32    y;
	fl32    z;
}	Vector3f;

// x, y, z double 64 bits
typedef	struct Vector3d
{
	dbl64	x;
	dbl64	y;
	dbl64	z;
}	Vector3d;

//***************************************************************************************//

typedef struct	RgbaFl32
{
	fl32	r;
	fl32	g;
	fl32	b;
	fl32	a;
}	RgbaFl32;

#endif
