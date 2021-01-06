// xenon.hpp
//
// A file that will include each and every component of the Xenon library.
// Must be included solely by a user.

#ifndef XENON_HG_LIB
#define XENON_HG_LIB

// All the namespaces declarations so we have the @brief on each of them.

/**
 * @brief Namespace that contains every single module this library has. 
 */
namespace xenon {
    /**
     * @brief Module that is able to perform asynchronous operations.   
     */
    namespace async {

    } // namespace async

    /**
     * @brief Module that has various concepts and tools that can be used in your regular code instead of SFINAE.
     */
    namespace concepts {

    } // namespace concepts

#ifdef _WIN32
    /**
     * @brief Module that can do graphics in console, such as colors and more. Windows-only.
     */
    namespace console {
        
    } // namespace console
#endif // _WIN32

    /**
     * @brief Module that helps with reading and writing to files.
     */
    namespace files {

    } // namespace files

#ifdef _WIN32
    /**
     * @brief Module that eases pressing of keys. Windows-only.
     */
    namespace keys {

    } // namespace keys
#endif // _WIN32

    /**
     * @brief Module that has other stuff that no other module has.
     */
    namespace misc {

    } // namespace misc

#ifdef _WIN32
    /**
     * @brief Module that eases moving mouse. Windows-only.
     */
    namespace mouse {

    } // namespace mouse
#endif // _WIN32

#ifdef _WIN32
    /**
     * @brief Module that helps with managing processes. Windows-only.
     */
    namespace process {

    } // namespace process
#endif // _WIN32

    /**
     * @brief Module that is able to generate random numbers and more.
     */
    namespace random {

    } // namespace random

#ifdef _WIN32
    /**
     * @brief Module that is able to play sounds. Windows-only.
     */
    namespace sound {

    } // namespace sound
#endif // _WIN32

    /**
     * @brief Module that helps transforming and managing strings.
     */
    namespace string {

    } // namespace string

    /**
     * @brief Module that has utility stuff like Vector classes and more.
     */
    namespace utility {

    } // namespace utility
    
#ifdef _WIN32
    /**
     * @brief Module that helps with managing windows. Windows-only.
     */
    namespace window {

    } // namespace window
#endif // _WIN32
} // namespace xenon

// All the includes
#include "async/async.hpp"

#endif // XENON_HG_LIB