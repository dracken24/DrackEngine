/*****************************************************************************/
/*\|/~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~\|/*/
/* |             ---------------------------------------------             | */
/* |             *--*  PROJET: DrackEngine PAR: Dracken24 *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  DATE:		 31-03-2023  		  *--*             | */
/* |             ---------------------------------------------             | */
/* |             *--*  FILE: 	  arrayDinamic.cpp        *--*             | */
/* |             ---------------------------------------------             | */
/*/|\~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~/|\*/
/*****************************************************************************/

#include <containers/arrayDinamic.hpp>

#include <core/deMemory.hpp>
#include <core/logger.hpp>

// void* _ArrayDinCreate(uint64 length, uint64 stride)
// {
//     uint64 header_size = DARRAY_FIELD_LENGTH * sizeof(uint64);
//     uint64 array_size = length * stride;
//     uint64 *new_array = (uint64 *)Mallocate(header_size + array_size, DE_MEMORY_TAG_MYARRAY);
//     SetMemory(new_array, 0, header_size + array_size);
//     new_array[DARRAY_CAPACITY] = length;
//     new_array[DARRAY_LENGTH] = 0;
//     new_array[DARRAY_STRIDE] = stride;
//     return (void*)(new_array + DARRAY_FIELD_LENGTH);
// }



// void _ArrayDinDestroy(void* array)
// {
//     uint64* header = (uint64*)array - DARRAY_FIELD_LENGTH;
//     uint64 header_size = DARRAY_FIELD_LENGTH * sizeof(uint64);
//     uint64 total_size = header_size + header[DARRAY_CAPACITY] * header[DARRAY_STRIDE];
//     FreeMem(header, total_size, DE_MEMORY_TAG_MYARRAY);
// }


uint64 _ArrayDinFieldGet(void* array, uint64 field)
{
    uint64* header = (uint64*)array - DARRAY_FIELD_LENGTH;
    return header[field];
}

void _ArrayDinFieldSet(void* array, uint64 field, uint64 value)
{
    uint64* header = (uint64*)array - DARRAY_FIELD_LENGTH;
    header[field] = value;
}

void* _darray_resize(void* array)
{
    uint64 length = ArrayDinLength(array);
    uint64 stride = ArrayDinStride(array);
    void* temp = ArrayDinCreate(
        (DE_ARRAY_DIN_RESIZE_FACTOR * ArrayDinCapacity(array)),
        stride);
    CopyMemory(temp, array, length * stride);

    _ArrayDinFieldSet(temp, DARRAY_LENGTH, length);
    ArrayDinDestroy(array);
    return temp;
}

void* _ArrayDinPush(void* array, const void* valuePtr)
{
    uint64 length = ArrayDinLength(array);
    uint64 stride = ArrayDinStride(array);
    if (length >= ArrayDinCapacity(array))
    {
        array = _darray_resize(array);
    }

    uint64 addr = (uint64)array;
    addr += (length * stride);
    CopyMemory((void*)addr, valuePtr, stride);
    _ArrayDinFieldSet(array, DARRAY_LENGTH, length + 1);

    return array;
}

void _ArrayDinPop(void* array, void* dest)
{
    uint64 length = ArrayDinLength(array);
    uint64 stride = ArrayDinStride(array);
    uint64 addr = (uint64)array;
    addr += ((length - 1) * stride);
    CopyMemory(dest, (void*)addr, stride);
    _ArrayDinFieldSet(array, DARRAY_LENGTH, length - 1);
}

void* _ArrayDinPopAt(void* array, uint64 index, void* dest)
{
    uint64 length = ArrayDinLength(array);
    uint64 stride = ArrayDinStride(array);
    if (index >= length) {
        DE_ERROR("Index outside the bounds of this array! Length: %i, index: %index", length, index);
        return array;
    }

    uint64 addr = (uint64)array;
    CopyMemory(dest, (void*)(addr + (index * stride)), stride);

    // If not on the last element, snip out the entry and copy the rest inward.
    if (index != length - 1) {
        CopyMemory(
            (void*)(addr + (index * stride)),
            (void*)(addr + ((index + 1) * stride)),
            stride * (length - index));
    }

    _ArrayDinFieldSet(array, DARRAY_LENGTH, length - 1);
    return array;
}

void* _ArrayDinInsertAt(void* array, uint64 index, void* valuePtr)
{
    uint64 length = ArrayDinLength(array);
    uint64 stride = ArrayDinStride(array);
    if (index >= length) {
        DE_ERROR("Index outside the bounds of this array! Length: %i, index: %index", length, index);
        return array;
    }
    if (length >= ArrayDinCapacity(array)) {
        array = _darray_resize(array);
    }

    uint64 addr = (uint64)array;

    // If not on the last element, copy the rest outward.
    if (index != length - 1) {
        CopyMemory(
            (void*)(addr + ((index + 1) * stride)),
            (void*)(addr + (index * stride)),
            stride * (length - index));
    }

    // Set the value at the index
    CopyMemory((void*)(addr + (index * stride)), valuePtr, stride);

    _ArrayDinFieldSet(array, DARRAY_LENGTH, length + 1);
    return array;
}
