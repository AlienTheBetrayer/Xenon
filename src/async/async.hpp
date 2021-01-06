// async.hpp
//
// Xenon's Module that is able to perform asynchronous operations.

#ifndef XENON_HG_ASYNC_MODULE
#define XENON_HG_ASYNC_MODULE

// Libraries
#include <thread>
#include <tuple>
#include <functional>

namespace xenon {
    namespace async {
		/**
		* @brief Runs a function in the separate thread with specified arguments and return type.
		* @param func: The function itself
		* @param args: All the args that the function accepts
		* @retval None
		*/
		template<typename Ret = void, typename... Args>
		inline void run(const std::function<Ret(Args...)>& func, Args&&... args) noexcept {
			std::thread(func, std::forward<Args>(args)...).detach();
		}

		/**
		* @brief Runs a function in a separate thread with a specified return type without any arguments.
		* @param func: The function itself
		* @retval None
		*/
        template<typename Ret = void>
		inline void run(const std::function<Ret(void)>& func) noexcept {
			std::thread(func).detach();
		}

		template<typename Ret, typename... Args>
		inline void then(const std::function<Ret(Args...)>& callback_func, Args&&... args) noexcept {
			std::thread([&](){
				Ret ret = callback_func(std::forward<Args>(args)...);
			}).detach();
		}

		template<typename Ret>
		inline void then(const std::function<Ret(void)>& callback_func) noexcept {
			std::thread([&](){
				Ret ret = callback_func();
			}).detach();
		}
    } // namespace async
} // namespace xenon

#endif // XENON_HG_ASYNC_MODULE