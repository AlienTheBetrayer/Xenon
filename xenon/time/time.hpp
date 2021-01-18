// time.hpp
//
// Xenon's Module that is able to work with time.

#ifndef XENON_HG_TIME_MODULE
#define XENON_HG_TIME_MODULE

// Libraries
#include <functional>

// Other parts of the Time component
#include "clock.hpp"

// Dependencies
#include "../async/async.hpp"

namespace {
    // -- Helper functions. Should not be used by the user. -- \\ 

    template<typename F, typename... Args>
        requires xenon::concepts::callable<F, Args...>
    inline void XENON_HF_set_timeout(F&& func, const uint32_t delay_ms, const bool async, Args&&... args) noexcept {
        const auto function = [&func, delay_ms]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
            func(std::forward<Args>(args)...);
        };
        async ? xenon::async::run<void>(function) : function();
    }
}

namespace xenon {
    namespace time {
        /**
         * @brief Waits the timeout and then runs the function(asynchronously). 
         * @note   
         * @param  func: The function
         * @param  timeout: After how many milliseconds to run the function
         * @param  args: Args
         * @retval None
         */
        template<typename F, typename... Args>
        inline void set_async_timeout(F&& func, const uint32_t timeout, Args&&... args) noexcept {
            XENON_HF_set_timeout(func, timeout, true, std::forward<Args>(args)...);
        }

        /**
         * @brief Waits the timeout and then runs the function(synchronously). 
         * @note   
         * @param  func: The function
         * @param  timeout: After how many milliseconds to run the function
         * @param  args: Args
         * @retval None
         */
        template<typename F, typename... Args>
        inline void set_sync_timeout(F&& func, const uint32_t timeout, Args&&... args) noexcept {
            XENON_HF_set_timeout(func, timeout, false, std::forward<Args>(args)...);
        }
    } // namespace time
} // namespace xenon

#endif // XENON_HG_TIME_MODULE