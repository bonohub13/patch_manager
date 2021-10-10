#include <iostream>
#include <memory>
#include "../include/utils/include/utils.hpp"

int main(int argc, char **argv)
{
    utils::Modes mode = utils::Modes::DEFAULT;
    std::unique_ptr<utils::AddPatch> addPatch;
    std::unique_ptr<utils::addPatch_t> patch_info
            = std::make_unique<utils::addPatch_t>();

    for (unsigned int i=1; i<argc; i++)
    {
        switch (mode)
        {
        case utils::Modes::DEFAULT:
        case utils::Modes::ADD_PATCH_DONE:
            if ((std::string(argv[i]) == "--add-patch" && (argc - i) > 4))
            {
                mode = utils::Modes::ADD_PATCH;
            }
            break;
        case utils::Modes::ADD_PATCH:
            break;
        default:
            break;
        }

        if (mode == utils::Modes::ADD_PATCH)
        {
            if (std::string(argv[i]) == "-s" && i+1 < argc)
            {
                patch_info->source_path = argv[i+1];
            }
            else if (std::string(argv[i]) == "-t" && i+1 < argc)
            {
                patch_info->target_path = argv[i+1];
            }

            if (patch_info->source_path.length() > 0
                    && patch_info->target_path.length() > 0)
            {
                if (utils::check_if_path_exists(patch_info->source_path)
                        && utils::check_if_path_exists(patch_info->target_path))
                {
                    addPatch = std::make_unique<utils::AddPatch>(
                            patch_info->source_path,
                            patch_info->target_path);
                    patch_info.release();
                    mode = utils::Modes::ADD_PATCH_DONE;
                }
            }
        }
    }

    return 0;
}
