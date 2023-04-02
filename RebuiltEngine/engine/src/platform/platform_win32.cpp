#include "platform/platform.hpp"

// Windows platform layer.
#if KPLATFORM_WINDOWS

#include "core/logger.h"
#include "core/input.h"
#include "core/event.h"

#include "containers/darray.h"

#include <windows.h>
#include <windowsx.h>  // param input extraction
#include <stdlib.h>

// For surface creation
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include "renderer/vulkan/vulkan_types.inl"

typedef struct internal_state {
    HINSTANCE h_instance;
    HWND hwnd;
    VkSurfaceKHR surface;
} internal_state;

// Clock
static dbl64 clock_frequency;
static LARGE_INTEGER start_time;

LRESULT CALLBACK win32_process_message(HWND hwnd, uint32 msg, WPARAM w_param, LPARAM l_param);

bl8 platform_startup(
    platformState *plat_state,
    const char *application_name,
    sint32 x,
    sint32 y,
    sint32 width,
    sint32 height) {
    plat_state->internal_state = malloc(sizeof(internal_state));
    internal_state *state = (internal_state *)plat_state->internal_state;

    state->h_instance = GetModuleHandleA(0);

    // Setup and register window class.
    HICON icon = LoadIcon(state->h_instance, IDI_APPLICATION);
    WNDCLASSA wc;
    memset(&wc, 0, sizeof(wc));
    wc.style = CS_DBLCLKS;  // Get double-clicks
    wc.lpfnWndProc = win32_process_message;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = state->h_instance;
    wc.hIcon = icon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);  // NULL; // Manage the cursor manually
    wc.hbrBackground = NULL;                   // Transparent
    wc.lpszClassName = "kohi_window_class";

    if (!RegisterClassA(&wc)) {
        MessageBoxA(0, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return false;
    }

    // Create window
    uint32 client_x = x;
    uint32 client_y = y;
    uint32 client_width = width;
    uint32 client_height = height;

    uint32 window_x = client_x;
    uint32 window_y = client_y;
    uint32 window_width = client_width;
    uint32 window_height = client_height;

    uint32 window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
    uint32 window_ex_style = WS_EX_APPWINDOW;

    window_style |= WS_MAXIMIZEBOX;
    window_style |= WS_MINIMIZEBOX;
    window_style |= WS_THICKFRAME;

    // Obtain the size of the border.
    RECT border_rect = {0, 0, 0, 0};
    AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);

    // In this case, the border rectangle is negative.
    window_x += border_rect.left;
    window_y += border_rect.top;

    // Grow by the size of the OS border.
    window_width += border_rect.right - border_rect.left;
    window_height += border_rect.bottom - border_rect.top;

    HWND handle = CreateWindowExA(
        window_ex_style, "kohi_window_class", application_name,
        window_style, window_x, window_y, window_width, window_height,
        0, 0, state->h_instance, 0);

    if (handle == 0) {
        MessageBoxA(NULL, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);

        DE_FATAL("Window creation failed!");
        return false;
    } else {
        state->hwnd = handle;
    }

    // Show the window
    bl32 should_activate = 1;  // TODO: if the window should not accept input, this should be false.
    sint32 show_window_command_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;
    // If initially minimized, use SW_MINIMIZE : SW_SHOWMINNOACTIVE;
    // If initially maximized, use SW_SHOWMAXIMIZED : SW_MAXIMIZE
    ShowWindow(state->hwnd, show_window_command_flags);

    // Clock setup
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    clock_frequency = 1.0 / (dbl64)frequency.QuadPart;
    QueryPerformanceCounter(&start_time);

    return true;
}

void platform_shutdown(platformState *plat_state) {
    // Simply cold-cast to the known type.
    internal_state *state = (internal_state *)plat_state->internal_state;

    if (state->hwnd) {
        DestroyWindow(state->hwnd);
        state->hwnd = 0;
    }
}

bl8 platform_pump_messages(platformState *plat_state) {
    MSG message;
    while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }

    return true;
}

void *platform_allocate(uint64 size, bl8 aligned) {
    return malloc(size);
}

void platform_free(void *block, bl8 aligned) {
    free(block);
}

void *platform_zero_memory(void *block, uint64 size) {
    return memset(block, 0, size);
}

