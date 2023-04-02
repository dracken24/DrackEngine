#include "containers/darray.hpp"

#include "core/kmemory.hpp"
#include "core/logger.hpp"

void* _darray_create(uint64 length, uint64 stride) {
    uint64 header_size = DARRAY_FIELD_LENGTH * sizeof(uint64);
    uint64 array_size = length * stride;
    uint64 *new_array = (uint64 *)kallocate(header_size + array_size, DE_MEMORY_TAG_MYARRAY);
    kset_memory(new_array, 0, header_size + array_size);
    new_array[DARRAY_CAPACITY] = length;
    new_array[DARRAY_LENGTH] = 0;
    new_array[DARRAY_STRIDE] = stride;
    return (void*)(new_array + DARRAY_FIELD_LENGTH);
}

void _darray_destroy(void* array) {
    uint64* header = (uint64*)array - DARRAY_FIELD_LENGTH;
    uint64 header_size = DARRAY_FIELD_LENGTH * sizeof(uint64);
    uint64 total_size = header_size + header[DARRAY_CAPACITY] * header[DARRAY_STRIDE];
    kfree(header, total_size, DE_MEMORY_TAG_MYARRAY);
}

uint64 _darray_field_get(void* array, uint64 field) {
    uint64* header = (uint64*)array - DARRAY_FIELD_LENGTH;
    return header[field];
}

void _darray_field_set(void* array, uint64 field, uint64 value) {
    uint64* header = (uint64*)array - DARRAY_FIELD_LENGTH;
    header[field] = value;
}

void* _darray_resize(void* array) {
    uint64 length = darray_length(array);
    uint64 stride = darray_stride(array);
    void* temp = _darray_create(
        (DARRAY_RESIZE_FACTOR * darray_capacity(array)),
        stride);
    kcopy_memory(temp, array, length * stride);

    _darray_field_set(temp, DARRAY_LENGTH, length);
    _darray_destroy(array);
    return temp;
}

void* _darray_push(void* array, const void* value_ptr) {
    uint64 length = darray_length(array);
    uint64 stride = darray_stride(array);
    if (length >= darray_capacity(array)) {
        array = _darray_resize(array);
    }

    uint64 addr = (uint64)array;
    addr += (length * stride);
    kcopy_memory((void*)addr, value_ptr, stride);
    _darray_field_set(array, DARRAY_LENGTH, length + 1);
    return array;
}

void _darray_pop(void* array, void* dest) {
    uint64 length = darray_length(array);
    uint64 stride = darray_stride(array);
    uint64 addr = (uint64)array;
    addr += ((length - 1) * stride);
    kcopy_memory(dest, (void*)addr, stride);
    _darray_field_set(array, DARRAY_LENGTH, length - 1);
}

void* _darray_pop_at(void* array, uint64 index, void* dest) {
    uint64 length = darray_length(array);
    uint64 stride = darray_stride(array);
    if (index >= length) {
        DE_ERROR("Index outside the bounds of this array! Length: %i, index: %index", length, index);
        return array;
    }

    uint64 addr = (uint64)array;
    kcopy_memory(dest, (void*)(addr + (index * stride)), stride);

    // If not on the last element, snip out the entry and copy the rest inward.
    if (index != length - 1) {
        kcopy_memory(
            (void*)(addr + (index * stride)),
            (void*)(addr + ((index + 1) * stride)),
            stride * (length - index));
    }

    _darray_field_set(array, DARRAY_LENGTH, length - 1);
    return array;
}

void* _darray_insert_at(void* array, uint64 index, void* value_ptr) {
    uint64 length = darray_length(array);
    uint64 stride = darray_stride(array);
    if (index >= length) {
        DE_ERROR("Index outside the bounds of this array! Length: %i, index: %index", length, index);
        return array;
    }
    if (length >= darray_capacity(array)) {
        array = _darray_resize(array);
    }

    uint64 addr = (uint64)array;

    // If not on the last element, copy the rest outward.
    if (index != length - 1) {
        kcopy_memory(
            (void*)(addr + ((index + 1) * stride)),
            (void*)(addr + (index * stride)),
            stride * (length - index));
    }

    // Set the value at the index
    kcopy_memory((void*)(addr + (index * stride)), value_ptr, stride);

    _darray_field_set(array, DARRAY_LENGTH, length + 1);
    return array;
}