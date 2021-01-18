// concepts.hpp
//
// Xenon's Module that has various concepts and tools that can be used in your regular code instead of SFINAE.

#ifndef XENON_HG_CONCEPTS_MODULE
#define XENON_HG_CONCEPTS_MODULE

// Libraries
#include <type_traits>
#include <cstdint>

namespace {
    // -- Helper functions. Should not be used by the user. -- \\ 

    template<typename T, typename... Ts>
    concept XENON_HF_all_same = (std::is_same_v<T, Ts> && ...);

    template<typename T, typename... Ts>
    concept XENON_HF_atleast_same = (std::is_same_v<T, Ts> || ...);
}

namespace xenon {
    namespace concepts {
#pragma region Other
        /**
         * @brief Works with any T.  
         */
        template<typename T>
        concept always_satisfied = true;

        /**
         * @brief Doesn't work with any T.  
         */
        template<typename T>
        concept always_unsatisfied = false;
#pragma endregion Other

#pragma region Types
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
        concept arithmetic = floating_point<T> || integral<T>;

        /**
         * @brief Works if T is a function.  
         */
        template<typename T>
        concept function = std::is_function_v<T>;

        /**
         * @brief Works if T is void.  
         */
        template<typename T>
        concept void_ = std::is_void_v<T>;
#pragma endregion Types

#pragma region Modifiers
        /**
         * @brief Works if T is const.
         */
        template<typename T>
        concept constant = std::is_const_v<T>;

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
         * @brief Works if T is a lvalue reference.  
         */
        template<typename T>
        concept lvalue_ref = std::is_lvalue_reference_v<T>;

        /**
         * @brief Works if T is a lvalue reference.  
         */
        template<typename T>
        concept clvalue_ref = std::is_lvalue_reference_v<T> && std::is_const_v<T>;

        /**
         * @brief Works if T is a rvalue reference.  
         */
        template<typename T>
        concept rvalue_ref = std::is_rvalue_reference_v<T>;

        /**
         * @brief Works if T is some reference.  
         */
        template<typename T>
        concept ref = lvalue_ref<T> || rvalue<T> || clvalue_ref<T>;