void *platform_copy_memory(void *dest, const void *source, uint64 size) {
    return memcpy(dest, source, size);
}

void *platform_set_memory(void *dest, sint32 value, uint64 size) {
    return memset(dest, value, size);
}

void platform_console_write(const char *message, uint8 colour) {
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    static uint8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);
    OutputDebugStringA(message);
    uint64 length = strlen(message);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, number_written, 0);
}

void platform_console_write_error(const char *message, uint8 colour) {
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
    // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
    static uint8 levels[6] = {64, 4, 6, 2, 1, 8};
    SetConsoleTextAttribute(console_handle, levels[colour]);
    OutputDebugStringA(message);
    uint64 length = strlen(message);
    LPDWORD number_written = 0;
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, number_written, 0);
}

dbl64 platform_get_absolute_time() {
    LARGE_INTEGER now_time;
    QueryPerformanceCounter(&now_time);
    return (dbl64)now_time.QuadPart * clock_frequency;
}

void platform_sleep(uint64 ms) {
    Sleep(ms);
}

void platform_get_required_extension_names(const char ***names_darray) {
    darray_push(*names_darray, &"VK_KHR_win32_surface");
}

// Surface creation for Vulkan
bl8 platform_create_vulkan_surface(platformState *plat_state, vulkan_context *context) {
    // Simply cold-cast to the known type.
    internal_state *state = (internal_state *)plat_state->internal_state;

    VkWin32SurfaceCreateInfoKHR create_info = {VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR};
    create_info.hinstance = state->h_instance;
    create_info.hwnd = state->hwnd;

    VkResult result = vkCreateWin32SurfaceKHR(context->instance, &create_info, context->allocator, &state->surface);
    if (result != VK_SUCCESS) {
        DE_FATAL("Vulkan surface creation failed.");
        return false;
    }

    context->surface = state->surface;
    return true;
}

LRESULT CALLBACK win32_process_message(HWND hwnd, uint32 msg, WPARAM w_param, LPARAM l_param) {
    switch (msg) {
        case WM_ERASEBKGND:
            // Notify the OS that erasing will be handled by the application to prevent flicker.
            return 1;
        case WM_CLOSE:
            // TODO: Fire an event for the application to quit.
            event_context data = {};
            event_fire(EVENT_CODE_APPLICATION_QUIT, 0, data);
            return true;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_SIZE: {
            // Get the updated size.
            // RECT r;
            // GetClientRect(hwnd, &r);
            // uint32 width = r.right - r.left;
            // uint32 height = r.bottom - r.top;

            // TODO: Fire an event for window resize.
        } break;
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP: {
            // Key pressed/released
            bl8 pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
            keys key = (uint16)w_param;

            // Pass to the input subsystem for processing.
            input_process_key(key, pressed);
        } break;
        case WM_MOUSEMOVE: {
            // Mouse move
            sint32 x_position = GET_X_LPARAM(l_param);
            sint32 y_position = GET_Y_LPARAM(l_param);
            
            // Pass over to the input subsystem.
            input_process_mouse_move(x_position, y_position);
        } break;
        case WM_MOUSEWHEEL: {
            sint32 z_delta = GET_WHEEL_DELTA_WPARAM(w_param);
            if (z_delta != 0) {
                // Flatten the input to an OS-independent (-1, 1)
                z_delta = (z_delta < 0) ? -1 : 1;
                input_process_mouse_wheel(z_delta);
            }
        } break;
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP: {
            bl8 pressed = msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN;
            buttons mouse_button = BUTTON_MAX_BUTTONS;
            switch (msg) {
                case WM_LBUTTONDOWN:
                case WM_LBUTTONUP:
                    mouse_button = BUTTON_LEFT;
                    break;
                case WM_MBUTTONDOWN:
                case WM_MBUTTONUP:
                    mouse_button = BUTTON_MIDDLE;
                    break;
                case WM_RBUTTONDOWN:
                case WM_RBUTTONUP:
                    mouse_button = BUTTON_RIGHT;
                    break;
            }

            // Pass over to the input subsystem.
            if (mouse_button != BUTTON_MAX_BUTTONS) {
                input_process_button(mouse_button, pressed);
            }
        } break;
    }

    return DefWindowProcA(hwnd, msg, w_param, l_param);
}

#endif  // KPLATFORM_WINDOWS
