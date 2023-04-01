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

#include "myArray.hpp"

#include "core/deMemory.hpp"
#include "core/logger.hpp"

void	*_MyArrayCreate(uint64 length, uint64 stride)
{
	uint64 headerSize = MYARRAY_LENGTH * sizeof(uint64);
	uint64 array_size = length * stride;
	uint64 *new_array = (uint64 *)DE_Malloc(headerSize + array_size, DE_MEMORY_TAG_MYARRAY);

	DE_SetMemory(new_array, 0, headerSize + array_size);
	new_array[MYARRAY_CAPACITY] = length;
	new_array[MYARRAY_LENGTH] = 0;
	new_array[MYARRAY_STRIDE] = stride;

	return (void *)(new_array + MYARRAY_FIELD_LENGTH);
}

void	_MyArrayDestroy(void *array)
{
	uint64 *header = (uint64 *)array - MYARRAY_FIELD_LENGTH;
	uint64 headerSize = MYARRAY_FIELD_LENGTH * sizeof(uint64);
	uint64 total_size = headerSize + header[MYARRAY_CAPACITY] * header[MYARRAY_STRIDE];

	DE_Free(header, total_size, DE_MEMORY_TAG_MYARRAY);
}

uint64	_MyArrayFieldGet(void *array, uint64 field)
{
	uint64 *header = (uint64 *)array - MYARRAY_FIELD_LENGTH;
	return header[field];
}

void	_MyArrayFieldSet(void *array, uint64 field, uint64 value)
{
	uint64 *header = (uint64 *)array - MYARRAY_FIELD_LENGTH;
	header[field] = value;
}

void	*_MyArrayResize(void *array)
{
	uint64 length = MyArrayLength(array);
	uint64 stride = MyArrayStride(array);
	void *temp = _MyArrayCreate(
		(MYARRAY_RESIZE_FACTOR * MyArrayCapacity(array)), stride);

	DE_CopyMemory(temp, array, length * stride);

	_MyArrayFieldSet(temp, MYARRAY_LENGTH, length);
	_MyArrayDestroy(array);

	return temp;
}

void	*_MyArrayPush(void *array, const void *value_ptr)
{
	uint64 length = MyArrayLength(array);
	uint64 stride = MyArrayStride(array);

	if (length >= MyArrayCapacity(array))
	{
		array = _MyArrayResize(array);
	}

	uint64 addr = (uint64)array;
	addr += (length * stride);
	DE_CopyMemory((void *)addr, value_ptr, stride);
	_MyArrayFieldSet(array, MYARRAY_LENGTH, length + 1);
	
	return array;
}

void	_MyArrayPop(void *array, void *dest)
{
	uint64 length = MyArrayLength(array);
	uint64 stride = MyArrayStride(array);
	uint64 addr = (uint64)array;

	addr += ((length - 1) * stride);
	DE_CopyMemory(dest, (void *)addr, stride);
	_MyArrayFieldSet(array, MYARRAY_LENGTH, length - 1);
}

void	*_MyArrayPopAt(void *array, uint64 index, void *dest)
{
	uint64 length = MyArrayLength(array);
	uint64 stride = MyArrayStride(array);

	if (index >= length)
	{
		DE_ERROR("Index outside the bounds of this array! Length: %i, index: %index", length, index);
		return array;
	}

	uint64 addr = (uint64)array;
	DE_CopyMemory(dest, (void *)(addr + (index * stride)), stride);

	// If not on the last element, snip out the entry and copy the rest inward.
	if (index != length - 1)
	{
		DE_CopyMemory(
			(void *)(addr + (index * stride)),
			(void *)(addr + ((index + 1) * stride)),
			stride * (length - index));
	}

	_MyArrayFieldSet(array, MYARRAY_LENGTH, length - 1);

	return array;
}

void	*_MyArray_insert_at(void *array, uint64 index, void *valuePtr)
{
	uint64 length = MyArrayLength(array);
	uint64 stride = MyArrayStride(array);
	if (index >= length)
	{
		DE_ERROR("Index outside the bounds of this array! Length: %i, index: %index", length, index);
		return array;
	}
	if (length >= MyArrayCapacity(array))
	{
		array = _MyArrayResize(array);
	}

	uint64 addr = (uint64)array;

	// If not on the last element, copy the rest outward.
	if (index != length - 1)
	{
		DE_CopyMemory(
			(void *)(addr + ((index + 1) * stride)),
			(void *)(addr + (index * stride)),
			stride * (length - index));
	}

	// Set the value at the index
	DE_CopyMemory((void *)(addr + (index * stride)), valuePtr, stride);

	_MyArrayFieldSet(array, MYARRAY_LENGTH, length + 1);

	return array;
}
