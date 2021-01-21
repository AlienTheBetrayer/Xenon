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
            uint32_t alpha = static_cast<uint32_t>(floor(255 / 100) * percentage);
	        SetLayeredWindowAttributes(window, 0, alpha, LWA_ALPHA);
        }
    } // namespace window
} // namespace xenon

#endif // XENON_HG_WINDOW_MODULE