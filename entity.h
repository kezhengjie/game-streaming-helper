#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include <nlohmann/json.hpp>

namespace entity {
struct Game {
    std::string name;
    std::string settings_file_path;
    std::string streaming_settings_file_path;
    std::string native_settings_file_path;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Game, name, settings_file_path, streaming_settings_file_path, native_settings_file_path)

struct MonitorSettings {
    int width;
    int height;
    int refresh_rate;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MonitorSettings, width, height, refresh_rate)

struct Monitor {
    MonitorSettings streaming;
    MonitorSettings native;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Monitor, streaming, native)

struct Config {
    std::vector<Game> games;
    Monitor monitor;

    static const Config& default_config()
    {
        static Config config {
            .games = std::vector<Game> {},
            .monitor = Monitor {
                .streaming = MonitorSettings {
                    .width = 1280,
                    .height = 720,
                    .refresh_rate = 60 },
                .native = MonitorSettings { .width = 1920, .height = 1080, .refresh_rate = 60 } }
        };
        return config;
    }
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Config, games, monitor)
}

#endif // ENTITY_H
