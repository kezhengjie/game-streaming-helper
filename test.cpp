#include "Windows.h"
#include "entity.h"
#include "util.h"
#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

void show_dm(const DEVMODE& dm)
{
    std::cout
        << "dmDeviceName:" << dm.dmDeviceName << " "
        << "dmSpecVersion:" << dm.dmSpecVersion << " "
        << "dmDriverVersion:" << dm.dmDriverVersion << " "
        << "dmSize:" << dm.dmSize << " "
        << "dmDriverExtra:" << dm.dmDriverExtra << " "
        << "dmFields:" << dm.dmFields << " "
        << "dmColor: " << dm.dmColor << " "
        << "dmDuplex: " << dm.dmDuplex << " "
        << "dmYResolution: " << dm.dmYResolution << " "
        << "dmTTOption: " << dm.dmTTOption << " "
        << "dmCollate: " << dm.dmCollate << " "
        << "dmFormName: " << dm.dmFormName << " "
        << "dmLogPixels: " << dm.dmLogPixels << " "
        << "dmBitsPerPel: " << dm.dmBitsPerPel << " "
        << "dmPelsWidth: " << dm.dmPelsWidth << " "
        << "dmPelsHeight: " << dm.dmPelsHeight << " "
        << "dmDisplayFrequency: " << dm.dmDisplayFrequency << " "
        << "dmICMMethod: " << dm.dmICMMethod << " "
        << "dmICMIntent: " << dm.dmICMIntent << " "
        << "dmMediaType: " << dm.dmMediaType << " "
        << "dmDitherType: " << dm.dmDitherType << " "
        << "dmReserved1: " << dm.dmReserved1 << " "
        << "dmReserved2: " << dm.dmReserved2 << " "
        << "dmPanningWidth: " << dm.dmPanningWidth << " "
        << "dmPanningHeight: " << dm.dmPanningHeight << " "
        << "dmOrientation: " << dm.dmOrientation << " "
        << "dmPaperSize: " << dm.dmPaperSize << " "
        << "dmPaperLength: " << dm.dmPaperLength << " "
        << "dmPaperWidth: " << dm.dmPaperWidth << " "
        << "dmScale: " << dm.dmScale << " "
        << "dmCopies: " << dm.dmCopies << " "
        << "dmDefaultSource: " << dm.dmDefaultSource << " "
        << "dmPrintQuality: " << dm.dmPrintQuality << " "
        << "dmDisplayOrientation: " << dm.dmDisplayOrientation << " "
        << "dmDisplayFixedOutput: " << dm.dmDisplayFixedOutput << " "
        << "dmDisplayFlags: " << dm.dmDisplayFlags << " "
        << "dmNup: " << dm.dmNup << " "
        << std::endl;
    ;
}

void enum_all_monitor_settings()
{
    DEVMODE dm = { 0 };
    dm.dmSize = sizeof(dm);
    for (int iModeNum = 0; EnumDisplaySettings(NULL, iModeNum, &dm) != 0; iModeNum++) {
        show_dm(dm);
    }
}

void show_current_monitor_settings()
{
    DEVMODE dm = { 0 };
    dm.dmSize = sizeof(dm);
    EnumDisplaySettings(NULL, -1, &dm);
    show_dm(dm);
}

void read_config()
{
    auto config_file_path = std::filesystem::path(util::get_executable_directory()) / "config.json";
    if (!std::filesystem::exists(config_file_path)) {
        std::cout << "Config file not found" << std::endl;
        return;
    }
    std::ifstream f(config_file_path);
    entity::Config config;
    try {
        auto obj = nlohmann::json::parse(f);
        std::cout << obj;
    } catch (const std::exception& e) {
        std::cout << "Error parsing config file: " << e.what() << std::endl;
        return;
    }
}

void create_template_config_json(std::string value)
{
    nlohmann::json j;
    j["name"] = value;
    std::ofstream f(value + ".json");
    f << j.dump(4);
}

void write_config()
{
    std::filesystem::path exe_dir_path = util::get_executable_directory();
    entity::Config config;
    config.games.push_back({
        .name = "name",
        .settings_file_path = (exe_dir_path / "game.json").string(),
        .streaming_settings_file_path = (exe_dir_path / "streaming.json").string(),
        .native_settings_file_path = (exe_dir_path / "native.json").string(),
    });
    config.monitor.native.width = 1920;
    config.monitor.native.height = 1080;
    config.monitor.native.refresh_rate = 60;
    config.monitor.streaming.width = 1280;
    config.monitor.streaming.height = 720;
    config.monitor.streaming.refresh_rate = 60;
    auto j = nlohmann::json(config);
    std::ofstream f("config.json");
    f << j.dump(4);
    create_template_config_json("game");
    create_template_config_json("streaming");
    create_template_config_json("native");
}

void change_monitor_settings()
{
    util::change_monitor_settings(1920, 1080, 60);
}

#include "spdlog/sinks/basic_file_sink.h"
void basic_logfile_example()
{
    try {
        auto logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
        logger->info("info");
        logger->warn("warn");
        logger->error("error");
    } catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
}

int main()
{
    // basic_logfile_example();
    write_config();
}
