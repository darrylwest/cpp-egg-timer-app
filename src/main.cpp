//
// dpw
//

#include <spdlog/spdlog.h>

#include <app/eggtimer.hpp>
#include <print>
#include <string>
#include <termio/termio.hpp>

constexpr std::string_view BANNER = R"(
 _______ __                _______ __               __                _______
|_     _|__|.-----.--.--. |     __|  |_.---.-.----.|  |_.-----.----. |   _   |.-----.-----.
  |   | |  ||     |  |  | |__     |   _|  _  |   _||   _|  -__|   _| |       ||  _  |  _  |
  |___| |__||__|__|___  | |_______|____|___._|__|  |____|_____|__|   |___|___||   __|   __|
                  |_____|                                                     |__|  |__|
)";

int main() {
    using namespace termio::termio;

    std::println("{}{}\n{}Version: {}{}", green(), BANNER, yellow(), app::eggtimer::VERSION,
                 reset()) constexpr auto lang
        = "c++";
    spdlog::info("Hello and welcome to {} eggtimer application, version: {}", lang,
                 app::eggtimer::VERSION);

    return 0;
}
