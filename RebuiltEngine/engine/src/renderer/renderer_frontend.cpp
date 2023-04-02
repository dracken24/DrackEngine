#include "renderer_frontend.hpp"

#include "renderer_backend.hpp"

#include "core/logger.hpp"
#include "core/kmemory.hpp"

struct platformState;

// Backend render context.
static renderer_backend* backend = 0;

bl8 renderer_initialize(const char* application_name, struct platformState* plat_state) {
    backend = (renderer_backend *)kallocate(sizeof(renderer_backend), DE_MEMORY_TAG_RENDERER);

    // TODO: make this configurable.
    renderer_backend_create(RENDERER_BACKEND_TYPE_VULKAN, plat_state, backend);
    backend->frame_number = 0;

    if (!backend->initialize(backend, application_name, plat_state)) {
        DE_FATAL("Renderer backend failed to initialize. Shutting down.");
        return false;
    }

    return true;
}

void renderer_shutdown() {
    backend->shutdown(backend);
    kfree(backend, sizeof(renderer_backend), DE_MEMORY_TAG_RENDERER);
}

bl8 renderer_begin_frame(fl32 delta_time) {
    return backend->begin_frame(backend, delta_time);
}

bl8 renderer_end_frame(fl32 delta_time) {
    bl8 result = backend->end_frame(backend, delta_time);
    backend->frame_number++;
    return result;
}

bl8 renderer_draw_frame(render_packet* packet) {
    // If the begin frame returned successfully, mid-frame operations may continue.
    if (renderer_begin_frame(packet->delta_time)) {

        // End the frame. If this fails, it is likely unrecoverable.
        bl8 result = renderer_end_frame(packet->delta_time);

        if (!result) {
            DE_ERROR("renderer_end_frame failed. Application shutting down...");
            return false;
        }
    }

    return true;
}