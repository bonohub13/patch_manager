#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

namespace utils
{
    /**
     * @brief Data to store input parameters for AddPatch class temporarily
     * 
     */
    struct addPatch_t
    {
        // Path of where the patch is located
        std::string source_path;
        // Path to apply the patch
        std::string target_path;
    };

    /**
     * @brief Adds patch and creates backups of the original source
     * 
     */
    class AddPatch
    {
    public:
        AddPatch(std::string &src_path, std::string &tgt_path);
        ~AddPatch(){};
    private:
        std::string src_path;   // path of where the patch is
        std::string tgt_path;   // path to apply the patch
        // files/directories to add patch
        std::vector<std::string> patch_files;
    public:
        /**
         * @brief Create a backup of original files to patch
         * 
         * @param path absolute path to create backup directory
         * @param files files to backup
         */
        void create_backup(std::filesystem::path &path, const std::vector<std::string> &files);
    };

    /**
     * @brief Check if given path exists
     * 
     * @param path Absolute path to check if exists
     * @return true 
     * @return false 
     */
    bool check_if_path_exists(const std::string &path);

    /**
     * @brief Output message formatted in a box style
     * 
     * @param msg_list list messages to output
     */
    void show_msg(const std::vector<std::string> &msg_list);
}   // namespace utils