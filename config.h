#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <vector>

#include "game.h"

struct Monitor
{
    int width;
    int height;
    int refresh_rate;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Monitor, width, height, refresh_rate)

struct Config
{
    std::vector<Game> games;
    Monitor streaming_monitor_settings;
    Monitor native_monitor_settings;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Config, games, streaming_monitor_settings, native_monitor_settings)

#endif
