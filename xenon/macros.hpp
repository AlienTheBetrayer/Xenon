// macros.hpp
// 
// All the needed macros for Xenon.

#ifndef XENON_HG_MACROS
#define XENON_HG_MACROS

#ifdef _WIN32
// Windows OS
#define XENON_M_WIN

#ifdef WIN32_LEAN_AND_MEAN
#define XENON_M_WLAM
#endif // WIN32_LEAN_AND_MEAN

// C++ version is bigger or equals to 20
#if defined(_MSVC_LANG) && _MSVC_LANG > 201703L || __cplusplus >= 201703L
#define XENON_M_CPP20GRT
#endif // defined(_MSVC_LANG) && _MSVC_LANG > 201703L || __cplusplus >= 201703L
#endif // _WIN32

#endif // XENON_HG_MACROS