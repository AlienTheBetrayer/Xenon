// modules.hpp
//
// Xenon's Module that is able to work with modules. Windows-only.

#ifndef XENON_HG_MODULES_MODULE
#define XENON_HG_MODULES_MODULE

#include "../macros.hpp"

#ifdef XENON_M_WIN

// Libraries
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <TlHelp32.h>
#include <optional>
#include <type_traits>
#include <string>

struct modinfo_t  {
    procinfo_t proc;
    MODULEENTRY32 mod;
};

// Dependenies
#include "../process/process.hpp"

namespace xenon {
    namespace modules {
        /**
         * @brief Lists through all the modules and calls a function on each of them with modinfo_t. 
         * @note   
         * @param  func: The function that will be called. The function return type has to be boolean. If it returns false, the process_list_for_each function breaks. Always return true or false! 
         * @retval None
         */
        template<typename F>    
            requires requires(F&& func, modinfo_t&& me32) {
                requires std::is_same_v<decltype(func(me32)), bool>;
            }
        [[nodiscard]] inline void list_for_each(F&& func) noexcept {
            xenon::process::list_for_each([&](const procinfo_t& process_info) noexcept -> bool {
                HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_info.th32ProcessID);  
                MODULEENTRY32 entry;
                entry.dwSize = sizeof(MODULEENTRY32);
                if(Module32First(snapshot, &entry)) [[likely]]
                    for(; Module32Next(snapshot, &entry) ;)
                        if(!func(modinfo_t{ .proc = process_info, .mod = entry })) [[unlikely]]
                            break;
                CloseHandle(snapshot);
                return true;
            });
        }

        /**
         * @brief Lists through all the modules of the process and calls a function on each of them with modinfo_t. 
         * @note   
         * @param  func: The function that will be called. The function return type has to be boolean. If it returns false, the process_list_for_each function breaks. Always return true or false! 
         * @retval None
         */
        template<typename F>    
            requires requires(F&& func, modinfo_t&& me32) {
                requires std::is_same_v<decltype(func(me32)), bool>;
            }
        [[nodiscard]] inline void process_list_for_each(F&& func, const HANDLE handle) noexcept {
            const DWORD pid = GetProcessId(handle);
            HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);  
            MODULEENTRY32 entry;
            entry.dwSize = sizeof(MODULEENTRY32);
            if(Module32First(snapshot, &entry)) [[likely]]
                for(; Module32Next(snapshot, &entry) ;)
                    if(!func(modinfo_t{ .mod = entry })) [[unlikely]]
                        break;
            CloseHandle(snapshot);
        }

        /**
         * @brief Finds the module with the specified name.
         * @note   
         * @param  module_name: The module name
         * @retval The process info 
         */
        [[nodiscard]] std::optional<modinfo_t> find_name(const std::string& module_name) noexcept {
            std::optional<modinfo_t> info = std::nullopt;
            list_for_each([&](const modinfo_t& info_) noexcept -> bool {
                if(!strcmp(info_.mod.szModule, module_name.c_str())) [[unlikely]] {
                    info = info_;
                    return false;
                } else [[likely]]
                    return true;
            });
            return info;
        }
    } // namespace modules
} // namespace xenon

#endif // XENON_M_WIN
#endif // XENON_HG_MODULES_MODULE