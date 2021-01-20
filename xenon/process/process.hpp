// async.hpp
//
// Xenon's Module that helps with managing processes. Windows-only.

#ifndef XENON_HG_PROCESS_MODULE
#define XENON_HG_PROCESS_MODULE

#include "../macros.hpp"

#ifdef XENON_M_WIN

// Libraries
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <TlHelp32.h>
#include <optional>
#include <string>

// Data types
using procinfo_t = PROCESSENTRY32;

namespace xenon {
    namespace process {
        /**
         * @brief Opens the process with process id.
         * @note   
         * @param  process_id: The identificator of the process
         * @param  access: The access that will be used to open that process
         * @retval Handle of the opened process
         */
        [[nodiscard]] HANDLE open_process_id(const uint32_t process_id, const DWORD access = PROCESS_ALL_ACCESS) noexcept {
            return OpenProcess(access, 0, process_id);
        }

        /**
         * @brief Opens the process with it's window name.
         * @note   
         * @param  window_name: The title of the window
         * @param  access: The access that will be used to open that process
         * @retval Handle of the opened process
         */
        [[nodiscard]] HANDLE open_window_name(const std::string& window_name, const DWORD access = PROCESS_ALL_ACCESS) noexcept {
            HWND window = FindWindowA(0, window_name.c_str());
            DWORD pid;
            GetWindowThreadProcessId(window, &pid);
            return open_process_id(pid, access);
        }

        /**
         * @brief Lists through all the processes and calls a function on each of them with procinfo_t. 
         * @note   
         * @param  func: The function that will be called. The function return type has to be boolean. If it returns false, the process_list_for_each function breaks. Always return true or false! 
         * @retval None
         */
        template<typename F>    
            requires requires(F&& func, procinfo_t&& pe32) {
                // TODO: make this test if the return type is boolean(make sure to do this on all the functions in the library!)

                func(pe32);
            }
        [[nodiscard]] inline void process_list_for_each(F&& func) noexcept {
            HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);  
            procinfo_t entry;
            entry.dwSize = sizeof(procinfo_t);
            if(Process32First(snapshot, &entry)) [[likely]]
                for(; Process32Next(snapshot, &entry) ;)
                    if(!func(entry)) [[unlikely]]
                        break;
            CloseHandle(snapshot);
        }

        /**
         * @brief Lists through all the processes
         * @note   
         * @param  process_name: The process name(not the window)
         * @retval The process info 
         */
        [[nodiscard]] std::optional<procinfo_t> find_process_name(const std::string& process_name) noexcept {
            procinfo_t info = {};
            info.dwSize = 0;
            process_list_for_each([&](const procinfo_t& info_) noexcept -> bool {
                if(!strcmp(info_.szExeFile, process_name.c_str())) [[unlikely]] {
                    info = info_;
                    return false;
                } else [[likely]]
                    return true;
            });
            if(info.dwSize == 0) [[unlikely]]
                return std::nullopt;
            else [[likely]]
                return info;
        }

        /**
         * @brief Terminates the process with the specified exit code 
         * @note   
         * @param  handle: Handle to the process 
         * @param  exit_code: The exit code
         * @retval None
         */
        void terminate(const HANDLE handle, const uint32_t exit_code = -1) noexcept {
            TerminateProcess(handle, exit_code);
        }

        /**
         * @brief Gets the process name 
         * @note   
         * @param  handle: Handle to the process 
         * @retval Process name
         */
        [[nodiscard]] std::string get_name(const HANDLE handle) noexcept {
            DWORD len = MAX_PATH;
            char name[MAX_PATH];
            QueryFullProcessImageName(handle, NULL, name, &len);
            return std::string(name);
        }

        /**
         * @brief Gets the process identificator
         * @note   
         * @param  handle: Handle to the process 
         * @retval Process identificator 
         */
        [[nodiscard]] DWORD get_pid(const HANDLE handle) noexcept {
            return GetProcessId(handle);
        }

        /**
         * @brief Gets the HANDLE from HWND
         * @note   
         * @param  window: The window HWND 
         * @param  access: The access to open that window
         * @retval The handle to that process
         */
        [[nodiscard]] HANDLE get_hwnd(const HWND window, const DWORD access = PROCESS_ALL_ACCESS) noexcept {
            DWORD pid;
            GetWindowThreadProcessId(window, &pid);
            return xenon::process::open_process_id(pid, access);
        }
    } // namespace proces
} // namespace xenon

#endif // XENON_M_WIN
#endif // XENON_HG_PROCESS_MODULE