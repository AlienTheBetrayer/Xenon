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
    template<typename F, typename... Args>
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
        
    } // namespace time
} // namespace xenon

#endif // XENON_HG_TIME_MODULE