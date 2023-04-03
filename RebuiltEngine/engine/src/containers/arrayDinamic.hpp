/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  arrayDinamic.hpp        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#ifndef ARRAYDINAMIC_HPP
# define ARRAYDINAMIC_HPP

# include <defines.hpp>
#include <containers/arrayDinamic.hpp>
#include <core/deMemory.hpp>
# include <core/logger.hpp>

/*
Memory layout
uint64 capacity = number elements that can be held
uint64 length = number of elements currently contained
uint64 stride = size of each element in bytes
void* elements
*/

#define DE_ARRAY_DIN_DEFAULT_CAPACITY 1
#define DE_ARRAY_DIN_RESIZE_FACTOR 2

#define ArrayDinClear(array) \
	_ArrayDinFieldSet(array, DARRAY_LENGTH, 0)

#define ArrayDinCapacity(array) \
	_ArrayDinFieldGet(array, DARRAY_CAPACITY)

#define ArrayDinLength(array) \
	_ArrayDinFieldGet(array, DARRAY_LENGTH)

#define ArrayDinStride(array) \
	_ArrayDinFieldGet(array, DARRAY_STRIDE)

#define ArrayDinLengthSet(array, value) \
	_ArrayDinFieldSet(array, DARRAY_LENGTH, value)

enum {
	DARRAY_CAPACITY,
	DARRAY_LENGTH,
	DARRAY_STRIDE,
	DARRAY_FIELD_LENGTH
};

template<typename T, typename U>
DE_API void		*ArrayDinCreate(T length, U stride)
{
	uint64 header_size = DARRAY_FIELD_LENGTH * sizeof(uint64);
	uint64 array_size = length * stride;
	uint64 *new_array = (uint64 *)Mallocate(header_size + array_size, DE_MEMORY_TAG_MYARRAY);
	SetMemory(new_array, 0, header_size + array_size);
	new_array[DARRAY_CAPACITY] = length;
	new_array[DARRAY_LENGTH] = 0;
	new_array[DARRAY_STRIDE] = stride;
	return (void *)(new_array + DARRAY_FIELD_LENGTH);
};

template<typename T>
DE_API void		ArrayDinDestroy(T *array)
{
	uint64 *header = (uint64 *)array - DARRAY_FIELD_LENGTH;
	uint64 header_size = DARRAY_FIELD_LENGTH * sizeof(uint64);
	uint64 total_size = header_size + header[DARRAY_CAPACITY] * header[DARRAY_STRIDE];
	FreeMem(header, total_size, DE_MEMORY_TAG_MYARRAY);
};

template<typename T>
DE_API uint64	_ArrayDinFieldGet(T *array, uint64 field)
{
	uint64 *header = (uint64 *)array - DARRAY_FIELD_LENGTH;
	return header[field];
};

template<typename T>
DE_API void		_ArrayDinFieldSet(T *array, uint64 field, uint64 value)
{
	uint64 *header = (uint64 *)array - DARRAY_FIELD_LENGTH;
	header[field] = value;
};

template<typename T>
DE_API T		*_darray_resize(T *array)
{
	uint64 length = ArrayDinLength(array);
	uint64 stride = ArrayDinStride(array);
	void *temp = ArrayDinCreate(
		(DE_ARRAY_DIN_RESIZE_FACTOR * ArrayDinCapacity(array)),
		stride);

	CopyMemory(temp, array, length * stride);

	_ArrayDinFieldSet(temp, DARRAY_LENGTH, length);
	ArrayDinDestroy(array);

	return temp;
};

template<typename T, typename U>
DE_API T		*_ArrayDinPush(T *array, const U *valuePtr)
{
	uint64 length = ArrayDinLength(array);
	uint64 stride = ArrayDinStride(array);
	if (length >= ArrayDinCapacity(array))
	{
		array = _darray_resize(array);
	}

	uint64 addr = (uint64)array;
	addr += (length * stride);
	CopyMemory((void *)addr, valuePtr, stride);
	_ArrayDinFieldSet(array, DARRAY_LENGTH, length + 1);

	return array;
};

template<typename T>
DE_API void		_ArrayDinPop(T *array, T *dest)
{
	uint64 length = ArrayDinLength(array);
	uint64 stride = ArrayDinStride(array);
	uint64 addr = (uint64)array;

	addr += ((length - 1) * stride);

	CopyMemory(dest, (void *)addr, stride);
	_ArrayDinFieldSet(array, DARRAY_LENGTH, length - 1);
};

template<typename T>
DE_API T		*_ArrayDinPopAt(T *array, uint64 index, T *dest)
{
	uint64 length = ArrayDinLength(array);
	uint64 stride = ArrayDinStride(array);
	if (index >= length)
	{
		DE_ERROR("Index outside the bounds of this array! Length: %i, index: %index", length, index);
		return array;
	}

	uint64 addr = (uint64)array;
	CopyMemory(dest, (void *)(addr + (index * stride)), stride);

	// If not on the last element, snip out the entry and copy the rest inward.
	if (index != length - 1)
	{
		CopyMemory(
			(void *)(addr + (index * stride)),
			(void *)(addr + ((index + 1) * stride)),
			stride * (length - index));
	}

	_ArrayDinFieldSet(array, DARRAY_LENGTH, length - 1);
	return array;
};

template<typename T, typename U>
DE_API T	*_ArrayDinInsertAt(T *array, uint64 index, U *valuePtr)
{
	uint64 length = ArrayDinLength(array);
	uint64 stride = ArrayDinStride(array);
	if (index >= length)
	{
		DE_ERROR("Index outside the bounds of this array! Length: %i, index: %index", length, index);
		return array;
	}
	if (length >= ArrayDinCapacity(array))
	{
		array = _darray_resize(array);
	}

	uint64 addr = (uint64)array;

	// If not on the last element, copy the rest outward.
	if (index != length - 1)
	{
		CopyMemory(
			(void *)(addr + ((index + 1) * stride)),
			(void *)(addr + (index * stride)),
			stride * (length - index));
	}

	// Set the value at the index
	CopyMemory((void *)(addr + (index * stride)), valuePtr, stride);

	_ArrayDinFieldSet(array, DARRAY_LENGTH, length + 1);
	return array;
};

// #define ArrayDinCreate(type) \
// 	_ArrayDinCreate(DE_ARRAY_DIN_DEFAULT_CAPACITY, sizeof(type))

#define ArrayDinReserve(type, capacity) \
	ArrayDinCreate(capacity, sizeof(type))

// #define ArrayDinDestroy(array) _ArrayDinDestroy(array);

#define ArrayDinPush(array, value)																\
	{																							\
		decltype(value) temp = value;															\
		array = static_cast<const char **>(_ArrayDinPush(static_cast<void *>(array), &temp));	\
	}

// #define ArrayDinPushEvent(array, value)                                                           \
// 	{                                                                                             \
// 		decltype(value) temp = value;                                                             \
// 		array = static_cast<registeredEvent *>(_ArrayDinPush(static_cast<void *>(array), &temp)); \
// 	}
// NOTE: could use __auto_type for temp above, but intellisense
// for VSCode flags it as an unknown type. typeof() seems to
// work just fine, though. Both are GNU extensions.

// #define ArrayDinPop(array, valuePtr) \
// 	_ArrayDinPop(array, valuePtr)

// #define ArrayDinInsertAt(array, index, value)           \
// 	{                                                   \
// 		typeof(value) temp = value;                     \
// 		array = _ArrayDinInsertAt(array, index, &temp); \
// 	}

// #define ArrayDinPopAt(array, index, valuePtr) \
// 	_ArrayDinPopAt(array, index, valuePtr)



#endif
	