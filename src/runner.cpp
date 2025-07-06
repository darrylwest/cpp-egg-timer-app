#include <spdlog/spdlog.h>

#include <app/command_executor.hpp>
#include <app/runner.hpp>
#include <app/timer.hpp>
#include <print>

namespace app::eggtimer {

    Runner::Runner(const Config& config) : context(config) {}

    void Runner::run() {
        auto seconds = context.total_seconds;
        auto cmd = context.runner_command;

        spdlog::info("Running default timer for {} seconds.", seconds);
        countdown(seconds, context.quiet);
        try {
            std::string output = execute_command(cmd);
            spdlog::info("Command output: \n{}", output);
            std::println("{}", output);
        } catch (const CommandExecutionError& e) {
            spdlog::error("Command execution failed: {}", e.what());
        }
    }
}  // namespace app::eggtimer
