#include <windows.h>
//
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "config.h"
#include "util.h"

void apply_native_settings(const Config &config)
{
    util::change_monitor_settings(config.native_monitor_settings.width, config.native_monitor_settings.height, config.native_monitor_settings.refresh_rate);
    for (const auto &game : config.games)
    {
        auto native_settings_file_path = std::filesystem::path(game.native_settings_file_path);
        auto settings_file_path = std::filesystem::path(game.settings_file_path);
        if (std::filesystem::exists(native_settings_file_path))
        {
            std::filesystem::copy_file(native_settings_file_path, settings_file_path, std::filesystem::copy_options::overwrite_existing);
        }
        else
        {
            std::cout << game.native_settings_file_path << " not exists" << std::endl;
        }
    }
}

void apply_streaming_settings(const Config &config)
{
    util::change_monitor_settings(config.streaming_monitor_settings.width, config.streaming_monitor_settings.height, config.streaming_monitor_settings.refresh_rate);
    for (const auto &game : config.games)
    {
        auto streaming_settings_file_path = std::filesystem::path(game.streaming_settings_file_path);
        auto settings_file_path = std::filesystem::path(game.settings_file_path);
        if (std::filesystem::exists(streaming_settings_file_path))
        {
            std::filesystem::copy_file(streaming_settings_file_path, settings_file_path, std::filesystem::copy_options::overwrite_existing);
        }
        else
        {
            std::cout << game.streaming_settings_file_path << " not exists" << std::endl;
        }
    }
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
