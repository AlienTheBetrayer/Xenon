// files.hpp
//
// Xenon's Module that helps with reading and writing to files.

#ifndef XENON_HG_FILES_MODULE
#define XENON_HG_FILES_MODULE

// Libraries
#include <fstream>
#include <string>

namespace xenon {
    namespace files {
        /**
         * @brief Reads the file and returns a string, containing all the file's data. Returns an empty string if it couldn't open the file.
         * @note   
         * @param  path: The path for the specified file. 
         * @retval 
         */
        [[nodiscard]] std::string read_file(const std::string& path) noexcept {
            if(std::ifstream file(path); file.good() && file.is_open()) [[likely]] {
                std::string text;
                for(std::string line; std::getline(file, line);)
                    text += line;
                return text;
            } else [[unlikely]]
                return "";
        }

        constexpr inline const uint64_t fileopen_err = -1;

        /**
         * @brief Counts the number of lines in a file. Returns fileopen_err if it couldn't open the file.
         * @note   
         * @param  path: The path for the specified file.  
         * @retval Number of lines
         */
        [[nodiscard]] uint64_t count_lines(const std::string& path) noexcept {
            if(std::ifstream file(path); file.good() && file.is_open()) [[likely]] {
                file.unsetf(std::ios_base::skipws);
                return static_cast<uint64_t>(std::count(std::istream_iterator<char>(file), std::istream_iterator<char>(), '\n'));
            }
            else [[unlikely]]
                return fileopen_err;
        }
    } // namespace files
} // namespace xenon

#endif // XENON_HG_FILES_MODULE