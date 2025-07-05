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

std::string capture_stdout(const std::function<void()>& func) {
    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());  // Redirect std::cout

    func();  // Execute function that prints to stdout

    std::cout.rdbuf(old_cout);  // Restore std::cout
    return oss.str();
}

int main(int argc, char** argv) {
    using namespace termio::termio;
    using namespace std::chrono;

    std::println("{}{}\n{}Version: {}{}", green(), BANNER, yellow(), app::eggtimer::VERSION, reset());
    // capture_stdout([]() { });

    try {
        app::eggtimer::Config config = app::eggtimer::parse_cli_options(argc, argv);

        spdlog::set_level(spdlog::level::err);

        if (config.dry_run) {
            spdlog::info("dry run: {} seconds", config.total_seconds);
            return 0;
        }

        spdlog::info("Parsed timeout: {} seconds", config.total_seconds);

        app::eggtimer::Runner default_runner(config);
        default_runner.run();
    } catch (const app::eggtimer::CliError& e) {
        spdlog::error("CLI Error: {}", e.what());
        return 1;
    }
}
