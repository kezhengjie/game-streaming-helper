#ifndef __UTIL_H__
#define __UTIL_H__

#include <windows.h>
#include <string>

namespace util
{
    std::string get_executable_directory();
    int get_resolution_height();
    void change_monitor_settings(int width, int height, int refresh_rate);
}

#endif