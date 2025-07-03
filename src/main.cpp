//
// dpw
//

#include <spdlog/spdlog.h>

#include <chrono>
#include <thread>
#include <app/eggtimer.hpp>
#include <print>
#include <string>
#include <termio/termio.hpp>

constexpr std::string_view BANNER = R"(
 _______                    _______ __                      
|    ___|.-----.-----._____|_     _|__|.--------.-----.----.
|    ___||  _  |  _  |______||   | |  ||        |  -__|   _|
|_______||___  |___  |       |___| |__||__|__|__|_____|__|  
         |_____|_____|                                      
)";

#include <app/cli.hpp>

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
        auto tick_time = 1s;

        std::cout << "Timer version: " << VERSION << " started..." << std::endl;
        auto start = high_resolution_clock::now();

        auto limit = config.total_seconds;

        for (auto i = 0; i < limit; i++) {
            if (i % 10 == 0) {
                // std::cout << t << " seconds, " << (limit * 10) - t << " remaining..." << std::endl;
                std::print("\n{} seconds, {} remaining", i, limit - i);
            }
            std::print(".");
            std::this_thread::sleep_for(tick_time * 1);
        }

        auto stop = high_resolution_clock::now();

        duration<float> duration = stop - start;

        std::string runner = "afplay /System/Library/Sounds/Funk.aiff";
        std::println("Timer complete: {} seconds, running: {}", duration.count(), runner);

        return std::system(runner.c_str());
    } catch (const app::eggtimer::CliError& e) {
        spdlog::error("CLI Error: {}", e.what());
        return 1;
    }
}

