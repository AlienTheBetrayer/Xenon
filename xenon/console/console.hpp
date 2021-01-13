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
//#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Kernel32.lib")

// Xenon's Modules
#include "../utilities/utilities.hpp"

namespace xenon {
    namespace console {
        /**
         * @brief Gets the std handle of the console.
         * @param  type: The type of the std handle
         * @retval The handle
         */
        [[nodiscard]] HANDLE get_handle(const DWORD type = STD_OUTPUT_HANDLE) noexcept {
            const HANDLE handle = GetStdHandle(type);
            return handle;
        }

        /**
         * @brief Gets the console's window.
         * @retval The window
         */
        [[nodiscard]] HWND get_window(void) noexcept {
            const HWND window = GetConsoleWindow();
            return window;
        }

        /**
         * @brief Sets the console's window size
         * @param  size: New size
         * @retval None
         */
        void set_window_size(const xenon::utilities::Vector2<uint32_t>& size) noexcept {
            const HWND window = get_window();
            RECT c_rect;
            GetWindowRect(window, &c_rect);
            MoveWindow(window, c_rect.left, c_rect.top, size.x, size.y, TRUE);
        }

        /**
         * @brief Sets the new buffer size for the console.
         * @param size: New size of the console's window buffer
         * @retval None
         */
        void set_buffer_size(const xenon::utilities::Vector2<uint32_t>& size) noexcept {
            COORD buffer = { static_cast<int16_t>(size.x), static_cast<int16_t>(size.y) };
            SetConsoleScreenBufferSize(get_handle(), buffer);
        }

        /**
         * @brief Sets the new window bounds.
         * @param bounds: New bounds of the console's window
         * @retval None
         */
        void set_window_bounds(const xenon::utilities::Rect<uint32_t>& bounds) noexcept {
            SetWindowPos(get_window(), nullptr, bounds.left, bounds.top, bounds.right - bounds.left, bounds.bottom - bounds.top, SWP_NOZORDER);
        }


        /**
         * @brief Gets the console's buffer size. 
         * @retval Buffer size vector
         */
        [[nodiscard]] xenon::utilities::Vector2<uint32_t> get_buffer_size(void) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(get_handle(), &csbi);
            return xenon::utilities::Vector2<uint32_t>{ static_cast<uint32_t>(csbi.dwSize.X), static_cast<uint32_t>(csbi.dwSize.Y) };
        }

        /**
         * @brief Gets the console window bounds.
         * @retval A console's window bounds 
         */
        [[nodiscard]] xenon::utilities::Rect<uint32_t> get_window_bounds(void) noexcept {
            RECT c_rect;
            GetWindowRect(get_window(), &c_rect);
            return xenon::utilities::Rect<uint32_t>{ static_cast<uint32_t>(c_rect.left), static_cast<uint32_t>(c_rect.right), static_cast<uint32_t>(c_rect.top), static_cast<uint32_t>(c_rect.bottom) };
        }

        /**
         * @brief Gets the console's window size.
         * @retval Window size vector
         */
        [[nodiscard]] xenon::utilities::Vector2<uint32_t> get_window_size(void) noexcept {
            xenon::utilities::Rect<uint32_t> c_rect = get_window_bounds();
            return xenon::utilities::Vector2<uint32_t>{ c_rect.right - c_rect.left, c_rect.bottom - c_rect.top };
        }

    } // namespace console
} // namespace xenon

#endif // XENON_M_WIN
#endif // XENON_HG_CONSOLE_MODULE