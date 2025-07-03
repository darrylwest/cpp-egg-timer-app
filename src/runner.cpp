#include <spdlog/spdlog.h>

#include <app/command_executor.hpp>
#include <app/runner.hpp>
#include <app/timer.hpp>

namespace app::eggtimer {

    DefaultTimerRunner::DefaultTimerRunner(int total_seconds) : m_total_seconds(total_seconds) {}

    void DefaultTimerRunner::run() {
        spdlog::info("Running default timer for {} seconds.", m_total_seconds);
        countdown(m_total_seconds);
    }

    CustomCommandRunner::CustomCommandRunner(int total_seconds, const std::string& command)
        : m_total_seconds(total_seconds), m_command(command) {}

    void CustomCommandRunner::run() {
        spdlog::info("Running custom command runner for {} seconds, command: '{}'.", m_total_seconds, m_command);
        countdown(m_total_seconds);
        try {
            std::string output = execute_command(m_command);
            spdlog::info("Command output: \n{}", output);
        } catch (const CommandExecutionError& e) {
            spdlog::error("Command execution failed: {}", e.what());
        }
    }

}  // namespace app::eggtimer
