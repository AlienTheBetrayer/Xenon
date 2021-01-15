// files.hpp
//
// Xenon's Module that helps with reading and writing to files.

#ifndef XENON_HG_FILES_MODULE
#define XENON_HG_FILES_MODULE

// Libraries
#include <fstream>
#include <string>
#include <optional>

namespace xenon {
    namespace files {
        /**
         * @brief Reads the file and returns a string, containing all the file's data.
         * @note   
         * @param  path: The path for the specified file. 
         * @retval 
         */
        [[nodiscard]] std::optional<std::string> read_file(const std::string& path) noexcept {
            if(std::ifstream file(path); file.good() && file.is_open()) [[likely]] {
                std::string text;
                for(std::string line; std::getline(file, line);)
                    text += line;
                file.close();
                return text;
            } else [[unlikely]]
                return {};
        }

        /**
         * @brief Counts the number of lines in a file.
         * @note   
         * @param  path: The path for the specified file.  
         * @retval Number of lines
         */
        [[nodiscard]] std::optional<uint64_t> count_lines(const std::string& path) noexcept {
            if(std::ifstream file(path); file.good() && file.is_open()) [[likely]] {
                file.unsetf(std::ios_base::skipws);
                const uint64_t lines = static_cast<uint64_t>(std::count(std::istream_iterator<char>(file), std::istream_iterator<char>(), '\n')); 
                file.close();
                return lines;
            }
            else [[unlikely]]
                return {};
        }

        bool write_file(const std::string& path, const std::string& content) noexcept {
            if(std::ofstream file(path); file.good() && file.is_open()) [[likely]] {
                file << content;
                file.close();
                return true;
            } else [[unlikely]]
                return false;
        }
    } // namespace files
} // namespace xenon

#endif // XENON_HG_FILES_MODULE