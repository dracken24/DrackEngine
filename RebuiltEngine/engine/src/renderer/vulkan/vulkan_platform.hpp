#pragma once

#include "defines.hpp"

struct platformState;
struct vulkan_context;

bl8 platform_create_vulkan_surface(
    struct platformState* plat_state,
    struct vulkan_context* context);

/**
 * Appends the names of required extensions for this platform to
 * the names_darray, which should be created and passed in.
 */
void platform_get_required_extension_names(const char*** names_darray);