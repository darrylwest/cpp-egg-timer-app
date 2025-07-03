//
// dpw
//

#include <spdlog/spdlog.h>

#include <app/eggtimer.hpp>
#include <chrono>
#include <print>
#include <string>
#include <termio/termio.hpp>
#include <thread>

constexpr std::string_view BANNER = R"(
 _______                    _______ __                      
|    ___|.-----.-----._____|_     _|__|.--------.-----.----.
|    ___||  _  |  _  |______||   | |  ||        |  -__|   _|
|_______||___  |___  |       |___| |__||__|__|__|_____|__|  
         |_____|_____|                                      
)";

#include <app/cli.hpp>
#include <app/runner.hpp>

int main(int argc, char** argv) {
    using namespace termio::termio;
    using namespace std::chrono;

    std::println("{}{}\n{}Version: {}{}", green(), BANNER, yellow(), app::eggtimer::VERSION, reset());

    try {
        app::eggtimer::Config config = app::eggtimer::parse_cli_options(argc, argv);
        if (config.dry_run) {
            spdlog::info("dry run: {} seconds", config.total_seconds);
            return 0;
        }

        spdlog::info("Parsed timeout: {} seconds", config.total_seconds);

        if (config.runner_command.empty()) {
            app::eggtimer::DefaultTimerRunner default_runner(config.total_seconds);
            default_runner.run();
        } else {
            app::eggtimer::CustomCommandRunner custom_runner(config.total_seconds, config.runner_command);
            custom_runner.run();
        }
    } catch (const app::eggtimer::CliError& e) {
        spdlog::error("CLI Error: {}", e.what());
        return 1;
    }
}
