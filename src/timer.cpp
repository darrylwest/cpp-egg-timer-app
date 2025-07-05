#include <spdlog/spdlog.h>

#include <app/timer.hpp>
#include <chrono>
#include <iostream>
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
        if (!quiet) {
            std::cout << "Starting egg timer for " << total_seconds << " seconds..." << '\n';
        }

        for (int i = total_seconds; i > 0; --i) {
            if (i % 10 == 0) {
                if (!quiet) {
                    std::cout << "\n" << yellow() << "Time remaining: " << i << " seconds" << reset();
                }
            }
            if (!quiet) {
                std::cout << "." << std::flush;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        if (!quiet) {
            std::cout << "\n" << green() << "Time's up!" << reset() << '\n';
        }
        spdlog::info("Egg timer finished.");
    }

}  // namespace app::eggtimer
