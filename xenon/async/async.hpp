// async.hpp
//
// Xenon's Module that is able to perform asynchronous operations.

#ifndef XENON_HG_ASYNC_MODULE
#define XENON_HG_ASYNC_MODULE

// Libraries
#include <thread>
#include <tuple>
#include <functional>
#include <iostream>
#include <utility>

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

		/**
		* @brief Calls work_func asynchronously with results from callback_func, which gets called asynchronously.
		* @param callback_func: The function which returns something
		* @param work_func: The function which accepts that something that callback_func returns
		* @param args: All the arguments to the callback_func
		* @param timeout: After how many milliseconds to run the callback_func
		* @retval None
		*/
		template<typename Ret, typename... Args>
		inline void then(const std::function<Ret(Args...)>& callback_func, const std::function<void(Ret)>& work_func, Args&&... args, const uint32_t timeout = 0) noexcept {
			std::thread([=, &args...]() {
				[[unlikely]] if(timeout)
					std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
				work_func(callback_func(std::forward<Args>(args)...));
			}).detach();
		}
    } // namespace async
} // namespace xenon

#endif // XENON_HG_ASYNC_MODULE