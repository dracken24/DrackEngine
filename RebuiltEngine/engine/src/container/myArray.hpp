/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	     myArray.hpp          *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef MYARRAY_HPP
# define MYARRAY_HPP

# include "../includes/core/defines.hpp"

/*
Memory layout
uint64 capacity = number elements that can be held
uint64 length = number of elements currently contained
uint64 stride = size of each element in bytes
void* elements
*/

enum
{
	MYARRAY_CAPACITY,
	MYARRAY_LENGTH,
	MYARRAY_STRIDE,
	MYARRAY_FIELD_LENGTH
};

DE_API void		*_MyArrayCreate(uint64 length, uint64 stride);
DE_API void		_MyArrayDestroy(void *array);

DE_API uint64	_MyArrayFieldGet(void *array, uint64 field);
DE_API void		_MyArrayFieldSet(void *array, uint64 field, uint64 value);

DE_API void		*_MyArrayResize(void *array);

DE_API void		*_MyArrayPush(void *array, const void *valuePtr);
DE_API void		_MyArrayPop(void *array, void *dest);

DE_API void		*_MyArrayPopAt(void *array, uint64 index, void *dest);
DE_API void		*_MyArrayInsertAt(void *array, uint64 index, void *valuePtr);

#define MYARRAY_DEFAULT_CAPACITY 1
#define MYARRAY_RESIZE_FACTOR 2

#define MyArrayCreate(type) \
	_MyArrayCreate(MYARRAY_DEFAULT_CAPACITY, sizeof(type))

#define MyArrayReserve(type, capacity) \
	_MyArrayCreate(capacity, decltype(type))

#define MyArrayDestroy(array) _MyArrayDestroy(array);

#define MyArrayPush(array, value)                                                                                                                \
	{                                                                                                                                            \
		decltype(value) temp = value;                                                                                                            \
		state.registered[code].events = static_cast<registeredEvent *>(_MyArrayPush(static_cast<void *>(state.registered[code].events), &temp)); \
	}
// NOTE: could use __auto_type for temp above, but intellisense
// for VSCode flags it as an unknown type. typeof() seems to
// work just fine, though. Both are GNU extensions.

#define MyArrayPop(array, valuePtr) \
	_MyArrayPop(array, valuePtr)

#define MyArrayInsertAt(array, index, value)           \
	{                                                  \
		typeof(value) temp = value;                    \
		array = _MyArrayInsertAt(array, index, &temp); \
	}

#define MyArrayPopAt(array, index, valuePtr) \
	_MyArrayPopAt(array, index, valuePtr)

#define MyArrayClear(array) \
	_MyArrayFieldSet(array, MYARRAY_LENGTH, 0)

#define MyArrayCapacity(array) \
	_MyArrayFieldGet(array, MYARRAY_CAPACITY)

#define MyArrayLength(array) \
	_MyArrayFieldGet(array, MYARRAY_LENGTH)

#define MyArrayStride(array) \
	_MyArrayFieldGet(array, MYARRAY_STRIDE)

#define MyArrayLengthSet(array, value) \
	_MyArrayFieldSet(array, MYARRAY_LENGTH, value)

#endif
