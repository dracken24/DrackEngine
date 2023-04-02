#include "application.hpp"
#include "game_types.hpp"

#include "logger.hpp"

#include "platform/platform.hpp"
#include "core/kmemory.hpp"
#include "core/event.hpp"
#include "core/input.hpp"
#include "core/time.hpp"

#include "renderer/renderer_frontend.hpp"

typedef struct application_state {
    game* game_inst;
    bl8 is_running;
    bl8 is_suspended;
    platformState platform;
    sint16 width;
    sint16 height;
    Clock clock;
    dbl64 last_time;
} application_state;

static bl8 initialized = false;
static application_state app_state;

// Event handlers
bl8 application_on_event(uint16 code, void* sender, void* listener_inst, event_context context);
bl8 application_on_key(uint16 code, void* sender, void* listener_inst, event_context context);

bl8 application_create(game* game_inst) {
    if (initialized) {
        DE_ERROR("application_create called more than once.");
        return false;
    }

    app_state.game_inst = game_inst;

    // Initialize subsystems.
    LogInit();
    input_initialize();

    // TODO: remove when log message are fully implemented
    DE_FATAL("Hello World! %f", 1.0f);
    DE_ERROR("Hello World! %f", 1.0f);
    DE_WARNING("Hello World! %f", 1.0f);
    DE_INFO("Hello World! %f", 1.0f);
    DE_DEBUG("Hello World! %f", 1.0f);
    DE_TRACE("Hello World! %f lol %s", 1.0f, "test\n");

    app_state.is_running = true;
    app_state.is_suspended = false;

    if(!event_initialize()) {
        DE_ERROR("Event system failed initialization. Application cannot continue.");
        return false;
    }

    event_register(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
    event_register(EVENT_CODE_KEY_PRESSED, 0, application_on_key);
    event_register(EVENT_CODE_KEY_RELEASED, 0, application_on_key);

    if (!platform_startup(
            &app_state.platform,
            game_inst->appConfig.name.c_str(),
            game_inst->appConfig.x,
            game_inst->appConfig.y,
            game_inst->appConfig.width,
            game_inst->appConfig.height)) {
        return false;
    }

    // Renderer startup
    if (!renderer_initialize(game_inst->appConfig.name.c_str(), &app_state.platform)) {
        DE_FATAL("Failed to initialize renderer. Aborting application.");
        return false;
    }

    // Initialize the game.
    if (!app_state.game_inst->initialize(app_state.game_inst)) {
        DE_FATAL("Game failed to initialize.");
        return false;
    }

    app_state.game_inst->onResize(app_state.game_inst, app_state.width, app_state.height);

    initialized = true;

    return true;
}

bl8 application_run() {
    app_state.clock.ClockStart();
    app_state.clock.ClockUpdate();
    app_state.last_time = app_state.clock._clock.elapsedTime;
    dbl64 running_time = 0;
    uint8 framesCount = 0;
    dbl64 target_frame_seconds = 1.0f / 60;

    DE_INFO(get_memory_usage_str().c_str());

    while (app_state.is_running) {
        if (!platform_pump_messages(&app_state.platform)) {
            app_state.is_running = false;
        }

        if (!app_state.is_suspended) {
            // Update clock and get delta time.
            app_state.clock.ClockUpdate();
            dbl64 current_time = app_state.clock._clock.elapsedTime;
            dbl64 delta = (current_time - app_state.last_time);
            dbl64 frame_start_time = platform_get_absolute_time();

            if (!app_state.game_inst->update(app_state.game_inst, (fl32)delta)) {
                DE_FATAL("Game update failed, shutting down.");
                app_state.is_running = false;
                break;
            }

            // Call the game's render routine.
            if (!app_state.game_inst->render(app_state.game_inst, (fl32)delta)) {
                DE_FATAL("Game render failed, shutting down.");
                app_state.is_running = false;
                break;
            }

            // TODO: refactor packet creation
            render_packet packet;
            packet.delta_time = delta;
            renderer_draw_frame(&packet);

            // Figure out how long the frame took and, if below
            dbl64 frame_end_time = platform_get_absolute_time();
            dbl64 frame_elapsed_time = frame_end_time - frame_start_time;
            running_time += frame_elapsed_time;
            dbl64 remaining_seconds = target_frame_seconds - frame_elapsed_time;

            if (remaining_seconds > 0) {
                uint64 remaining_ms = (remaining_seconds * 1000);

                // If there is time left, give it back to the OS.
                // std::cout << "Frame: " << (int)framesCount << std::endl;
                bl8 limit_frames = true;
                if (remaining_ms > 0 && limit_frames) {
                    platform_sleep(remaining_ms - 1);
                }

                framesCount++;
            }

            // NOTE: Input update/state copying should always be handled
            // after any input should be recorded; I.E. before this line.
            // As a safety, input is the last thing to be updated before
            // this frame ends.
            input_update(delta);

            // Update last time
            app_state.last_time = current_time;
        }
    }

    app_state.is_running = false;

    // Shutdown event system.
    event_unregister(EVENT_CODE_APPLICATION_QUIT, 0, application_on_event);
    event_unregister(EVENT_CODE_KEY_PRESSED, 0, application_on_key);
    event_unregister(EVENT_CODE_KEY_RELEASED, 0, application_on_key);
    event_shutdown();
    input_shutdown();

    renderer_shutdown();

    platform_shutdown(&app_state.platform);

    return true;
}

bl8 application_on_event(uint16 code, void* sender, void* listener_inst, event_context context) {
    switch (code) {
        case EVENT_CODE_APPLICATION_QUIT: {
            DE_INFO("EVENT_CODE_APPLICATION_QUIT recieved, shutting down.\n");
            app_state.is_running = false;
            return true;
        }
    }

    return false;
}

bl8 application_on_key(uint16 code, void* sender, void* listener_inst, event_context context) {
    if (code == EVENT_CODE_KEY_PRESSED) {
        uint16 key_code = context.data.uint16[0];
        if (key_code == KEY_ESCAPE) {
            // NOTE: Technically firing an event to itself, but there may be other listeners.
            event_context data = {};
            event_fire(EVENT_CODE_APPLICATION_QUIT, 0, data);

            // Block anything else from processing this.
            return true;
        } else if (key_code == KEY_A) {
            // Example on checking for a key
            DE_DEBUG("Explicit - A key pressed!");
        } else {
            DE_DEBUG("'%c' key pressed in window.", key_code);
        }
    } else if (code == EVENT_CODE_KEY_RELEASED) {
        uint16 key_code = context.data.uint16[0];
        if (key_code == KEY_B) {
            // Example on checking for a key
            DE_DEBUG("Explicit - B key released!");
        } else {
            DE_DEBUG("'%c' key released in window.", key_code);
        }
    }
    return false;
}