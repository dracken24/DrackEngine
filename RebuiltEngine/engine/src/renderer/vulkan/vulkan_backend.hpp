#pragma once

#include "renderer/renderer_backend.hpp"

bl8 vulkan_renderer_backend_initialize(renderer_backend* backend, const char* application_name, struct platformState* plat_state);
void vulkan_renderer_backend_shutdown(renderer_backend* backend);

void vulkan_renderer_backend_on_resized(renderer_backend* backend, uint16 width, uint16 height);

bl8 vulkan_renderer_backend_begin_frame(renderer_backend* backend, fl32 delta_time);
bl8 vulkan_renderer_backend_end_frame(renderer_backend* backend, fl32 delta_time);