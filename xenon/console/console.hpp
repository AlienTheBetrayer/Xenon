// console.hpp
//
// Xenon's Module that can do graphics in console, such as colors and more. Windows-only.

#ifndef XENON_HG_CONSOLE_MODULE
#define XENON_HG_CONSOLE_MODULE

// Xenon's Macros
#include "../macros.hpp"

#ifdef XENON_M_WIN

// Windows library
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>

// Linking Windows' .lib files
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Kernel32.lib")

// Other libraries
#include <string>
#include <unordered_map>
#include <cstdio>

// Xenon's Modules
#include "../utilities/utilities.hpp"

namespace xenon {
    namespace console {
#pragma region Fundamental_get_functions
        /**
         * @brief Gets the std handle of the console.
         * @note 
         * @param  type: The type of the std handle
         * @retval The handle
         */
        [[nodiscard]] HANDLE get_handle(const DWORD type = STD_OUTPUT_HANDLE) noexcept {
            const HANDLE handle = GetStdHandle(type);
            return handle;
        }

        /**
         * @brief Gets the console's window.
         * @note 
         * @retval The window
         */
        [[nodiscard]] HWND get_window(void) noexcept {
            const HWND window = GetConsoleWindow();
            return window;
        }
#pragma endregion Fundamental_get_functions

#pragma region Get_consoles_property_functions
        /**
         * @brief Gets the console's buffer size. 
         * @note 
         * @retval Buffer size vector
         */
        [[nodiscard]] xenon::utilities::Vector2<uint32_t> get_buffer_size(void) noexcept {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(get_handle(), &csbi);
            return xenon::utilities::Vector2<uint32_t>{ static_cast<uint32_t>(csbi.dwSize.X), static_cast<uint32_t>(csbi.dwSize.Y) };
        }

        /**
         * @brief Gets the console window bounds.
         * @note 
         * @retval A console's window bounds 
         */
        [[nodiscard]] xenon::utilities::Rect<uint32_t> get_window_bounds(void) noexcept {
            RECT c_rect;
            GetWindowRect(get_window(), &c_rect);
            return xenon::utilities::Rect<uint32_t>{ static_cast<uint32_t>(c_rect.left), static_cast<uint32_t>(c_rect.right), static_cast<uint32_t>(c_rect.top), static_cast<uint32_t>(c_rect.bottom) };
        }

        /**
         * @brief Gets the console's window size.
         * @note 
         * @retval Window size vector
         */
        [[nodiscard]] xenon::utilities::Vector2<uint32_t> get_window_size(void) noexcept {
            xenon::utilities::Rect<uint32_t> c_rect = get_window_bounds();
            return xenon::utilities::Vector2<uint32_t>{ c_rect.right - c_rect.left, c_rect.bottom - c_rect.top };
        }
#pragma endregion Get_consoles_property_functions

#pragma region Set_consoles_property_functions
        /**
         * @brief Sets the new buffer size for the console.
         * @note 
         * @param size: New size of the console's window buffer
         * @retval None
         */
        void set_buffer_size(const xenon::utilities::Vector2<uint32_t>& size) noexcept {
            COORD buffer = { static_cast<int16_t>(size.x), static_cast<int16_t>(size.y) };
            SetConsoleScreenBufferSize(get_handle(), buffer);
        }

        /**
         * @brief Sets the console's window title to a specified string.
         * @note 
         * @param  new_title: A new title for the console's window 
         * @retval None
         */
        void set_window_title(const std::string& new_title) noexcept {
            SetConsoleTitleA(new_title.c_str());
        }

        /**
         * @brief Gets the console's window title and returns it.
         * @note 
         * @retval Console's window title string.
         */
        [[nodiscard]] std::string get_window_title(void) noexcept {
            char str[128];
            GetConsoleTitleA(str, 128);
            return std::string(str);
        }
#pragma endregion Set_consoles_property_functions

#pragma region Buffer
        /**
         * @brief All the colors that can be used.  
         */
        inline std::unordered_map<std::string, uint32_t> colors = {
            {"black", 0},
			{"dark_blue", 1},
			{"green", 2},
			{"light_blue", 3},
			{"red", 4},
			{"purple", 5},
			{"orange", 6},
			{"light_gray", 7},
			{"dark_gray", 8},
			{"blue", 9},
			{"light_green", 10},
			{"cyan", 11},
			{"light_red", 12},
			{"pink", 13},
			{"yellow", 14},
			{"white", 15}
		};

        /**
         * @brief Goes to specific coordinates.
         * @note
         * @param  axis: Coordinates
         * @retval None
         */
        void axis_goto(const xenon::utilities::Vector2<int32_t>& axis) noexcept {
            SetConsoleCursorPosition(get_handle(), { static_cast<int16_t>(axis.x), static_cast<int16_t>(axis.y) });
        }

        /**
         * @brief Sets the current color to the specified.
         * @note   
         * @param  color: Color
         * @retval None
         */
        void set_color(const uint32_t color) noexcept {
            SetConsoleTextAttribute(get_handle(), static_cast<uint16_t>(color));
        }

        /**
         * @brief  Sets the current color to the specified.
         * @note   
         * @param  color: Color
         * @retval None
         */
        void set_color(const std::string& color) noexcept {
            set_color(colors[color]);
        }

        /**
         * @brief Sets the current color to the specified and prints out text.
         * @note   
         * @param  text: Text
         * @param  color: Color
         * @retval None
         */
        void color_print(const std::string& text, const uint32_t color) noexcept {
            set_color(color);
            printf(text.c_str());
            set_color("light_gray");
        }

        /**
         * @brief Sets the current color to the specified and prints out text.
         * @note   
         * @param  text: Text
         * @param  color: Color
         * @retval None
         */
        void color_print(const std::string& text, const std::string& color) noexcept {
            color_print(text, colors[color]);
        }

        /**
         * @brief Goes to the specified coordinates and prints out text.
         * @note   
         * @param  text: Text
         * @param  axis: Coordinates
         * @retval None
         */
        void axis_print(const std::string& text, const xenon::utilities::Vector2<int32_t>& axis) noexcept {
            axis_goto(axis);
            printf(text.c_str());
        }

        /**
         * @brief Goes to the specified coordinates, sets current color to the specified and prints out text.
         * @note   
         * @param  text: Text
         * @param  color: Color
         * @param  axis: Coordinates
         * @retval None
         */
        void axis_color_print(const std::string& text, const uint32_t color, const xenon::utilities::Vector2<int32_t>& axis) noexcept {
            axis_goto(axis);
            color_print(text, color);
        }

        /**
         * @brief Goes to the specified coordinates, sets current color to the specified and prints out text. 
         * @note   
         * @param  text: 
         * @param  color: 
         * @param  axis: 
         * @retval None
         */
        void axis_color_print(const std::string& text, const std::string& color, const xenon::utilities::Vector2<int32_t>& axis) noexcept {
            axis_color_print(text, colors[color], axis);
        }
#pragma endregion Buffer
    } // namespace console
} // namespace xenon

#endif // XENON_M_WIN
#endif // XENON_HG_CONSOLE_MODULE