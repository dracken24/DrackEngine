/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 09-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     deMath.hpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef DE_MATH_HPP
# define DE_MATH_HPP

#include <defines.hpp>
#include <math/structs.hpp>
#include <core/deMemory.hpp>

#define DE_PI 3.14159265358979323846f
#define DE_PI_2 2.0f * DE_PI
#define DE_HALF_PI 0.5f * DE_PI
#define DE_QUARTER_PI 0.25f * DE_PI
#define DE_ONE_OVER_PI 1.0f / DE_PI
#define DE_ONE_OVER_TWO_PI 1.0f / DE_PI_2
#define DE_sqirt_TWO 1.41421356237309504880f
#define DE_sqirt_THREE 1.73205080756887729352f
#define DE_sqirt_ONE_OVER_TWO 0.70710678118654752440f
#define DE_sqirt_ONE_OVER_THREE 0.57735026918962576450f
#define DE_DEG2RAD_MULTIPLIER DE_PI / 180.0f
#define DE_RAD2DEG_MULTIPLIER 180.0f / DE_PI

// The multiplier to convert seconds to milliseconds.
#define DE_SEC_TO_MS_MULTIPLIER 1000.0f

// The multiplier to convert milliseconds to seconds.
#define DE_MS_TO_SEC_MULTIPLIER 0.001f

// A huge number that should be larger than any valid number used.
#define DE_INFINITY 1e30f

// Smallest positive number where 1.0 + FLOAT_EPSILON != 0
#define DE_FLOAT_EPSILON 1.192092896e-07f

//**********************************************************************************//
// 							 General math functions							    	//
//**********************************************************************************//

DE_API fl32		DE_Sin(fl32 x);
DE_API fl32		DE_Cos(fl32 x);
DE_API fl32		DE_Tan(fl32 x);
DE_API fl32		DE_Acos(fl32 x);
DE_API fl32		DE_Sqirt(fl32 x);
DE_API fl32		DE_Abs(fl32 x);

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// Indicates if the value is a power of 2. 0 is considered _not_ a power of 2.		//
// @param value The value to be interpreted.								 		//
// @returns true if a power of 2, otherwise false.									//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE bl8	IsPowerOf2(uint64 value)
{
	return ((value != 0) && ((value & (value - 1)) == 0));
}

DE_API sint32	DE_Random();
DE_API sint32	DE_RandomInRange(sint32 min, sint32 max);

DE_API fl32		DE_Fl_Random();
DE_API fl32		DE_Fl_RandomInRange(fl32 min, fl32 max);


