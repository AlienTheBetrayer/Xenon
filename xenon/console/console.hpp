// console.hpp
//
// Xenon's Module that can do graphics in console, such as colors and more. Windows-only.

#ifndef XENON_HG_CONSOLE_MODULE
#define XENON_HG_CONSOLE_MODULE

// Xenon's Macros
#include "../macros.hpp"

#ifdef XENON_M_WIN

// All the libraries
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

// Xenon's Modules
#include "../utilities/utilities.hpp"

namespace xenon {
    namespace console {
        // Get functions
        
        [[nodiscard]] HANDLE get_handle(const DWORD type = STD_OUTPUT_HANDLE) noexcept;
        [[nodiscard]] HWND get_window(void) noexcept; 

        // Get console's properties functions

        [[nodiscard]] xenon::utilities::Vector2<uint32_t> get_window_size(void) noexcept;
        [[nodiscard]] xenon::utilities::Vector2<uint32_t> get_buffer_size(void) noexcept;
        [[nodiscard]] xenon::utilities::Rect<uint32_t> get_window_bounds(void) noexcept;

        // Set console's properties functions
        void set_window_size(const xenon::utilities::Vector2<uint32_t>& size) noexcept;
    } // namespace console
} // namespace xenon

#endif // XENON_M_WIN
#endif // XENON_HG_CONSOLE_MODULE