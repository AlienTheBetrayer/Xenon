// xenon.hpp
//
// A file that will include each and every component of the Xenon library.
// Must be included solely by a user.

#ifndef XENON_HG_LIB
#define XENON_HG_LIB

// Library's dependencies
#include "./macros.hpp"

#ifdef XENON_M_CPP20GRT
// All the namespaces declarations so we have the @brief on each of them.

/**
 * @brief Namespace that contains every single module this library has. 
 */
namespace xenon {
    /**
     * @brief Module that is able to work with args and parameter packs.  
     */
    namespace args {

    }

    /**
     * @brief Module that is able to perform asynchronous operations.   
     */
    namespace async {

    } // namespace async

#ifdef XENON_M_CPP20GRT
    /**
     * @brief Module that has various concepts and tools that can be used in your regular code instead of SFINAE.
     */
    namespace concepts {

    } // namespace concepts
#endif // XENON_M_CPP20GRT

#ifdef XENON_M_WIN
    /**
     * @brief Module that can do graphics in console, such as colors and more. Windows-only.
     */
    namespace console {
        
    } // namespace console
#endif // XENON_M_WIN

    /**
     * @brief Module that helps with reading and writing to files.
     */
    namespace files {

    } // namespace files

#ifdef XENON_M_WIN
    /**
     * @brief Module that eases pressing of keys. Windows-only.
     */
    namespace keys {

    } // namespace keys
#endif // XENON_M_WIN

#ifdef XENON_M_WIN
    /**
     * @brief Module that is able to work with modules. Windows-only.  
     */
    namespace modules {

    }
#endif // XENON_M_WIN

    /**
     * @brief Module that has other stuff that no other module has.
     */
    namespace misc {

    } // namespace misc

#ifdef XENON_M_WIN
    /**
     * @brief Module that eases moving mouse. Windows-only.
     */
    namespace mouse {

    } // namespace mouse
#endif // XENON_M_WIN

#ifdef XENON_M_WIN
    /**
     * @brief Module that helps with managing processes. Windows-only.
     */
    namespace process {

    } // namespace process
#endif // XENON_M_WIN

    /**
     * @brief Module that is able to generate random numbers and more.
     */
    namespace random {

    } // namespace random

#ifdef XENON_M_WIN
    /**
     * @brief Module that is able to play sounds. Windows-only.
     */
    namespace sound {

    } // namespace sound
#endif // XENON_M_WIN

    /**
     * @brief Module that helps transforming and managing strings.
     */
    namespace string {

    } // namespace string

    /**
     * @brief Module that is able to work with time.  
     */
    namespace time {

    } // namespace time

    /**
     * @brief Module that has utility stuff like Vector classes and more.
     */
    namespace utility {

    } // namespace utility
    
#ifdef XENON_M_WIN
    /**
     * @brief Module that helps with managing windows. Windows-only.
     */
    namespace window {

    } // namespace window
#endif // XENON_M_WIN
} // namespace xenon

// All the includes
#include "concepts/concepts.hpp"
#include "async/async.hpp"
#include "utilities/utilities.hpp"
#include "files/files.hpp"
#include "random/random.hpp"
#include "time/time.hpp"

// Windows-only includes
#ifdef XENON_M_WIN
#include "console/console.hpp"
#include "process/process.hpp"
#endif

#else // XENON_M_CPP17GRT
#error xenon requires at least cpp20
#endif // XENON_M_CPP17GRT

#endif // XENON_HG_LIB