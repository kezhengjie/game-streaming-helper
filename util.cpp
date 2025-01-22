#include "util.h"

#include <windows.h>
#include <stdexcept>
#include <string>

namespace util
{
    std::string get_executable_directory()
    {
        char temp[MAX_PATH];
        if (GetModuleFileNameA(NULL, temp, MAX_PATH))
        {
            std::string path(temp);
            auto last_sep_index = path.rfind('\\');
            if (last_sep_index != std::string::npos)
            {
                return path.substr(0, last_sep_index);
            }
        }
        return "";
    }

    int get_resolution_height()
    {
        return GetSystemMetrics(SM_CYSCREEN);
    }

    void change_monitor_settings(int width, int height, int refresh_rate)
    {
        DEVMODE dm;
        ZeroMemory(&dm, sizeof(dm));
        dm.dmSize = sizeof(dm);
        if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm))
        {
            dm.dmPelsWidth = width;
            dm.dmPelsHeight = height;
            dm.dmDisplayFrequency = refresh_rate;
            dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
            LONG result = ChangeDisplaySettings(&dm, 0);
            if (result != DISP_CHANGE_SUCCESSFUL)
            {
                throw std::runtime_error("Failed to change display settings,error code:" + std::to_string(result));
            }
        }
    }

    void overwrite_file(const std::filesystem::path &source, const std::filesystem::path &destination)
    {
        if (!std::filesystem::exists(source))
        {
            throw std::runtime_error(source.string() + " not exists");
        }
        if (std::filesystem::exists(destination))
        {
            std::filesystem::remove(destination);
        }
        std::filesystem::copy_file(source, destination, std::filesystem::copy_options::none);
    }
}