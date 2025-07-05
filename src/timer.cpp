#include <spdlog/spdlog.h>

#include <app/timer.hpp>
#include <chrono>
#include <print>
#include <termio/termio.hpp>
#include <thread>

namespace app::eggtimer {

    void countdown(int total_seconds, bool quiet) {
        using namespace termio::termio;

        if (total_seconds <= 0) {
            spdlog::info("Timer not set or set to 0 seconds. Exiting.");
            return;
        }

        spdlog::info("Starting egg timer for {} seconds...", total_seconds);
        if (!quiet) std::println("Starting egg timer for {} seconds...", total_seconds);

        for (int i = total_seconds; i > 0; --i) {
            if (i % 10 == 0) {
                if (!quiet) std::print("\n{}Time remaining: {} seconds{}", yellow(), i, reset());
            }
            if (!quiet) std::print(".");

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::println("\n{}Time's up!{}", green(), reset());
        spdlog::info("Egg timer finished.");
    }

}  // namespace app::eggtimer
