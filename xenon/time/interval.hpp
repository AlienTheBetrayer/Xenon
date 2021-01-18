// interval.hpp
//
// An interval class that is a part of a Time module.

#ifndef XENON_HG_TIME_INTERVAL
#define XENON_HG_TIME_INTERVAL

// Dependencies
#include "../async/async.hpp"

namespace xenon {
    namespace time {
        /**
         * @brief An interval class that will be used in a time module  
         * @note   
         */
        template<typename F, typename... Args>
            requires xenon::concepts::callable<F, Args...>
        class interval {
        public:
            /**
             * @brief Constructs the interval class.  
             * @note   
             * @param  func: The functon
             * @param  timeout: The timeout
             * @param  async: Whether it is asynchronous or not 
             * @param  args: Args
             */
            explicit interval(F&& func, const uint32_t timeout, const bool async, Args&&... args) noexcept
                : m_func(std::forward<F>(func)), m_timeout(timeout), m_async(async) {
                const auto function = [&]() {
                    for(;;) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(m_timeout));
                        if(m_running == 1)
                            m_func(std::forward<Args>(args)...);
                        else
                            break;
                    }
                };
                m_async ? xenon::async::run<void>(function, std::forward<Args>(args)...) : function(std::forward<Args>(args)...);
            }

            /**
             * @brief A default destructor.  
             * @note   
             */
            ~interval(void) noexcept = default;

            /**
             * @brief Pauses the interval class
             * @note   
             * @retval None
             */
            void pause(void) noexcept {
                m_running = 0;
            }

            /**
             * @brief Resumes the interval class
             * @note   
             * @retval None
             */
            void resume(void) noexcept {
                m_running = 1;
            }

            /**
             * @brief Stops the interval class
             * @note   
             * @retval None
             */
            void stop(void) noexcept {
                m_running = -1;
            }
        private:
            int32_t m_running = 1;
            uint32_t m_timeout = 1000;
            F m_func;
            bool m_async;
        };
    } // namespace time
} // namespace xenon

#endif // XENON_HG_TIME_INTERVAL