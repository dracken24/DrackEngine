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
	return (value != 0) && ((value & (value - 1)) == 0);
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

#endif
