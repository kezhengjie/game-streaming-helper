#include "Windows.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "util.h"
#include <filesystem>
#include <nlohmann/json.hpp>
#include "config.h"

void show_dm(const DEVMODE &dm)
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
    DEVMODE dm = {0};
    dm.dmSize = sizeof(dm);
    for (int iModeNum = 0; EnumDisplaySettings(NULL, iModeNum, &dm) != 0; iModeNum++)
    {
        show_dm(dm);
    }
}

void show_current_monitor_settings()
{
    DEVMODE dm = {0};
    dm.dmSize = sizeof(dm);
    EnumDisplaySettings(NULL, -1, &dm);
    show_dm(dm);
}

void read_config()
{
    auto config_file_path = std::filesystem::path(util::get_executable_directory()) / "config.json";
    if (!std::filesystem::exists(config_file_path))
    {
        std::cout << "Config file not found" << std::endl;
        return;
    }
    std::ifstream f(config_file_path);
    Config config;
    try
    {
        auto obj = nlohmann::json::parse(f);
        std::cout << obj;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error parsing config file: " << e.what() << std::endl;
        return;
    }
}

void change_monitor_settings()
{
    util::change_monitor_settings(1920, 1080, 60);
}

int main()
{
    read_config();
}