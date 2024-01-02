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

# include "../includes/defines.hpp"

typedef union vec2_u
{
	// An array of x, y
	fl32 elements[2];
	struct
	{
		union
		{
			// The first element.
			fl32 x, r, s, u, width;
		};
		union
		{
			// The second element.
			fl32 y, g, t, v, height;
		};
	};
} Vector2;

typedef struct vec3_u
{
	union
	{
		// An array of x, y, z
		fl32 elements[3];
		struct
		{
			union
			{
				// The first element.
				fl32 x, r, s, u;
			};
			union
			{
				// The second element.
				fl32 y, g, t, v;
			};
			union
			{
				// The third element.
				fl32 z, b, p, w;
			};
		};
	};
} Vector3;

typedef union vec4_u
{
#if defined(KUSE_SIMD)
	// Used for SIMD operations.
	alignas(16) __m128 data;
#endif
	// An array of x, y, z, w
	alignas(16) fl32 elements[4];
	union
	{
		struct
		{
			union
			{
				// The first element.
				fl32 x, r, s;
			};
			union
			{
				// The second element.
				fl32 y, g, t;
			};
			union
			{
				// The third element.
				fl32 z, b, p, whide;
			};
			union
			{
				// The fourth element.
				fl32 w, a, q, hight;
			};
		};
	};
} Vector4;

typedef Vector4 quat;

typedef union	mat_4
{
	alignas(16) fl32 data[16];
#if defined(KUSE_SIMD)
	alignas(16) Vector4 rows[4];
#endif
}	Matrix4;

typedef struct	vertex3d
{
	Vector3 position;
}	vertex3d;

#endif
