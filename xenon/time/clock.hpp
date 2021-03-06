// clock.hpp
//
// A clock class that is a part of a Time module.

#ifndef XENON_HG_TIME_CLOCK
#define XENON_HG_TIME_CLOCK

#include <chrono>

namespace xenon {
    namespace time {
        /**
         * @brief All the time order types that you can use in clock class.  
         * @note   
         */
        enum class time_order {
            // Seconds
            s, 
            // Milliseconds
            ms,
            // Microseconds
            us,
            // Nanoseconds
            ns
		};

        /**
         * @brief A type for all the time points that will be used.
         * @note
         */  
        using timepoint_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

        /**
         * @brief A clock class that is used to measure time. Starts when constructed.  
         * @note   
         */
        class clock final {
        public:
            /**
             * @brief Constructs the clock class and starts the timer.
             * @note   
             */
            clock(void) noexcept {
                m_start = std::chrono::high_resolution_clock::now();
            }

            /**
             * @brief A default destructor.  
             * @note 
             */
            ~clock(void) noexcept = default;

            /**
             * @brief Ends the clock. 
             * @note   
             * @retval None
             */
            void stop(void) noexcept {
                m_end = std::chrono::high_resolution_clock::now();
            }

            /**
             * @brief Gets the duration of the clock
             * @note   
             * @param  time_order_: Time order(second, nanosecond, etc) 
             * @retval Duration in the specified time order
             */
            [[nodiscard]] double get(const time_order time_order_ = time_order::s) noexcept {
                return std::chrono::duration<double>(m_end - m_start).count() * (time_order_ == time_order::s ? 1 : pow(10, static_cast<int32_t>(time_order_) * 3));
            }
        private:
            timepoint_t m_start;
            timepoint_t m_end;
        };
    } // namespace time
} // namespace xenon

#endif // XENON_HG_TIME_CLOCK