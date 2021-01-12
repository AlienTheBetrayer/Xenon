// vector3.hpp
//
// A simple Vector3 class that is a part of Utilities Module.

#ifndef XENON_HG_UTILITIES_VECTOR3
#define XENON_HG_UTILITIES_VECTOR3

// Xenon's Modules
#include "../concepts/concepts.hpp"

namespace xenon {
    namespace utilities {
        /**
         * @brief A simple Vector3 class with operator overloads.  
         */
        template<typename T>
            requires xenon::concepts::arithmetic<T>
        struct Vector3 {
            T x;
            T y;
            T z;

            /**
             * @brief Compares two vectors.
             * @param vec: Another vector 
             */
            [[nodiscard]] auto operator<=>(const Vector3& vec) const noexcept = default;

            /**
             * @brief Adds two vectors together.
             * @param vec: Another vector.
             * @retval New vector.
             */
            [[nodiscard]] Vector3 operator+(const Vector3& vec) noexcept {
                return Vector3{ x + vec.x, y + vec.y, z + vec.z };
            }

            /**
             * @brief Subtracts two vectors together.
             * @param vec: Another vector.
             * @retval New vector.
             */
            [[nodiscard]] Vector3 operator-(const Vector3& vec) noexcept {
                return Vector3{ x - vec.x, y - vec.y, z - vec.z };
            }

             /**
             * @brief Multiplies two vectors together.
             * @param vec: Another vector.
             * @retval New vector.
             */
            [[nodiscard]] Vector3 operator*(const Vector3& vec) noexcept {
                return Vector3{ x * vec.x, y * vec.y, z * vec.z };
            }

            /**
             * @brief Divides two vectors together.
             * @param vec: Another vector.
             * @retval New vector.
             */
            [[nodiscard]] Vector3 operator/(const Vector3& vec) noexcept {
                return Vector3{ x / vec.x, y / vec.y, z * vec.z };
            }

            friend std::ostream& operator<<(std::ostream& os, const Vector3& vec) noexcept {
                os << "[" << vec.x << "; " << vec.y << "; " << vec.z << "]";
                return os;
            }
        };
    } // namespace utilities
} // namespace xenon

#endif // XENON_HG_UTILITIES_VECTOR3