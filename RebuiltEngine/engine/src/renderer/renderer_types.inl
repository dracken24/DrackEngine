#pragma once

#include "defines.hpp"

typedef enum renderer_backend_type {
    RENDERER_BACKEND_TYPE_VULKAN,
    RENDERER_BACKEND_TYPE_OPENGL,
    RENDERER_BACKEND_TYPE_DIRECTX
} renderer_backend_type;

typedef struct renderer_backend {
    struct platformState* plat_state;
    uint64 frame_number;

    bl8 (*initialize)(struct renderer_backend* backend, const char* application_name, struct platformState* plat_state);

    void (*shutdown)(struct renderer_backend* backend);

    void (*resized)(struct renderer_backend* backend, uint16 width, uint16 height);

    bl8 (*begin_frame)(struct renderer_backend* backend, fl32 delta_time);
    bl8 (*end_frame)(struct renderer_backend* backend, fl32 delta_time);    
} renderer_backend;

typedef struct render_packet {
    fl32 delta_time;
} render_packet;