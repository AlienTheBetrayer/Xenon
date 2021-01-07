// concepts.hpp
//
// Xenon's Module that has various concepts and tools that can be used in your regular code instead of SFINAE.

#ifndef XENON_HG_CONCEPTS_MODULE
#define XENON_HG_CONCEPTS_MODULE

// Libraries
#include <type_traits>

namespace {
    /**
     * @brief A helper function. Should not be used by the user.
     */
    template<typename T, typename... Ts>
    concept XENON_HF_all_same = (std::is_same_v<T, Ts> && ...);
}

namespace xenon {
    namespace concepts {
        /**
         * @brief Works with any T.  
         */
        template<typename T>
        concept always_satisfied = true;

        /**
         * @brief Works if T is integral.  
         */
        template<typename T>
        concept integral = std::is_integral_v<T>;

        /**
         * @brief Works if T is a signed integral.
         */
        template<typename T>
        concept signed_integral = integral<T> && std::is_signed_v<T>;

        /**
         * @brief Works if T is an unsigned integral.
         */
        template<typename T>
        concept unsigned_integral = integral<T> && std::is_unsigned_v<T>;

        /**
         * @brief Works if T is a floating point.
         */
        template<typename T>
        concept floating_point = std::is_floating_point_v<T>;

        /**
         * @brief Works if T is either floating point or integral.  
         */
        template<typename T>
        concept arithmetic = floating_point<T> && integral<T>;

        /**
         * @brief Works if T is const.
         */
        template<typename T>
        concept constant = std::is_const_v<T>;

        /**
         * @brief Works if T is a function.  
         */
        template<typename T>
        concept function = std::is_function_v<T>;
        
        /**
         * @brief Works if T is callable with Args. 
         */
        template<typename F, typename... Args>
        concept callable = requires(const F&& func, Args&&... args) {
            requires function<F>;
            func(std::forward<Args>(args)...);
        };

        /**
         * @brief Works if T is addable to T_.
         */
        template<typename T, typename T_>
        concept addable = requires(const T& t, const T_& t_) {
            t + t_;
        };

        /**
         * @brief Works if T_ is subtractable from T.
         */
        template<typename T, typename T_>
        concept subtractable = requires(const T& t, const T_& t_) {
            t - t_;
        };

        /**
         * @brief Works if T is divisible by T_.
         */
        template<typename T, typename T_>
        concept divisible = requires(const T& t, const T_& t_) {
            t / t_;
        };

        /**
         * @brief Works if T is multipliable by T_.
         */
        template<typename T, typename T_>
        concept multipliable = requires(const T& t, const T_& t_) {
            t * t_;
        };

        /**
         * @brief Works if T is settable to T_.
         */
        template<typename T, typename T_>
        concept settable = requires(T& t, const T_& t_) {
            t = t_;
        };

        /**
         * @brief Works if T is a lvalue reference.  
         */
        template<typename T>
        concept lvalue_ref = std::is_lvalue_reference_v<T>;

        /**
         * @brief Works if T is a rvalue reference.  
         */
        template<typename T>
        concept rvalue_ref = std::is_rvalue_reference_v<T>;

        /**
         * @brief Works if T is a pointer. 
         */
        template<typename T>
        concept pointer = std::is_pointer_v<T>;

        /**
         * @brief Works if T is an array. 
         */
        template<typename T>
        concept array = std::is_array_v<T>;

        /**
         * @brief Works if all Ts are the same types.  
         */
        template<typename... Ts>
        concept all_same = XENON_HF_all_same<Ts...>;

        /**
         * @brief Works if T and T_ are the same types.  
         */
        template<typename T, typename T_>
        concept same = all_same<T, T_>;
    } // namespace concepts
} // namespace xenon

#endif // XENON_HG_CONCEPTS_MODULE