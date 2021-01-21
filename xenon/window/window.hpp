// window.hpp
//
// Xenon's ...

#ifndef XENON_HG_WINDOW_MODULE
#define XENON_HG_WINDOW_MODULE

// Libraries
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>

// Dependencies
#include "../utilities/utilities.hpp"

namespace xenon {
    namespace window {
        /**
         * @brief Sets the transparency of the window(100 = completely visible)
         * @note   
         * @param  window: The window
         * @param  percentage: The percentage to set the transparency to
         * @retval None
         */
        void set_alpha(const HWND window, const uint32_t percentage) noexcept {
            const uint32_t alpha = static_cast<uint32_t>(floor(255 / 100) * percentage);
	        SetLayeredWindowAttributes(window, 0, alpha, LWA_ALPHA);
        }

        /**
         * @brief Changes the title of the window 
         * @note   
         * @param  window: The window 
         * @param  new_title: New window title
         * @retval None
         */
        void set_title(const HWND window, const std::string& new_title) noexcept {
            SetWindowText(window, new_title.c_str());
        }

        /**
         * @brief Sets the window's bounds 
         * @note   
         * @param  window: The window
         * @param  bounds: The new bounds
         * @retval None
         */
        void set_bounds(const HWND window, const xenon::utilities::Rect<uint32_t>& bounds) noexcept {
            SetWindowPos(window, nullptr, bounds.left, bounds.top, bounds.right - bounds.left, bounds.bottom - bounds.top, SWP_NOZORDER);
        }

        /**
         * @brief Sets the window's size 
         * @note   
         * @param  window: The window
         * @param  size: The new size
         * @retval None
         */
        void set_size(const HWND window, const xenon::utilities::Vector2<uint32_t>& size) noexcept {
            RECT c_rect;
            GetWindowRect(window, &c_rect);
            MoveWindow(window, c_rect.left, c_rect.top, size.x, size.y, TRUE);
        }

        /**
         * @brief Positions the window at the center of your screen
         * @note   
         * @param  window: The window
         * @retval None
         */
        void center(const HWND window) noexcept {
            RECT w_rect, m_rect;
            GetWindowRect(window, &w_rect);
            GetWindowRect(GetDesktopWindow(), &m_rect);
            SetWindowPos(window, nullptr, m_rect.right / 2 - (w_rect.right - w_rect.left) / 2, m_rect.bottom / 2 - (w_rect.bottom - w_rect.top) / 2 , 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        }

        /**
         * @brief Returns true if the cursor is within the bounds of the window, false otherwise.
         * @note   
         * @param  window: The window
         * @retval Whether the cursor is within the bounds of the window 
         */
        [[nodiscard]] bool is_cursor_within_bounds(const HWND window) noexcept {
            RECT w_rect;
            POINT m_point;
            GetWindowRect(window, &w_rect);
            GetCursorPos(&m_point);
            return m_point.x >= w_rect.left && m_point.x <= w_rect.right && m_point.y >= w_rect.top && m_point.y <= w_rect.bottom;
        }

        /**
         * @brief Gets the title of the specified window
         * @note   
         * @param  window: The window
         * @retval The window's title
         */
        [[nodiscard]] std::string get_title(const HWND window) noexcept {
            const uint32_t len = GetWindowTextLengthA(window);
            std::unique_ptr<char> title = std::make_unique<char>(len + 1);
            GetWindowTextA(window, title.get(), len + 1);
            return std::string(title.get());
        }

        // Arguments that you will pass to for_each function
        struct enum_windows_args {
            std::function<void(HWND)> func;
            bool show_only_visible = true;
            bool has_non_empty_title = true;
        };

        // Do not call this
        BOOL __stdcall XENON_HF_enum_windows_callback(const HWND window, const LPARAM param) noexcept {
            const enum_windows_args* args = reinterpret_cast<enum_windows_args*>(param);
            if(args->show_only_visible)
                if(!(IsWindowVisible(window) && IsWindow(window)))
                    return TRUE;
            if(args->has_non_empty_title)
                if(get_title(window).empty())
                    return TRUE;
            args->func(window);
            return TRUE;
        }

        /**
         * @brief Runs your function on all the windows existing. You can customize it with enum_windows_args. 
         * @note   
         * @param  args: The arguments, make sure to pass the func to it!
         * @retval None
         */
        void for_each(const enum_windows_args& args) noexcept {
            EnumWindows(&enum_windows_callback, reinterpret_cast<LPARAM>(&args));
        }

        /**
         * @brief Sets the visibility of the window. 
         * @note   
         * @param  window: The window
         * @param  visibility: Whether or not the window should display
         * @retval None
         */
        void set_visibility(const HWND window, const bool visibility) noexcept {
            ShowWindow(window, visibility ? SW_SHOW : SW_HIDE);
        }

        /**
         * @brief Sets the topmost of the window. 
         * @note   
         * @param  window: The window
         * @param  topmost: Whether or not the window should be topmost
         * @retval None
         */
        void set_topmost(const HWND window, const bool topmost) noexcept {
            SetWindowPos(window, topmost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }
    } // namespace window
} // namespace xenon

#endif // XENON_HG_WINDOW_MODULE