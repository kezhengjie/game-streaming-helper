#ifndef __UTIL_H__
#define __UTIL_H__

#include <windows.h>
#include <string>
#include <filesystem>
#include "entity.h"
#include <set>

namespace util
{
    std::string get_executable_directory();
    int get_resolution_height();
    void change_monitor_settings(int width, int height, int refresh_rate);
    void overwrite_file(const std::filesystem::path &source, const std::filesystem::path &destination);
    std::set<entity::MonitorSettings> get_monitor_settings();
}

#endif