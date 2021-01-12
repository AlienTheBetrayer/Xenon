// console.cpp

#include "console.hpp"

/**
 * @brief Gets the std handle of the console.
 * @param  type: The type of the std handle
 * @retval The handle
 */
[[nodiscard]] HANDLE xenon::console::get_handle(const DWORD type = STD_OUTPUT_HANDLE) noexcept {
    const HANDLE handle = GetStdHandle(type);
    return handle;
}

/**
 * @brief Gets the console's window.
 * @retval The window
 */
[[nodiscard]] HWND xenon::console::get_window(void) noexcept {
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

    MoveWindow(window, c_rect.left, c_rect.top, size.x, size.y);
}

/**
 * @brief Gets the console's window size.
 * @retval Window size vector
 */
[[nodiscard]] xenon::utilities::Vector2<uint32_t> xenon::console::get_window_size(void) noexcept {
	Rect c_rect = get_window_bounds();
	return Vector2I{ c_rect.right - c_rect.left, c_rect.bottom - c_rect.top };
}

/**
 * @brief Gets the console's buffer size. 
 * @retval Buffer size vector
 */
[[nodiscard]] xenon::utilities::Vector2<uint32_t> xenon::console::get_buffer_size(void) noexcept {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetHandle(), &csbi);

	return xenon::utilities::Vector2<uint32_t>{ csbi.dwSize.X, csbi.dwSize.Y };
}

/**
 * @brief Gets the console window bounds.
 * @retval A console's window bounds 
 */
[[nodiscard]] xenon::utilities::Rect<uint32_t> xenon::console::get_window_bounds(void) noexcept {
    RECT c_rect;
    GetWindowRect(GetConsole(), &c_rect);

    return xenon::utilities::Rect<uint32_t>{ c_rect.left, c_rect.right, c_rect.top, c_rect.bottom };
}