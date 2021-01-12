// Vector4.hpp
//
// A simple Vector4 class that is a part of Utilities Module.

#ifndef XENON_HG_UTILITIES_VECTOR4
#define XENON_HG_UTILITIES_VECTOR4

// Xenon's Modules
#include "../concepts/concepts.hpp"

namespace xenon {
    namespace utilities {
        /**
         * @brief A simple Vector4 class with operator overloads.  
         */
        template<typename T>
            requires xenon::concepts::arithmetic<T>
        struct Vector4 {
            T x;
            T y;
            T z;
            T w;

            /**
             * @brief Compares two vectors.
             * @param vec: Another vector 
             */
            [[nodiscard]] auto operator<=>(const Vector4& vec) const noexcept = default;

            /**
             * @brief Adds two vectors together.
             * @param vec: Another vector
             * @retval New vector
             */
            [[nodiscard]] Vector4 operator+(const Vector4& vec) noexcept {
                return Vector4{ x + vec.x, y + vec.y, z + vec.z, w + vec.w };
            }

            /**
             * @brief Subtracts two vectors.
             * @param vec: Another vector
             * @retval New vector
             */
            [[nodiscard]] Vector4 operator-(const Vector4& vec) noexcept {
                return Vector4{ x - vec.x, y - vec.y, z - vec.z, w - vec.w };
            }

             /**
             * @brief Multiplies two vectors together.
             * @param vec: Another vector
             * @retval New vector
             */
            [[nodiscard]] Vector4 operator*(const Vector4& vec) noexcept {
                return Vector4{ x * vec.x, y * vec.y, z * vec.z, w * vec.w };
            }

            /**
             * @brief Divides two vectors.
             * @param vec: Another vector
             * @retval New vector
             */
            [[nodiscard]] Vector4 operator/(const Vector4& vec) noexcept {
                return Vector4{ x / vec.x, y / vec.y, z / vec.z, w / vec.w };
            }

            friend std::ostream& operator<<(std::ostream& os, const Vector4& vec) noexcept {
                os << "[" << vec.x << "; " << vec.y << "; " << vec.z << "; " << vec.w << "]";
                return os;
            }
        };
    } // namespace utilities
} // namespace xenon

#endif // XENON_HG_UTILITIES_VECTOR4