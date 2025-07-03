//
// Created by Darryl West on 3/22/25.
//
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() function

#include <catch2/catch_all.hpp>
#include <app/eggtimer.hpp>
#include <spdlog/spdlog.h>
#include <print>
#include <termio/termio.hpp>
#include <vendor/perftimer.hpp>

perftimer::PerfTimer timer("Catch2 Unit Tests");
using namespace termio::termio;

struct MainTestSetup {

    MainTestSetup() {
        spdlog::set_level(spdlog::level::critical);

        // do any config stuff
        timer.start();
        // timer.log << "started";
    }

    ~MainTestSetup() {
        timer.stop();
        std::println("{}Tests complete...{}", green(), reset());
        timer.show_duration();
        // std::println("{}", timer.log.str());
    }
};

// put helpers here...
MainTestSetup setup;

// Tests here
TEST_CASE("Version test", "[version]") {
    const auto vers = app::eggtimer::VERSION;
    REQUIRE(vers == app::eggtimer::VERSION);
}
