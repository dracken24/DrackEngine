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

#ifndef DE_ARRAYDINAMIC_HPP
# define DE_ARRAYDINAMIC_HPP

# include <defines.hpp>
# include <containers/arrayDinamic.hpp>
# include <core/deMemory.hpp>
# include <core/logger.hpp>

/*
Memory layout
uint64 capacity = number elements that can be held
uint64 length = number of elements currently contained
uint64 stride = size of each element in bytes
void* elements
*/

# define DE_ARRAY_DIN_DEFAULT_CAPACITY 1
# define DE_ARRAY_DIN_RESIZE_FACTOR 2

# define DE_ArrayClear(array) _DE_ArrayFieldSet(array, DARRAY_LENGTH, 0)

# define DE_ArrayCapacity(array) _DE_ArrayFieldGet(array, DARRAY_CAPACITY)

# define DE_ArrayLength(array)  _DE_ArrayFieldGet(array, DARRAY_LENGTH)

# define DE_ArrayStride(array)  _DE_ArrayFieldGet(array, DARRAY_STRIDE)

# define DE_ArrayLengthSet(array, value)  _DE_ArrayFieldSet(array, DARRAY_LENGTH, value)

# define DE_ArrayReserve(type, capacity)  DE_ArrayCreate(capacity, sizeof(type))

# define DE_ArrayPush(array, value)                                                            \
	{                                                                                         \
		decltype(value) temp = value;                                                         \
		array = static_cast<const char **>(_DE_ArrayPush(static_cast<void *>(array), &temp)); \
	}

#define DE_ArrayPush2(array, value)                                                         \
	{                                                                                       \
		decltype(value) temp = value;                                                       \
		array = static_cast<testEntry *>(_DE_ArrayPush(static_cast<void *>(array), &temp)); \
	}

enum {
	DARRAY_CAPACITY,
	DARRAY_LENGTH,
	DARRAY_STRIDE,
	DARRAY_FIELD_LENGTH
};

template<typename T, typename U>
DE_API void		*DE_ArrayCreate(T length, U stride)
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
DE_API void		DE_ArrayDestroy(T array)
{
	uint64 *header = (uint64 *)array - DARRAY_FIELD_LENGTH;
	uint64 header_size = DARRAY_FIELD_LENGTH * sizeof(uint64);
	uint64 total_size = header_size + header[DARRAY_CAPACITY] * header[DARRAY_STRIDE];
	
	FreeMem(header, total_size, DE_MEMORY_TAG_MYARRAY);
};

template<typename T>
DE_API uint64	_DE_ArrayFieldGet(T array, uint64 field)
{
	uint64 *header = (uint64 *)array - DARRAY_FIELD_LENGTH;
	
	return header[field];
};

template<typename T>
DE_API void	_DE_ArrayFieldSet(T array, uint64 field, uint64 value)
{
	uint64 *header = (uint64 *)array - DARRAY_FIELD_LENGTH;
	header[field] = value;
};

template<typename T>
DE_API T	DE_ArrayResize(T array)
{
	uint64 length = DE_ArrayLength(array);
	uint64 stride = DE_ArrayStride(array);
	
	T temp = (T)DE_ArrayCreate(
		(DE_ARRAY_DIN_RESIZE_FACTOR * DE_ArrayCapacity(array)),
		stride);

	CopyMemory(temp, array, length * stride);

	_DE_ArrayFieldSet(temp, DARRAY_LENGTH, length);
	DE_ArrayDestroy(array);

	return temp;
};

template<typename T, typename U>
DE_API T	_DE_ArrayPush(T array, const U valuePtr)
{
	uint64 length = DE_ArrayLength(array);
	uint64 stride = DE_ArrayStride(array);

	if (length >= DE_ArrayCapacity(array))
	{
		array = DE_ArrayResize(array);
	}

	uint64 addr = (uint64)array;
	addr += (length * stride);

	CopyMemory((void *)addr, valuePtr, stride);
	_DE_ArrayFieldSet(array, DARRAY_LENGTH, length + 1);

	return array;
};

template<typename T>
DE_API void		DE_ArrayPop(T array, T dest)
{
	uint64 length = DE_ArrayLength(array);
	uint64 stride = DE_ArrayStride(array);
	uint64 addr = (uint64)array;

	addr += ((length - 1) * stride);

	CopyMemory(dest, (void *)addr, stride);
	_DE_ArrayFieldSet(array, DARRAY_LENGTH, length - 1);
};

template<typename T>
DE_API T		DE_ArrayPopAt(T array, uint64 index, T dest)
{
	uint64 length = DE_ArrayLength(array);
	uint64 stride = DE_ArrayStride(array);

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

	_DE_ArrayFieldSet(array, DARRAY_LENGTH, length - 1);
	return array;
};

template<typename T, typename U>
DE_API T	DE_ArrayInsertAt(T array, uint64 index, U valuePtr)
{
	uint64 length = DE_ArrayLength(array);
	uint64 stride = DE_ArrayStride(array);
	if (index >= length)
	{
		DE_ERROR("Index outside the bounds of this array! Length: %i, index: %index", length, index);
		return array;
	}
	if (length >= DE_ArrayCapacity(array))
	{
		array = DE_ArrayResize(array);
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

	_DE_ArrayFieldSet(array, DARRAY_LENGTH, length + 1);
	return array;
};

#endif
	