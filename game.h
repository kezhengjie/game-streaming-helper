#ifndef __GAME_H__
#define __GAME_H__

#include <nlohmann/json.hpp>

struct Game
{
    std::string name;
    std::string settings_file_path;
    std::string streaming_settings_file_path;
    std::string native_settings_file_path;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Game, name, settings_file_path, streaming_settings_file_path, native_settings_file_path)

#endif