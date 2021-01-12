// rect.hpp
//
// A simple Rect class that is a part of Utilities Module.

#ifndef XENON_HG_UTILITIES_RECT
#define XENON_HG_UTILITIES_RECT

// Xenon's Modules
#include "../concepts/concepts.hpp"

namespace xenon {
    namespace utilities {
        /**
         * @brief A simple Rect class with operator overloads.  
         */
        template<typename T>
            requires xenon::concepts::arithmetic<T>
        struct Rect {
            T left;
            T right;
            T top;
            T bottom;

            /**
             * @brief Compares two rectangles.
             * @param rect: Another rectangle 
             */
            [[nodiscard]] auto operator<=>(const Rect& rect) const noexcept = default;

            /**
             * @brief Adds two rectangles together.
             * @param rect: Another rectangle
             * @retval New rectangle
             */
            [[nodiscard]] Rect operator+(const Rect& rect) noexcept {
                return Rect{ left + rect.left, right + rect.right, top + rect.top, bottom + rect.bottom };
            }

            /**
             * @brief Subtracts two rectangles.
             * @param rect: Another rectangle
             * @retval New rectangle
             */
            [[nodiscard]] Rect operator-(const Rect& rect) noexcept {
                return Rect{ left - rect.left, right - rect.right, top - rect.top, bottom - rect.bottom };
            }

             /**
             * @brief Multiplies two rectangle together.
             * @param rect: Another rectangle
             * @retval New rectangle
             */
            [[nodiscard]] Rect operator*(const Rect& rect) noexcept {
                return Rect{ left * rect.left, right * rect.right, top * rect.top, bottom * rect.bottom };
            }

            /**
             * @brief Divides two rectangles.
             * @param rect: Another rectangle
             * @retval New rectangle
             */
            [[nodiscard]] Rect operator/(const Rect& rect) noexcept {
                return Rect{ left / rect.left, right / rect.right, top / rect.top, bottom / rect.bottom };
            }

            friend std::ostream& operator<<(std::ostream& os, const Rect& rect) noexcept {
                os << "[" << rect.left << "; " << rect.right << "; " << rect.top << "; " << rect.bottom << "]";
                return os;
            }
        };
    } // namespace utilities
} // namespace xenon

#endif // XENON_HG_UTILITIES_RECT