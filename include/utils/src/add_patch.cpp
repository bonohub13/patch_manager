#include "../include/add_patch.hpp"

utils::AddPatch::AddPatch(std::string &src_path, std::string &tgt_path)
    : src_path(src_path), tgt_path(tgt_path)
{
    using std::filesystem::directory_iterator;
    
    std::string file_path;
    std::vector<std::string> msg_vector = {
        "Ignoring files/directories starting with .git",
        "    Examples:",
        "      > .git",
        "      > .gitignore"
    };

    show_msg(msg_vector);

    for (const auto &file : directory_iterator(src_path))
    {
        file_path
                = std::string(file.path()).substr(std::string(file.path()).find_last_of("/") + 1);

        if (file_path.substr(0, 4).compare(".git") != 0)
        {
            std::cout << file_path << std::endl;
            patch_files.push_back(file_path);
        }
    }
}

void utils::AddPatch::create_backup(const std::filesystem::path &path,
                                    const std::vector<std::string> &files)
{
    namespace fs = std::filesystem;

    bool check_result;
    std::string src_path_tmp;
    std::string tgt_path_tmp;

    check_result = fs::create_directory(path);

    if (!check_result)
    {
        std::cout << "DIRECTORY CREATE FAILURE: Failed to create directory at " << path << "." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (const auto &file : files)
    {
        src_path_tmp = this->tgt_path.append("/".append(file));
        tgt_path_tmp = std::string(path).append("/".append(file));

        try
        {
            check_result = fs::copy(fs::path(src_path_tmp),
                                    fs::path(tgt_path_tmp));

            if (!check_result)
            {
                std::cout << "FILE COPY FAILURE: Failed to copy file " << src_path_tmp
                          << " as " << tgt_path_tmp << "." << std::endl;
                exit(EXIT_FAILURE);
            }

            check_result = fs::remove(fs::path(src_path_tmp));

            if (!check_result)
            {
                std::cout << "FILE DELETE FAILURE: Failed to delete file "
                          << src_path_tmp << "." << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        catch (fs::filesystem_error &e)
        {
            std::cout << e.what() << std::endl;
            abort(100);
        }
    }
}

bool utils::check_if_path_exists(const std::string &path)
{
    namespace fs = std::filesystem;

    return fs::exists(path);
}

void utils::show_msg(const std::vector<std::string> &msg_list)
{
    unsigned int longest_msg = 0;

    for (const auto &msg : msg_list)
    {
        longest_msg = (msg.length() > longest_msg) ? msg.length() : longest_msg;
    }

    std::cout << "+--" << std::string(longest_msg, '-') << "--+" << std::endl;
    
    for (const auto &msg : msg_list)
    {
        std::cout << "|  " << msg << std::string(longest_msg - msg.length(), ' ') << "  |" << std::endl;
    }
    
    std::cout << "+--" << std::string(longest_msg, '-') << "--+" << std::endl;
}
