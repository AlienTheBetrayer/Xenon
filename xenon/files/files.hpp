// files.hpp
//
// Xenon's Module that helps with reading and writing to files.

#ifndef XENON_HG_FILES_MODULE
#define XENON_HG_FILES_MODULE

// Libraries
#include <fstream>
#include <string>
#include <optional>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

namespace xenon {
    namespace files {
        /**
         * @brief Writing mode that can be used when writing to files.  
         * @note   
         */
        enum class writing_mode {
            overwrite = std::ios_base::in | std::ios_base::out,
            append = std::ios_base::app
        };

        /**
         * @brief Reads the file and returns a string, containing all the file's data.
         * @note   
         * @param  path: The path for the specified file 
         * @retval A string, which contains all the file's data
         */
        [[nodiscard]] std::optional<std::string> read_file(const std::string& path) noexcept {
            if(std::ifstream file(path); file.good() && file.is_open()) [[likely]] {
                std::string text;
                for(std::string line; std::getline(file, line);)
                    text += line;
                file.close();
                return text;
            } else [[unlikely]]
                return std::nullopt;
        }

        /**
         * @brief Reads the file line by line and returns a vector, which contains all the lines.
         * @note   
         * @param  path: The path for the specified file
         * @param  estimated_lines_quantity: An approximated amount of lines that a file has
         * @retval All the lines of the file.
         */
        [[nodiscard]] std::optional<std::vector<std::string>> read_file_lines(const std::string& path, const uint64_t estimated_lines_quantity = -1) noexcept {
            if(std::ifstream file(path); file.good() && file.is_open()) [[likely]] {
                std::vector<std::string> lines = {};
                if(estimated_lines_quantity != static_cast<uint64_t>(-1)) [[unlikely]]
                    lines.reserve(estimated_lines_quantity);  
                for(std::string line; std::getline(file, line);)
                    lines.emplace_back(line);
                file.close();
                return lines;
            } else [[unlikely]]
                return std::nullopt;
        }

        /**
         * @brief Counts the number of lines in a file.
         * @note   
         * @param  path: The path for the specified file  
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
                return std::nullopt;
        }

        /**
         * @brief Writes a new content to the specified file. 
         * @note   
         * @param  path: The path for the specified file
         * @param  content: The content that will be written to that file
         * @retval Status of the opened file. True if opened correctly. 
         */
        bool write_file(const std::string& path, const std::string& content, const writing_mode open_mode = writing_mode::overwrite) noexcept {
            if(std::ofstream file(path, static_cast<std::ios_base::openmode>(open_mode)); file.good() && file.is_open()) [[likely]] {
                file << content;
                file.close();
                return true;
            } else [[unlikely]]
                return false;
        }

        /**
         * @brief Writes a new content line by line from content vector to the specified file.
         * @note   
         * @param  path: The path for the specified file
         * @param  content: The content that will be written to that file
         * @retval Status of the opened file. True if opened correctly. 
         */
        bool write_file(const std::string& path, const std::vector<std::string>& content, const writing_mode open_mode = writing_mode::overwrite) noexcept {
            if(std::ofstream file(path, static_cast<std::ios_base::openmode>(open_mode)); file.good() && file.is_open()) [[likely]] {
                for(const std::string& line : content)
                    file << line << "\n";
                file.close();
                return true;
            } else [[unlikely]]
                return false;
        }

        /**
         * @brief Clears the file.
         * @note   
         * @param  path: The path for the specified file. 
         * @retval Status of the opened file. True if opened correctly. 
         */
        bool clear_file(const std::string& path) noexcept {
            if(std::ofstream file(path); file.good() && file.is_open()) [[likely]] {
                file.close();
                return true;
            } else [[unlikely]]
                return false;
        }

        /**
         * @brief Iterates a directory and calls a function with each path.
         * @note   
         * @param  path: The path to the specified directory.
         * @param  callback_func: A function that will be called with each path.
         * @retval None
         */
        template<typename F>
            requires requires(F&& func, const std::string& str) {
                func(str);
            }
        inline void iterate_folder(const std::string& path, F&& callback_func) noexcept {
            for(const auto& dir : fs::directory_iterator(path))
                callback_func(dir.path().string());
        }

        /**
         * @brief Recursively iterates a directory and calls a function with each path.
         * @note   
         * @param  path: The path to the specified directory.
         * @param  callback_func: A function that will be called with each path.
         * @retval None
         */
        template<typename F>
            requires requires(F&& func, const std::string& str) {
                func(str);
            }
        inline void recursive_iterate_folder(const std::string& path, F&& callback_func) noexcept {
            for(const auto& dir : fs::recursive_directory_iterator(path))
                callback_func(dir.path().string());
        }
    } // namespace files
} // namespace xenon

#endif // XENON_HG_FILES_MODULE