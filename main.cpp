#include <windows.h>
//
#include <iostream>
#include <functional>
#include <fstream>
#include <vector>
#include <filesystem>
#include "config.h"
#include "util.h"

void apply_game_settings(const std::vector<Game> games, std::function<std::string(const Game &)> game_settings_filepath_getter)
{
    for (const auto &game : games)
    {
        auto applied_game_settings_file_path = std::filesystem::path(game_settings_filepath_getter(game));
        auto game_settings_file_path = std::filesystem::path(game.settings_file_path);
        if (std::filesystem::exists(applied_game_settings_file_path))
        {
            try
            {
                util::overwrite_file(applied_game_settings_file_path, game_settings_file_path);
            }
            catch (const std::exception &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        else
        {
            std::cout << applied_game_settings_file_path << " not exists" << std::endl;
        }
    }
}

void apply_native_settings(const Config &config)
{
    util::change_monitor_settings(config.native_monitor_settings.width, config.native_monitor_settings.height, config.native_monitor_settings.refresh_rate);
    apply_game_settings(config.games, [](const Game &game) { return game.native_settings_file_path; });
}

void apply_streaming_settings(const Config &config)
{
    util::change_monitor_settings(config.streaming_monitor_settings.width, config.streaming_monitor_settings.height, config.streaming_monitor_settings.refresh_rate);
    apply_game_settings(config.games, [](const Game &game) { return game.streaming_settings_file_path; });
}

int main()
{
    auto config_file_path = std::filesystem::path(util::get_executable_directory()) / "config.json";
    if (!std::filesystem::exists(config_file_path))
    {
        std::cout << "Config file not found" << std::endl;
        return 1;
    }
    std::ifstream f(config_file_path);
    Config config;
    try
    {
        config = nlohmann::json::parse(f);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error parsing config file: " << e.what() << std::endl;
        return 1;
    }
    auto height = util::get_resolution_height();
    if (height < config.native_monitor_settings.height)
    {
        apply_native_settings(config);
    }
    else
    {
        apply_streaming_settings(config);
    }
}