        /**
         * @brief Works if T is volatile.  
         */
        template<typename T>
        concept volatile_ = std::is_volatile_v<T>;
#pragma endregion Modifiers

#pragma region Operators
        /**
         * @brief Works if T is callable with Args. 
         */
        template<typename F, typename... Args>
        concept callable = requires(F&& func, Args&&... args) {
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
         * @brief Works if T is equalable to T_.
         */
        template<typename T, typename T_>
        concept equals_able = requires(const T& t, const T_& t_) {
            t == t_;
        };

        /**
         * @brief Works if T is biggerable to T_.
         */
        template<typename T, typename T_>
        concept bigger_able = requires(const T& t, const T_& t_) {
            t > t_;
        };

        /**
         * @brief Works if T is lessable to T_.
         */
        template<typename T, typename T_>
        concept less_able = requires(const T& t, const T_& t_) {
            t < t_;
        };

        /**
         * @brief Works if T is biggerable or equalsable to T_.
         */
        template<typename T, typename T_>
        concept bigger_equals_able = requires(const T& t, const T_& t_) {
            t >= t_;
        };

        /**
         * @brief Works if T is lessable or equalsable to T_.
         */
        template<typename T, typename T_>
        concept less_equals_able = requires(const T& t, const T_& t_) {
            t <= t_;
        };
#pragma endregion Operators

#pragma region Equality_of_types
        /**
         * @brief Works if all Ts are the same types.  
         */
        template<typename... Ts>
        concept all_same = XENON_HF_all_same<Ts...>;

        /**
         * @brief Works if there are at least two same types.
         */
        template<typename... Ts>
        concept atleast_same = XENON_HF_atleast_same<Ts...>;

        /**
         * @brief Works if T and T_ are the same types.  
         */
        template<typename T, typename T_>
        concept same = all_same<T, T_>;
#pragma endregion Equality_of_types

#pragma region Quantity_of_args
        /**
         * @brief Works if the amount of args is N.   
         */
        template<typename... Ts, uint32_t N>
        concept equals_n_args = (sizeof...(Ts) == N);

        /**
         * @brief Works if the amount of args is less than N.  
         */
        template<typename... Ts, uint32_t N>
        concept less_n_args = (sizeof...(Ts) < N);
        
        /**
         * @brief Works if the amount of args is more than N. 
         */
        template<typename... Ts, uint32_t N>
        concept more_n_args = (sizeof...(Ts) > N);

        /**
         * @brief Works if the amount of args is less or equals than N.   
         */
        template<typename... Ts, uint32_t N>
        concept less_equals_n_args = (sizeof...(Ts) <= N);

        /**
         * @brief Works if the amount of args is more or equals than N.  
         */
        template<typename... Ts, uint32_t N>
        concept more_equals_n_args = (sizeof...(Ts) >= N);

        /**
         * @brief Works if the amount of args is not N. 
         */
        template<typename... Ts, uint32_t N>
        concept not_equals_n_args = (sizeof...(Ts) != N);

        /**
         * @brief Works if the amount of args is even. 
         */
        template<typename... Ts>
        concept even_n_args = (sizeof...(Ts) % 2 == 0);

        /**
         * @brief Works if the amount of args is odd. 
         */
        template<typename... Ts>
        concept odd_n_args = (sizeof...(Ts) % 2 != 0);
#pragma endregion Quantity_of_args
        
#pragma region Iterators
        /**
         * @brief Works if T class has begin function.  
         */
        template<typename T>
        concept has_begin = requires(T& obj) {
            requires std::is_class_v<T>;
            obj.begin();
        };

        /**
         * @brief Works if T class has end function.  
         */
        template<typename T>
        concept has_end = requires(T& obj) {
            requires std::is_class_v<T>;
            obj.end();
        };

        /**
         * @brief Works if T class has rbegin function.  
         */
        template<typename T>
        concept has_rbegin = requires(T& obj) {
            requires std::is_class_v<T>;
            obj.rbegin();
        };

        /**
         * @brief Works if T class has rend function.  
         */
        template<typename T>
        concept has_rend = requires(T& obj) {
            requires std::is_class_v<T>;
            obj.rend();
        };

        /**
         * @brief Works if T class has cbegin function.  
         */
        template<typename T>
        concept has_cbegin = requires(T& obj) {
            requires std::is_class_v<T>;
            obj.cbegin();
        };

        /**
         * @brief Works if T class has cend function.  
         */
        template<typename T>
        concept has_cend = requires(T& obj) {
            requires std::is_class_v<T>;
            obj.cend();
        };

        /**
         * @brief Works if T class has crbegin function.  
         */
        template<typename T>
        concept has_crbegin = requires(T& obj) {
            requires std::is_class_v<T>;
            obj.crbegin();
        };

        /**
         * @brief Works if T class has crend function.  
         */
        template<typename T>
        concept has_crend = requires(T& obj) {
            requires std::is_class_v<T>;
            obj.crend();
        };

        /**
         * @brief Works if T class has regular iterator.  
         */
        template<typename T>
        concept has_iterator = requires(T& obj) {
            requires std::is_class_v<T>;
            requires has_begin<T> && has_end<T>;
        };

        /**
         * @brief Works if T class has reverse iterator.  
         */
        template<typename T>
        concept has_reverse_iterator = requires(T& obj) {
            requires std::is_class_v<T>;
            requires has_rbegin<T> && has_rend<T>;
        };

        /**
         * @brief Works if T class has const iterator.
         */
        template<typename T>
        concept has_const_iterator = requires(T& obj) {
            requires std::is_class_v<T>;
            requires has_cbegin<T> && has_cend<T>;
        };

        /**
         * @brief Works if T class has const reverse iterator.  
         */
        template<typename T>
        concept has_const_reverse_iterator = requires(T& obj) {
            requires std::is_class_v<T>;
            requires has_crbegin<T> && has_crend<T>;
        };

        /**
         * @brief Works if T class has regular, reverse, const iterators. 
         */
        template<typename T>
        concept has_full_iterator = requires(T& obj) {
            requires std::is_class_v<T>;
            requires has_iterator<T> && has_reverse_iterator<T> && has_const_iterator<T> && has_const_reverse_iterator<T>;
        };
#pragma endregion Iterators
    } // namespace concepts
} // namespace xenon

#endif // XENON_HG_CONCEPTS_MODULE