//**********************************************************************************//
// 							 			Vector 2							     	//
//**********************************************************************************//

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a new 2-element vector using the supplied values.		//
//																					//
// @param x The x value.															//
// @param y The y value.															//
// @return A new 2-element vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector2	Vector2Create(fl32 x, fl32 y)
{
	return (Vector2){x, y};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 2-component vector with all components set to 0.0f.	//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector2	Vector2Zero()
{
	return (Vector2){0.0f, 0.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 2-component vector with all components set to 1.0f.	//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector2	Vector2One()
{
	return (Vector2){1.0f, 1.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 2-component vector pointing up (0, 1).				//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector2 Vector2Up()
{
	return (Vector2){0.0f, 1.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 2-component vector pointing down (0, -1).			//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector2 Vector2Down()
{
	return (Vector2){0.0f, -1.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 2-component vector pointing left (-1, 0).			//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector2 Vector2Left()
{
	return (Vector2){-1.0f, 0.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 2-component vector pointing right (1, 0).			//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector2 Vector2Right()
{
	return (Vector2){1.0f, 0.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Adds vector_1 to vector_0 and returns a copy of the result.				//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The resulting vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector2	Vector2Add(Vector2 vector_0, Vector2 vector_1)
{
	return (Vector2){(vector_0.x + vector_1.x), (vector_0.y + vector_1.y)};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Subtracts vector_1 from vector_0 and returns a copy of the result.		//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The resulting vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector2	Vector2Sub(Vector2 vector_0, Vector2 vector_1)
{
	return (Vector2){(vector_0.x - vector_1.x), (vector_0.y - vector_1.y)};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Multiplies vector_0 by vector_1 and returns a copy of the result.			//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The resulting vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector2	Vector2Mul(Vector2 vector_0, Vector2 vector_1)
{
	return (Vector2){(vector_0.x * vector_1.x), (vector_0.y * vector_1.y)};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Divides vector_0 by vector_1 and returns a copy of the result.			//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The resulting vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector2	Vector2Div(Vector2 vector_0, Vector2 vector_1)
{
	return (Vector2){(vector_0.x / vector_1.x), (vector_0.y / vector_1.y)};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns the squared length of the provided vector.						//
//																					//
// @param vector The vector to retrieve the squared length of.						//
// @return The squared length.														//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE fl32		Vector2LengthSquared(Vector2 vector)
{
	return ((vector.x * vector.x) + (vector.y * vector.y));
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns the length of the provided vector.								//
//																					//
// @param vector The vector to retrieve the length of.								//
// @return The length.																//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE fl32		Vector2Length(Vector2 vector)
{
	return DE_Sqirt(Vector2LengthSquared(vector));
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Normalizes the provided vector in place to a unit vector.					//
//																					//
// @param vector A pointer to the vector to be normalized.							//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE void		Vector2Normalize(Vector2 *vector)
{
	const fl32 length = Vector2Length(*vector);
	vector->x /= length;
	vector->y /= length;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a normalized copy of the supplied vector.							//
//																					//
// @param vector The vector to be normalized.										//
// @return A normalized copy of the supplied vector									//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector2	Vector2Normalized(Vector2 vector)
{
	Vector2Normalize(&vector);

	return vector;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Compares all elements of vector_0 and vector_1 and ensures the difference	//
// is less than tolerance.															//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @param tolerance The difference tolerance. Typically K_FLOAT_EPSILON or similar.	//
// @return true if within tolerance; otherwise false.								//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE bl8		Vector2Compare(Vector2 vector_0, Vector2 vector_1, fl32 tolerance)
{
	if (DE_Abs(vector_0.x - vector_1.x) > tolerance)
	{
		return false;
	}

	if (DE_Abs(vector_0.y - vector_1.y) > tolerance)
	{
		return false;
	}

	return true;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns the distance between vector_0 and vector_1.						//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The distance between vector_0 and vector_1.								//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE fl32		Vector2Distance(Vector2 vector_0, Vector2 vector_1)
{
	Vector2 ret = (Vector2){(vector_0.x - vector_1.x), (vector_0.y - vector_1.y)};

	return Vector2Length(ret);
}


//**********************************************************************************//
// 							 			Vector 3							     	//
//**********************************************************************************//

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a new 3-element vector using the supplied values.		//
//																					//
// @param x The x value.															//
// @param y The y value.															//
// @param z The z value.															//
// @return A new 3-element vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Create(fl32 x, fl32 y, fl32 z)
{
	return (Vector3){x, y, z};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a new Vector3 containing the x, y and z components of the			//
// supplied Vector4, essentially dropping the w component.							//
//																					//
// @param vector The 4-component vector to extract from.							//
// @return A new Vector3															//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3FromVector4(Vector4 vector)
{
	return (Vector3){vector.x, vector.y, vector.z};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a new Vector4 using vector as the x, y and z components			//
// and w for the 4e value.															//
//																					//
// @param vector The 3-component vector.											//
// @param w The w component.														//
// @return A new Vector4															//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector4	Vector3ToVector4(Vector3 vector, fl32 w)
{
	return (Vector4){vector.x, vector.y, vector.z, w};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 3-component vector with all components set to 0.0f.	//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Zero()
{
	return (Vector3){0.0f, 0.0f, 0.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 3-component vector with all components set to 1.0f.	//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3One()
{
	return (Vector3){1.0f, 1.0f, 1.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 3-component vector pointing up (0, 1, 0).			//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Up()
{
	return (Vector3){0.0f, 1.0f, 0.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 3-component vector pointing down (0, -1, 0).		//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Down()
{
	return (Vector3){0.0f, -1.0f, 0.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 3-component vector pointing left (-1, 0, 0).		//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Left()
{
	return (Vector3){-1.0f, 0.0f, 0.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 3-component vector pointing right (1, 0, 0).		//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Right()
{
	return (Vector3){1.0f, 0.0f, 0.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 3-component vector pointing forward (0, 0, -1).		//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Forward()
{
	return (Vector3){0.0f, 0.0f, -1.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 3-component vector pointing backward (0, 0, 1).		//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Back()
{
	return (Vector3){0.0f, 0.0f, 1.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Adds vector_1 to vector_0 and returns a copy of the result.				//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The resulting vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Add(Vector3 vector_0, Vector3 vector_1)
{
	return (Vector3){
		(vector_0.x + vector_1.x),
		(vector_0.y + vector_1.y),
		(vector_0.z + vector_1.z)};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Subtracts vector_1 from vector_0 and returns a copy of the result.		//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The resulting vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Sub(Vector3 vector_0, Vector3 vector_1)
{
	return (Vector3){
		(vector_0.x - vector_1.x),
		(vector_0.y - vector_1.y),
		(vector_0.z - vector_1.z)};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Multiplies vector_0 by vector_1 and returns a copy of the result.			//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The resulting vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Mul(Vector3 vector_0, Vector3 vector_1)
{
	return (Vector3){
		(vector_0.x * vector_1.x),
		(vector_0.y * vector_1.y),
		(vector_0.z * vector_1.z)};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Multiplies all elements of vector_0 by scalar and returns 				//
// a copy of the result.															//
//																					//
// @param vector_0 The vector to be multiplied.										//
// @param scalar The scalar value.													//
// @return A copy of the resulting vector.											//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3MulScalar(Vector3 vector_0, fl32 scalar)
{
	return (Vector3){
		(vector_0.x * scalar),
		(vector_0.y * scalar),
		(vector_0.z * scalar)};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Divides vector_0 by vector_1 and returns a copy of the result.			//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The resulting vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Div(Vector3 vector_0, Vector3 vector_1)
{
	return (Vector3){
		(vector_0.x / vector_1.x),
		(vector_0.y / vector_1.y),
		(vector_0.z / vector_1.z)};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns the squared length of the provided vector.						//
//																					//
// @param vector The vector to retrieve the squared length of.						//
// @return The squared length.														//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE fl32		Vector3LengthSquared(Vector3 vector)
{
	return ((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns the length of the provided vector.								//
//																					//
// @param vector The vector to retrieve the length of.								//
// @return The length.																//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE fl32		Vector3Length(Vector3 vector)
{
	return DE_Sqirt(Vector3LengthSquared(vector));
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Normalizes the provided vector in place to a unit vector.					//
//																					//
// @param vector A pointer to the vector to be normalized.							//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE void		Vector3Normalize(Vector3 *vector)
{
	const fl32 length = Vector3Length(*vector);
	(vector->x /= length);
	(vector->y /= length);
	(vector->z /= length);
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a normalized copy of the supplied vector.							//
//																					//
// @param vector The vector to be normalized.										//
// @return A normalized copy of the supplied vector									//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Normalized(Vector3 vector)
{
	Vector3Normalize(&vector);

	return vector;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns the dot product between the provided vectors. Typically used		//
// to calculate the difference in direction.										//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The dot product.															//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE fl32		Vector3Dot(Vector3 vector_0, Vector3 vector_1)
{
	fl32 ret = 0;

	ret += (vector_0.x * vector_1.x);
	ret += (vector_0.y * vector_1.y);
	ret += (vector_0.z * vector_1.z);

	return ret;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Calculates and returns the cross product of the supplied vectors.			//
// The cross product is a new vector which is orthoganal to both provided vectors.	//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The cross product.														//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector3Cross(Vector3 vector_0, Vector3 vector_1)
{
	return (Vector3){
		((vector_0.y * vector_1.z) - (vector_0.z * vector_1.y)),
		((vector_0.z * vector_1.x) - (vector_0.x * vector_1.z)),
		((vector_0.x * vector_1.y) - (vector_0.y * vector_1.x))};
}

/**
 * @brief Compares all elements of vector_0 and vector_1 and ensures the difference
 * is less than tolerance.
 *
 * @param vector_0 The first vector.
 * @param vector_1 The second vector.
 * @param tolerance The difference tolerance. Typically K_FLOAT_EPSILON or similar.
 * @return true if within tolerance; otherwise false.
 */
DE_INLINE const bl8	Vector3Compare(Vector3 vector_0, Vector3 vector_1, fl32 tolerance)
{
	if (DE_Abs(vector_0.x - vector_1.x) > tolerance)
	{
		return false;
	}

	if (DE_Abs(vector_0.y - vector_1.y) > tolerance)
	{
		return false;
	}

	if (DE_Abs(vector_0.z - vector_1.z) > tolerance)
	{
		return false;
	}

	return true;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns the distance between vector_0 and vector_1.						//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The distance between vector_0 and vector_1.								//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE fl32	Vector3Distance(Vector3 vector_0, Vector3 vector_1)
{
	Vector3 ret = (Vector3){
		(vector_0.x - vector_1.x),
		(vector_0.y - vector_1.y),
		(vector_0.z - vector_1.z)};

	return Vector3Length(ret);
}


//**********************************************************************************//
// 							 			Vector 4							     	//
//**********************************************************************************//

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a new 4-element vector using the supplied values.		//
//																					//
// @param x The x value.															//
// @param y The y value.															//
// @param z The z value.															//
// @param w The w value.															//
// @return A new 4-element vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector4	Vector4Create(fl32 x, fl32 y, fl32 z, fl32 w)
{
	Vector4 ret;
#if defined(KUSE_SIMD)
	out_vector.data = _mm_setr_ps(x, y, z, w);
#else
	ret.x = x;
	ret.y = y;
	ret.z = z;
	ret.w = w;
#endif
	return ret;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a new Vector3 containing the x, y and z components of the			//
// supplied Vector4, essentially dropping the w component.							//
//																					//
// @param vector The 4-component vector to extract from.							//
// @return A new Vector3															//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Vector4ToVector3(Vector4 vector)
{
	return (Vector3){vector.x, vector.y, vector.z};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a new Vector4 using vector as the x, y and z components			//
// and w for w.																		//
//																					//
// @param vector The 3-component vector.											//
// @param w The w component.														//
// @return A new Vector4															//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector4	Vector4FromVector3(Vector3 vector, fl32 w)
{
#if defined(KUSE_SIMD)
	Vector4 ret;
	ret.data = _mm_setr_ps(x, y, z, w);
	return ret;
#else
	return (Vector4){vector.x, vector.y, vector.z, w};
#endif
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 3-component vector with all components set to 0.0f.	//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector4	Vector4_Zero()
{
	return (Vector4){0.0f, 0.0f, 0.0f, 0.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a 3-component vector with all components set to 1.0f.	//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector4	Vector4One()
{
	return (Vector4){1.0f, 1.0f, 1.0f, 1.0f};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Adds vector_1 to vector_0 and returns a copy of the result.				//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The resulting vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector4	Vector4Add(Vector4 vector_0, Vector4 vector_1)
{
	Vector4 result;
	for (uint64 i = 0; i < 4; ++i)
	{
		result.elements[i] = vector_0.elements[i] + vector_1.elements[i];
	}

	return result;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Subtracts vector_1 from vector_0 and returns a copy of the result.		//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The resulting vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector4	Vector4Sub(Vector4 vector_0, Vector4 vector_1)
{
	Vector4 result;
	for (uint64 i = 0; i < 4; ++i)
	{
		result.elements[i] = vector_0.elements[i] - vector_1.elements[i];
	}

	return result;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Multiplies vector_0 by vector_1 and returns a copy of the result.			//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The resulting vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector4	Vector4Mul(Vector4 vector_0, Vector4 vector_1)
{
	Vector4 result;
	for (uint64 i = 0; i < 4; ++i)
	{
		result.elements[i] = vector_0.elements[i] * vector_1.elements[i];
	}

	return result;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Divides vector_0 by vector_1 and returns a copy of the result.			//
//																					//
// @param vector_0 The first vector.												//
// @param vector_1 The second vector.												//
// @return The resulting vector.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector4	Vector4Div(Vector4 vector_0, Vector4 vector_1)
{
	Vector4 result;
	for (uint64 i = 0; i < 4; ++i)
	{
		result.elements[i] = vector_0.elements[i] / vector_1.elements[i];
	}

	return result;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns the squared length of the provided vector.						//
//																					//
// @param vector The vector to retrieve the squared length of.						//
// @return The squared length.														//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE fl32	Vector4LengthSquared(Vector4 vector)
{
	return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z + vector.w * vector.w;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns the length of the provided vector.								//
//																					//
// @param vector The vector to retrieve the length of.								//
// @return The length.																//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE fl32	Vector4Length(Vector4 vector)
{
	return DE_Sqirt(Vector4LengthSquared(vector));
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Normalizes the provided vector in place to a unit vector.					//
//																					//
// @param vector A pointer to the vector to be normalized.							//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE void	Vector4Normalize(Vector4 *vector)
{
	const fl32 length = Vector4Length(*vector);
	vector->x /= length;
	vector->y /= length;
	vector->z /= length;
	vector->w /= length;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a normalized copy of the supplied vector.							//
//																					//
// @param vector The vector to be normalized.										//
// @return A normalized copy of the supplied vector									//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector4	Vector4Normalized(Vector4 vector)
{
	Vector4Normalize(&vector);

	return vector;
}

DE_INLINE fl32	Vector4DotFl32(fl32 a0, fl32 a1, fl32 a2, fl32 a3,
								fl32 b0, fl32 b1, fl32 b2, fl32 b3)
{
	fl32 ret;
	ret = (a0 * b0) + (a1 * b1) + (a2 * b2) + (a3 * b3);

	return ret;
}


//**********************************************************************************//
// 							 			Matrix								     	//
//**********************************************************************************//

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns an identity matrix:									//
//																					//
// {																				//
//   {1, 0, 0, 0},																	//
//   {0, 1, 0, 0},																	//
//   {0, 0, 1, 0},																	//
//   {0, 0, 0, 1}																	//
// }																				//
//																					//
// @return A new identity matrix													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Matrix4	Matrix4Identity()
{
	Matrix4	retMatrix;

	SetMemory(retMatrix.data, sizeof(fl32) * 16);

	retMatrix.data[0] = 1.0f;
	retMatrix.data[5] = 1.0f;
	retMatrix.data[10] = 1.0f;
	retMatrix.data[15] = 1.0f;

	return retMatrix;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns the result of multiplying matrix_0 and matrix_1.					//
//																					//
// @param matrix_0 The first matrix to be multiplied.								//
// @param matrix_1 The second matrix to be multiplied.								//
// @return The result of the matrix multiplication.									//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Matrix4	Matrix4Mul(Matrix4 matrix_0, Matrix4 matrix_1)
{
	Matrix4 retMatrix = Matrix4Identity();

	const fl32 *m1_ptr = matrix_0.data;
	const fl32 *m2_ptr = matrix_1.data;
	fl32 *dst_ptr = retMatrix.data;

	for (sint32 i = 0; i < 4; ++i)
	{
		for (sint32 j = 0; j < 4; ++j)
		{
			*dst_ptr =
				m1_ptr[0] * m2_ptr[0 + j] +
				m1_ptr[1] * m2_ptr[4 + j] +
				m1_ptr[2] * m2_ptr[8 + j] +
				m1_ptr[3] * m2_ptr[12 + j];
			dst_ptr++;
		}
		m1_ptr += 4;
	}

	return retMatrix;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns an orthographic projection matrix. Typically used to	//
// render flat or 2D scenes.														//
//																					//
// @param left The left side of the view frustum.									//
// @param right The right side of the view frustum.									//
// @param bottom The bottom side of the view frustum.								//
// @param top The top side of the view frustum.										//
// @param near_clip The near clipping plane distance.								//
// @param far_clip The far clipping plane distance.									//
// @return A new orthographic projection matrix.									//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Matrix4	Matrix4Orthographic(fl32 left, fl32 right, fl32 bottom, fl32 top, fl32 near_clip, fl32 far_clip)
{
	Matrix4 retMatrix = Matrix4Identity();

	fl32 lr = 1.0f / (left - right);
	fl32 bt = 1.0f / (bottom - top);
	fl32 nf = 1.0f / (near_clip - far_clip);

	retMatrix.data[0] = -2.0f * lr;
	retMatrix.data[5] = -2.0f * bt;
	retMatrix.data[10] = 2.0f * nf;

	retMatrix.data[12] = (left + right) * lr;
	retMatrix.data[13] = (top + bottom) * bt;
	retMatrix.data[14] = (far_clip + near_clip) * nf;

	return retMatrix;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a perspective matrix. Typically used					//
// to render 3d scenes.																//
//																					//
// @param fov_radians The field of view in radians.									//
// @param aspect_ratio The aspect ratio.											//
// @param near_clip The near clipping plane distance.								//
// @param far_clip The far clipping plane distance.									//
// @return A new perspective matrix.												//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Matrix4	Matrix4Perspective(fl32 fovRadians, fl32 aspectRatio, fl32 nearClip, fl32 farClip)
{
	fl32 halfTanFov = DE_Tan(fovRadians * 0.5f);
	Matrix4 retMatrix;

	SetMemory(retMatrix.data, sizeof(fl32) * 16);

	retMatrix.data[0] = 1.0f / (aspectRatio * halfTanFov);
	retMatrix.data[5] = 1.0f / halfTanFov;
	retMatrix.data[10] = -((farClip + nearClip) / (farClip - nearClip));
	retMatrix.data[11] = -1.0f;
	retMatrix.data[14] = -((2.0f * farClip * nearClip) / (farClip - nearClip));

	return retMatrix;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns a look-at matrix, or a matrix looking					//
// at target from the perspective of position.										//
//																					//
// @param position The position of the matrix.										//
// @param target The position to "look at".											//
// @param up The up vector.															//
// @return A matrix looking at target from the perspective of position.				//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Matrix4	Matrix4LookAt(Vector3 position, Vector3 target, Vector3 up)
{
	Matrix4 retMatrix;
	Vector3 Zaxis;
	Zaxis.x = target.x - position.x;
	Zaxis.y = target.y - position.y;
	Zaxis.z = target.z - position.z;

	Zaxis = Vector3Normalized(Zaxis);
	Vector3 Xaxis = Vector3Normalized(Vector3Cross(Zaxis, up));
	Vector3 Yaxis = Vector3Cross(Xaxis, Zaxis);

	retMatrix.data[0] = Xaxis.x;
	retMatrix.data[1] = Yaxis.x;
	retMatrix.data[2] = -Zaxis.x;
	retMatrix.data[3] = 0;

	retMatrix.data[4] = Xaxis.y;
	retMatrix.data[5] = Yaxis.y;
	retMatrix.data[6] = -Zaxis.y;
	retMatrix.data[7] = 0;

	retMatrix.data[8] = Xaxis.z;
	retMatrix.data[9] = Yaxis.z;
	retMatrix.data[10] = -Zaxis.z;
	retMatrix.data[11] = 0;

	retMatrix.data[12] = -Vector3Dot(Xaxis, position);
	retMatrix.data[13] = -Vector3Dot(Yaxis, position);
	retMatrix.data[14] = Vector3Dot(Zaxis, position);
	retMatrix.data[15] = 1.0f;

	return retMatrix;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a transposed copy of the provided matrix (rows->colums)			//
//																					//
// @param matrix The matrix to be transposed.										//
// @return A transposed copy of of the provided matrix.								//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Matrix4	Matrix4Transposed(Matrix4 matrix)
{
	Matrix4 retMatrix = Matrix4Identity();

	retMatrix.data[0] = matrix.data[0];
	retMatrix.data[1] = matrix.data[4];
	retMatrix.data[2] = matrix.data[8];
	retMatrix.data[3] = matrix.data[12];

	retMatrix.data[4] = matrix.data[1];
	retMatrix.data[5] = matrix.data[5];
	retMatrix.data[6] = matrix.data[9];
	retMatrix.data[7] = matrix.data[13];

	retMatrix.data[8] = matrix.data[2];
	retMatrix.data[9] = matrix.data[6];
	retMatrix.data[10] = matrix.data[10];
	retMatrix.data[11] = matrix.data[14];

	retMatrix.data[12] = matrix.data[3];
	retMatrix.data[13] = matrix.data[7];
	retMatrix.data[14] = matrix.data[11];
	retMatrix.data[15] = matrix.data[15];

	return retMatrix;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Creates and returns an inverse of the provided matrix.					//
//																					//
// @param matrix The matrix to be inverted.											//
// @return A inverted copy of the provided matrix.									//
// "Pass from 2d space to 3dspace projection"										//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Matrix4	Matrix4Inverse(Matrix4 matrix)
{
	const fl32 *m = matrix.data;

	fl32 t0 = m[10] * m[15];
	fl32 t1 = m[14] * m[11];
	fl32 t2 = m[6] * m[15];
	fl32 t3 = m[14] * m[7];

	fl32 t4 = m[6] * m[11];
	fl32 t5 = m[10] * m[7];
	fl32 t6 = m[2] * m[15];
	fl32 t7 = m[14] * m[3];

	fl32 t8 = m[2] * m[11];
	fl32 t9 = m[10] * m[3];
	fl32 t10 = m[2] * m[7];
	fl32 t11 = m[6] * m[3];

	fl32 t12 = m[8] * m[13];
	fl32 t13 = m[12] * m[9];
	fl32 t14 = m[4] * m[13];
	fl32 t15 = m[12] * m[5];

	fl32 t16 = m[4] * m[9];
	fl32 t17 = m[8] * m[5];
	fl32 t18 = m[0] * m[13];
	fl32 t19 = m[12] * m[1];

	fl32 t20 = m[0] * m[9];
	fl32 t21 = m[8] * m[1];
	fl32 t22 = m[0] * m[5];
	fl32 t23 = m[4] * m[1];

	Matrix4 retMatrix;
	fl32 *o = retMatrix.data;

	o[0] = (t0 * m[5] + t3 * m[9] + t4 * m[13]) - (t1 * m[5] + t2 * m[9] + t5 * m[13]);
	o[1] = (t1 * m[1] + t6 * m[9] + t9 * m[13]) - (t0 * m[1] + t7 * m[9] + t8 * m[13]);
	o[2] = (t2 * m[1] + t7 * m[5] + t10 * m[13]) - (t3 * m[1] + t6 * m[5] + t11 * m[13]);
	o[3] = (t5 * m[1] + t8 * m[5] + t11 * m[9]) - (t4 * m[1] + t9 * m[5] + t10 * m[9]);

	fl32 d = 1.0f / (m[0] * o[0] + m[4] * o[1] + m[8] * o[2] + m[12] * o[3]);

	o[0] = d * o[0];
	o[1] = d * o[1];
	o[2] = d * o[2];
	o[3] = d * o[3];

	o[4] = d * ((t1 * m[4] + t2 * m[8] + t5 * m[12]) - (t0 * m[4] + t3 * m[8] + t4 * m[12]));
	o[5] = d * ((t0 * m[0] + t7 * m[8] + t8 * m[12]) - (t1 * m[0] + t6 * m[8] + t9 * m[12]));
	o[6] = d * ((t3 * m[0] + t6 * m[4] + t11 * m[12]) - (t2 * m[0] + t7 * m[4] + t10 * m[12]));
	o[7] = d * ((t4 * m[0] + t9 * m[4] + t10 * m[8]) - (t5 * m[0] + t8 * m[4] + t11 * m[8]));

	o[8] = d * ((t12 * m[7] + t15 * m[11] + t16 * m[15]) - (t13 * m[7] + t14 * m[11] + t17 * m[15]));
	o[9] = d * ((t13 * m[3] + t18 * m[11] + t21 * m[15]) - (t12 * m[3] + t19 * m[11] + t20 * m[15]));
	o[10] = d * ((t14 * m[3] + t19 * m[7] + t22 * m[15]) - (t15 * m[3] + t18 * m[7] + t23 * m[15]));
	o[11] = d * ((t17 * m[3] + t20 * m[7] + t23 * m[11]) - (t16 * m[3] + t21 * m[7] + t22 * m[11]));

	o[12] = d * ((t14 * m[10] + t17 * m[14] + t13 * m[6]) - (t16 * m[14] + t12 * m[6] + t15 * m[10]));
	o[13] = d * ((t20 * m[14] + t12 * m[2] + t19 * m[10]) - (t18 * m[10] + t21 * m[14] + t13 * m[2]));
	o[14] = d * ((t18 * m[6] + t23 * m[14] + t15 * m[2]) - (t22 * m[14] + t14 * m[2] + t19 * m[6]));
	o[15] = d * ((t22 * m[10] + t16 * m[2] + t21 * m[6]) - (t20 * m[6] + t23 * m[10] + t17 * m[2]));

	return retMatrix;
}

DE_INLINE Matrix4	Matrix4Translation(Vector3 position)
{
	Matrix4 retMatrix = Matrix4Identity();

	retMatrix.data[12] = position.x;
	retMatrix.data[13] = position.y;
	retMatrix.data[14] = position.z;

	return retMatrix;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a scale matrix using the provided scale.							//
//																					//
// @param scale The 3-component scale.												//
// @return A scale matrix.															//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Matrix4	Matrix4Scale(Vector3 scale)
{
	Matrix4 retMatrix = Matrix4Identity();

	retMatrix.data[0] = scale.x;
	retMatrix.data[5] = scale.y;
	retMatrix.data[10] = scale.z;

	return retMatrix;
}

DE_INLINE Matrix4	Matrix4EulerX(fl32 angleRadians)
{
	Matrix4 retMatrix = Matrix4Identity();
	fl32 c = DE_Cos(angleRadians);
	fl32 s = DE_Sin(angleRadians);

	retMatrix.data[5] = c;
	retMatrix.data[6] = s;
	retMatrix.data[9] = -s;
	retMatrix.data[10] = c;

	return retMatrix;
}

DE_INLINE Matrix4	Matrix4EulerY(fl32 YangleRadians)
{
	Matrix4 retMatrix = Matrix4Identity();
	fl32 c = DE_Cos(YangleRadians);
	fl32 s = DE_Sin(YangleRadians);

	retMatrix.data[0] = c;
	retMatrix.data[2] = -s;
	retMatrix.data[8] = s;
	retMatrix.data[10] = c;

	return retMatrix;
}

DE_INLINE Matrix4	Matrix4EulerZ(fl32 YangleRadians)
{
	Matrix4 retMatrix = Matrix4Identity();

	fl32 c = DE_Cos(YangleRadians);
	fl32 s = DE_Sin(YangleRadians);

	retMatrix.data[0] = c;
	retMatrix.data[1] = s;
	retMatrix.data[4] = -s;
	retMatrix.data[5] = c;

	return retMatrix;
}

DE_INLINE Matrix4	Matrix4EulerXyz(fl32 x_radians, fl32 y_radians, fl32 z_radians)
{
	Matrix4 rx = Matrix4EulerX(x_radians);
	Matrix4 ry = Matrix4EulerY(y_radians);
	Matrix4 rz = Matrix4EulerZ(z_radians);
	Matrix4 retMatrix = Matrix4Mul(rx, ry);

	retMatrix = Matrix4Mul(retMatrix, rz);

	return retMatrix;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a forward vector relative to the provided matrix.					//
//																					//
// @param matrix The matrix from which to base the vector.							//
// @return A 3-component directional vector.										//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Matrix4Forward(Matrix4 matrix)
{
	Vector3 forward;
	forward.x = -matrix.data[2];
	forward.y = -matrix.data[6];
	forward.z = -matrix.data[10];

	Vector3Normalize(&forward);//
	return forward;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a backward vector relative to the provided matrix.				//
//																					//
// @param matrix The matrix from which to base the vector.							//
// @return A 3-component directional vector.										//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Matrix4Backward(Matrix4 matrix)
{
	Vector3 backward;

	backward.x = matrix.data[2];
	backward.y = matrix.data[6];
	backward.z = matrix.data[10];

	Vector3Normalize(&backward);

	return backward;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a upward vector relative to the provided matrix.					//
//																					//
// @param matrix The matrix from which to base the vector.							//
// @return A 3-component directional vector.										//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Matrix4Up(Matrix4 matrix)
{
	Vector3 up;

	up.x = matrix.data[1];
	up.y = matrix.data[5];
	up.z = matrix.data[9];

	Vector3Normalize(&up);

	return up;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a downward vector relative to the provided matrix.				//
//																					//
// @param matrix The matrix from which to base the vector.							//
// @return A 3-component directional vector.										//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Matrix4Down(Matrix4 matrix)
{
	Vector3 down;

	down.x = -matrix.data[1];
	down.y = -matrix.data[5];
	down.z = -matrix.data[9];

	Vector3Normalize(&down);

	return down;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a left vector relative to the provided matrix.					//
//																					//
// @param matrix The matrix from which to base the vector.							//
// @return A 3-component directional vector.										//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Matrix4Left(Matrix4 matrix)
{
	Vector3 left;

	left.x = -matrix.data[0];
	left.y = -matrix.data[4];
	left.z = -matrix.data[8];

	Vector3Normalize(&left);

	return left;
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Returns a right vector relative to the provided matrix.					//
//																					//
// @param matrix The matrix from which to base the vector.							//
// @return A 3-component directional vector.										//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE Vector3	Matrix4Right(Matrix4 matrix)
{
	Vector3 right;

	right.x = matrix.data[0];
	right.y = matrix.data[4];
	right.z = matrix.data[8];

	Vector3Normalize(&right);

	return right;
}


//**********************************************************************************//
// 							 		Queternions							     	    //
//**********************************************************************************//

DE_INLINE quat		QuatIdentity()
{
	return (quat){0, 0, 0, 1.0f};
}

DE_INLINE fl32		QuatNormal(quat q)
{
	return DE_Sqirt((q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w));
}

DE_INLINE quat		QuatNormalize(quat q)
{
	fl32 normal = QuatNormal(q);

	return (quat){(q.x / normal), (q.y / normal), (q.z / normal), (q.w / normal)};
}

DE_INLINE quat		QuatConjugate(quat q)
{
	return (quat){-q.x, -q.y, -q.z, q.w};
}

DE_INLINE quat		QuatInverse(quat q)
{
	return QuatNormalize(QuatConjugate(q));
}

DE_INLINE quat		QuatMul(quat q_0, quat q_1)
{
	quat out_quaternion;

	out_quaternion.x = q_0.x * q_1.w +
					   q_0.y * q_1.z -
					   q_0.z * q_1.y +
					   q_0.w * q_1.x;

	out_quaternion.y = -q_0.x * q_1.z +
					   q_0.y * q_1.w +
					   q_0.z * q_1.x +
					   q_0.w * q_1.y;

	out_quaternion.z = q_0.x * q_1.y -
					   q_0.y * q_1.x +
					   q_0.z * q_1.w +
					   q_0.w * q_1.z;

	out_quaternion.w = -q_0.x * q_1.x -
					   q_0.y * q_1.y -
					   q_0.z * q_1.z +
					   q_0.w * q_1.w;

	return out_quaternion;
}

DE_INLINE fl32		QuatDot(quat q_0, quat q_1)
{
	return ((q_0.x * q_1.x) + (q_0.y * q_1.y) + (q_0.z * q_1.z) + (q_0.w * q_1.w));
}

DE_INLINE Matrix4	QuatToMatrix4(quat q)
{
	Matrix4 retMatrix = Matrix4Identity();

	// https://stackoverflow.com/questions/1556260/convert-quaternion-rotation-to-rotation-matrix

	quat n = QuatNormalize(q);

	retMatrix.data[0] = 1.0f - 2.0f * n.y * n.y - 2.0f * n.z * n.z;
	retMatrix.data[1] = 2.0f * n.x * n.y - 2.0f * n.z * n.w;
	retMatrix.data[2] = 2.0f * n.x * n.z + 2.0f * n.y * n.w;

	retMatrix.data[4] = 2.0f * n.x * n.y + 2.0f * n.z * n.w;
	retMatrix.data[5] = 1.0f - 2.0f * n.x * n.x - 2.0f * n.z * n.z;
	retMatrix.data[6] = 2.0f * n.y * n.z - 2.0f * n.x * n.w;

	retMatrix.data[8] = 2.0f * n.x * n.z - 2.0f * n.y * n.w;
	retMatrix.data[9] = 2.0f * n.y * n.z + 2.0f * n.x * n.w;
	retMatrix.data[10] = 1.0f - 2.0f * n.x * n.x - 2.0f * n.y * n.y;

	return retMatrix;
}

// Calculates a rotation matrix based on the quaternion and the passed in center point.
DE_INLINE Matrix4	QuatToRotationMatrix(quat q, Vector3 center)
{
	Matrix4 retMatrix;

	fl32 *o = retMatrix.data;

	o[0] = (q.x * q.x) - (q.y * q.y) - (q.z * q.z) + (q.w * q.w);
	o[1] = 2.0f * ((q.x * q.y) + (q.z * q.w));
	o[2] = 2.0f * ((q.x * q.z) - (q.y * q.w));
	o[3] = center.x - center.x * o[0] - center.y * o[1] - center.z * o[2];

	o[4] = 2.0f * ((q.x * q.y) - (q.z * q.w));
	o[5] = -(q.x * q.x) + (q.y * q.y) - (q.z * q.z) + (q.w * q.w);
	o[6] = 2.0f * ((q.y * q.z) + (q.x * q.w));
	o[7] = center.y - center.x * o[4] - center.y * o[5] - center.z * o[6];

	o[8] = 2.0f * ((q.x * q.z) + (q.y * q.w));
	o[9] = 2.0f * ((q.y * q.z) - (q.x * q.w));
	o[10] = -(q.x * q.x) - (q.y * q.y) + (q.z * q.z) + (q.w * q.w);
	o[11] = center.z - center.x * o[8] - center.y * o[9] - center.z * o[10];

	o[12] = 0.0f;
	o[13] = 0.0f;
	o[14] = 0.0f;
	o[15] = 1.0f;

	return retMatrix;
}

DE_INLINE quat		QuatFromAxisAngle(Vector3 axis, fl32 angle, bl8 normalize)
{
	const fl32 half_angle = 0.5f * angle;
	fl32 s = DE_Sin(half_angle);
	fl32 c = DE_Cos(half_angle);

	quat q = (quat){s * axis.x, s * axis.y, s * axis.z, c};

	if (normalize)
	{
		return QuatNormalize(q);
	}

	return q;
}

DE_INLINE quat		QuatSlerp(quat q_0, quat q_1, fl32 percentage)
{
	quat retQuaternion;
	// Source: https://en.wikipedia.org/wiki/Slerp
	// Only unit quaternions are valid rotations.
	// Normalize to avoid undefined behavior.
	quat v0 = QuatNormalize(q_0);
	quat v1 = QuatNormalize(q_1);

	// Compute the cosine of the angle between the two vectors.
	fl32 dot = QuatDot(v0, v1);

	// If the dot product is negative, slerp won't take
	// the shorter path. Note that v1 and -v1 are equivalent when
	// the negation is applied to all four components. Fix by
	// reversing one quaternion.
	if (dot < 0.0f)
	{
		v1.x = -v1.x;
		v1.y = -v1.y;
		v1.z = -v1.z;
		v1.w = -v1.w;
		dot = -dot;
	}

	const fl32 DOT_THRESHOLD = 0.9995f;
	if (dot > DOT_THRESHOLD)
	{
		// If the inputs are too close for comfort, linearly interpolate
		// and normalize the result.
		retQuaternion = (quat){
			v0.x + ((v1.x - v0.x) * percentage),
			v0.y + ((v1.y - v0.y) * percentage),
			v0.z + ((v1.z - v0.z) * percentage),
			v0.w + ((v1.w - v0.w) * percentage)};

		return QuatNormalize(retQuaternion);
	}

	// Since dot is in range [0, DOT_THRESHOLD], acos is safe
	fl32 theta_0 = DE_Acos(dot);		  // theta_0 = angle between input vectors
	fl32 theta = theta_0 * percentage; // theta = angle between v0 and result
	fl32 sinTheta = DE_Sin(theta);	  // compute this value only once
	fl32 sinTheta_0 = DE_Sin(theta_0);  // compute this value only once

	fl32 s0 = DE_Cos(theta) - dot * sinTheta / sinTheta_0; // == sin(theta_0 - theta) / sin(theta_0)
	fl32 s1 = sinTheta / sinTheta_0;

	return (quat){(v0.x * s0) + (v1.x * s1), (v0.y * s0) + (v1.y * s1),
					(v0.z * s0) + (v1.z * s1), (v0.w * s0) + (v1.w * s1)};
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Converts provided degrees to radians.										//
//																					//
// @param degrees The degrees to be converted.										//
// @return The amount in radians.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE fl32	DegToRad(fl32 degrees)
{
	return (degrees * DE_DEG2RAD_MULTIPLIER);
}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Converts provided radians to degrees.										//
//																					//
// @param radians The radians to be converted.										//
// @return The amount in degrees.													//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
DE_INLINE fl32	RadToDeg(fl32 radians)
{
	return (radians * DE_RAD2DEG_MULTIPLIER);
}

#endif
