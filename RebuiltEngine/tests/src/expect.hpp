/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 11-04-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     expect.hpp           *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <core/logger.hpp>
#include <math/deMath.hpp>

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Expects expected to be equal to actual.									//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
#define ExpectShouldBe(expected, actual)                                                                  \
	if (actual != expected)                                                                               \
	{                                                                                                     \
		DE_ERROR("--> Expected %lld, but got: %lld. File: %s:%d.", expected, actual, __FILE__, __LINE__); \
		return false;                                                                                     \
	}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Expects expected to NOT be equal to actual.								//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
#define ExpectShouldNotBe(expected, actual)                                                                   \
	if (actual == expected)                                                                                      \
	{                                                                                                            \
		DE_ERROR("--> Expected %d != %d, but they are equal. File: %s:%d.", expected, actual, __FILE__, __LINE__); \
		return false;                                                                                            \
	}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Expects expected to be actual given a tolerance of K_FLOAT_EPSILON.		//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
#define ExpectFloatToBe(expected, actual)                                                        \
	if (DE_Abs(expected - actual) > 0.001f)                                                           \
	{                                                                                               \
		DE_ERROR("--> Expected %f, but got: %f. File: %s:%d.", expected, actual, __FILE__, __LINE__); \
		return false;                                                                               \
	}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Expects actual to be true.												//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
#define ExpectToBeTrue(actual)                                                      \
	if (actual != true)                                                                \
	{                                                                                  \
		DE_ERROR("--> Expected true, but got: false. File: %s:%d.", __FILE__, __LINE__); \
		return false;                                                                  \
	}

//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
// @brief Expects actual to be false.												//
//~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-//
#define ExpectToBeFalse(actual)                                                     \
	if (actual != false)                                                               \
	{                                                                                  \
		DE_ERROR("--> Expected false, but got: true. File: %s:%d.", __FILE__, __LINE__); \
		return false;                                                                  \
	}
