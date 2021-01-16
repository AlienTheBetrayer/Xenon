// random.hpp
//
// Xenon's Module that is able to generate random numbers and more.

#ifndef XENON_HG_RANDOM_MODULE
#define XENON_HG_RANDOM_MODULE

// Libraries
#include <random>
#include <memory>
#include <string>
#include <sstream>

// Xenon's Dependencies
#include "../concepts/concepts.hpp"

namespace xenon {
    namespace random {
        /**
         * @brief A class that allows you to get random stuff.  
         * @note   
         */
        class random_engine final {
        public:
            random_engine(void) noexcept {
                std::random_device rd;
                gen = std::make_unique<std::mt19937>(rd());
            }

            /**
             * @brief Gets an integral random number in some range.
             * @note   
             * @param  from: Start of the range
             * @param  to: End of the range
             * @retval A random number
             */
            template<typename T>
                requires xenon::concepts::integral<T>
            [[nodiscard]] T get_integral(const T from, const T to) noexcept {
                std::uniform_int_distribution<T> distr(from, to);
                return static_cast<T>(distr(*gen.get()));
            }

            /**
             * @brief Gets a floating random number in some range.
             * @note   
             * @param  from: Start of the range
             * @param  to: End of the range
             * @retval A random number
             */
            template<typename T>
                requires xenon::concepts::floating_point<T>
            [[nodiscard]] T get_floating_point(const T from, const T to) noexcept {
                std::uniform_real_distribution<T> distr(from, to);
                return static_cast<T>(distr(*gen.get()));
            }

            /**
             * @brief Gets a random character out of all printable characters except space.
             * @note   
             * @retval A random character.
             */
            [[nodiscard]] char get_char(void) noexcept {
                return static_cast<char>(get_integral<uint32_t>(33, 126));
            }

            /**
             * @brief Generates a random string with a specified length
             * @note   
             * @param  len: A length of the random string
             * @retval A random string
             */
            [[nodiscard]] std::string get_string(const uint32_t len = 20) noexcept {
                std::string rand_str = "";
                rand_str.reserve(len);
                for(uint32_t i = 0; i < len; ++i)
                    rand_str += get_char();
                return rand_str;
            }

            /**
             * @brief Generates a random boolean.
             * @note   
             * @retval True or false
             */
            [[nodiscard]] bool get_bool(void) noexcept {
                return static_cast<bool>(get_integral(0, 1));
            }

            /**
             * @brief Generates a random UUID.
             * @note   
             * @retval A random UUID
             */
            [[nodiscard]] std::string get_uuid(void) noexcept {
                std::stringstream ss;
                ss << std::hex;

                for (uint32_t i = 0; i < 8; i++)
                    ss << get_integral<int32_t>(0, 15);
                ss << "-";

                for (uint32_t i = 0; i < 4; i++)
                    ss << get_integral<int32_t>(0, 15);
                ss << "-4";

                for (uint32_t i = 0; i < 3; i++)
                    ss << get_integral<int32_t>(0, 15);
                ss << "-";

                ss << get_integral<int32_t>(8, 11);
                for (uint32_t i = 0; i < 3; i++)
                    ss << get_integral<int32_t>(0, 15);
                ss << "-";

                for (uint32_t i = 0; i < 12; i++)
                    ss << get_integral<int32_t>(0, 15);
                return ss.str();
            }
            
            ~random_engine(void) noexcept = default;
        private:
            std::unique_ptr<std::mt19937> gen;
        };
    } // namespace random
} // namespace xenon

#endif // XENON_HG_RANDOM_MODULE