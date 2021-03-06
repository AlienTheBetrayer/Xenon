// vector2.hpp
//
// A simple Vector2 class that is a part of Utilities Module.

#ifndef XENON_HG_UTILITIES_VECTOR2
#define XENON_HG_UTILITIES_VECTOR2

// Xenon's Modules
#include "../concepts/concepts.hpp"

namespace xenon {
    namespace utilities {
        /**
         * @brief A simple Vector2 class with operator overloads.  
         */
        template<typename T>
            requires xenon::concepts::arithmetic<T>
        struct Vector2 {
            T x;
            T y;

            /**
             * @brief Compares two vectors.
             * @note 
             * @param vec: Another vector 
             */
            [[nodiscard]] auto operator<=>(const Vector2& vec) const noexcept = default;

            /**
             * @brief Adds two vectors together.
             * @note 
             * @param vec: Another vector
             * @retval New vector
             */
            [[nodiscard]] Vector2 operator+(const Vector2& vec) noexcept {
                return Vector2{ x + vec.x, y + vec.y };
            }

            /**
             * @brief Subtracts two vectors.
             * @note 
             * @param vec: Another vector
             * @retval New vector
             */
            [[nodiscard]] Vector2 operator-(const Vector2& vec) noexcept {
                return Vector2{ x - vec.x, y - vec.y };
            }

             /**
             * @brief Multiplies two vectors together.
             * @note 
             * @param vec: Another vector
             * @retval New vector
             */
            [[nodiscard]] Vector2 operator*(const Vector2& vec) noexcept {
                return Vector2{ x * vec.x, y * vec.y };
            }

            /**
             * @brief Divides two vectors.
             * @note 
             * @param vec: Another vector
             * @retval New vector
             */
            [[nodiscard]] Vector2 operator/(const Vector2& vec) noexcept {
                return Vector2{ x / vec.x, y / vec.y };
            }

            friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) noexcept {
                os << "[" << vec.x << "; " << vec.y << "]";
                return os;
            }
        };
    } // namespace utilities
} // namespace xenon

#endif // XENON_HG_UTILITIES_VECTOR2