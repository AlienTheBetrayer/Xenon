// async.hpp
//
// Xenon's Module that is able to perform asynchronous operations.

#ifndef XENON_HG_ASYNC_MODULE
#define XENON_HG_ASYNC_MODULE

// Libraries
#include <thread>
#include <iostream>
#include <utility>

// Xenon's Modules
#include "../concepts/concepts.hpp"

namespace xenon {
    namespace async {
		/**
		* @brief Runs a function in the separate thread with specified arguments and return type.
		* @param func: The function itself
		* @param args: All the args that the function accepts
		* @note
		* @retval None
		*/
		template<typename F, typename... Args>
			requires xenon::concepts::callable<F, Args...>
		inline void run(F&& func, Args&&... args) noexcept {
			std::thread(func, std::forward<Args>(args)...).detach();
		}

		/**
		* @brief Calls work_func asynchronously with results from callback_func, which gets called asynchronously.
		* @param callback_func: The function which returns something
		* @param work_func: The function which accepts that something that callback_func returns
		* @param args: All the arguments to the callback_func
		* @note
		* @retval None
		*/
		template<typename Ret, typename F, typename F_, typename... Args>
			requires !xenon::concepts::void_<Ret> && requires(F&& func, Ret& ret, Args&&... args) {
				ret = func(std::forward<Args>(args)...);
			} && xenon::concepts::callable<F_, Ret>
		inline void then(F&& callback_func, F_&& work_func, Args&&... args) noexcept {
			xenon::async::run([=, &args...](){
				work_func(callback_func(std::forward<Args>(args)...));
			});
		}
    } // namespace async
} // namespace xenon

#endif // XENON_HG_ASYNC_MODULE