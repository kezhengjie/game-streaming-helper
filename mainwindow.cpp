#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <windows.h>
//
#include "entity.h"
#include "util.h"
#include <filesystem>
#include <fstream>
#include <functional>
#include <vector>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

struct Logger {
protected:
    Logger()
    {
        file_logger_ = spdlog::basic_logger_mt("log", (std::filesystem::path(util::get_executable_directory()) / "game-streaming-helper.log").string());
        file_logger_->set_pattern(get_pattern());
        spdlog::set_pattern(get_pattern());
    }
    ~Logger() { }

    static Logger& get_instance()
    {
        static Logger global_logger;
        return global_logger;
    }

public:
    template <typename... Args>
    static void info(Args&&... args)
    {
        spdlog::info(std::forward<Args>(args)...);
        Logger::get_instance().file_logger_->info(std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void error(Args&&... args)
    {
        spdlog::error(std::forward<Args>(args)...);
        Logger::get_instance().file_logger_->error(std::forward<Args>(args)...);
    }

protected:
    static std::string get_pattern()
    {
        return "[%Y-%m-%d %H:%M:%S.%e] [%l] %v";
    }
    decltype(spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt")) file_logger_;
};

void apply_game_settings(const std::vector<entity::Game> games, std::function<std::string(const entity::Game&)> game_settings_file_getter)
{
    for (const auto& game : games) {
        auto applied_game_settings_file_path = std::filesystem::path(game_settings_file_getter(game));
        auto game_settings_file_path = std::filesystem::path(game.settings_file_path);
        if (std::filesystem::exists(applied_game_settings_file_path)) {
            try {
                util::overwrite_file(applied_game_settings_file_path, game_settings_file_path);
            } catch (const std::exception& e) {
                Logger::error("Error applying game settings: {}", e.what());
            }
        } else {
            Logger::error("{} not exists", applied_game_settings_file_path.string());
        }
    }
}

void apply_native_settings(const entity::Config& config)
{
    util::change_monitor_settings(config.monitor.native.width, config.monitor.native.height, config.monitor.native.refresh_rate);
    apply_game_settings(config.games, [](const entity::Game& game) { return game.native_settings_file_path; });
}

void apply_streaming_settings(const entity::Config& config)
{
    util::change_monitor_settings(config.monitor.streaming.width, config.monitor.streaming.height, config.monitor.streaming.refresh_rate);
    apply_game_settings(config.games, [](const entity::Game& game) { return game.streaming_settings_file_path; });
}

int switch_enviroment()
{
    auto config_file_path = std::filesystem::path(util::get_executable_directory()) / "config.json";
    if (!std::filesystem::exists(config_file_path)) {
        Logger::error("{} not found", config_file_path.string());
        return 1;
    }
    std::ifstream f(config_file_path);
    entity::Config config;
    try {
        config = nlohmann::json::parse(f);
    } catch (const std::exception& e) {
        Logger::error("Error parsing config file: {}", std::string(e.what()));
        return 1;
    }
    auto height = util::get_resolution_height();
    if (height < config.monitor.native.height) {
        apply_native_settings(config);
    } else {
        apply_streaming_settings(config);
    }
    return 0;
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect(ui->pushButton, &QPushButton::clicked, this, []() -> void { switch_enviroment(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}
