#pragma once

#include <stdexcept>
#include <string>

namespace app::eggtimer {

    constexpr int DEFAULT_SECONDS = 300;
    static constexpr std::string_view DEFAULT_RUNNER_COMMAND = "afplay /System/Library/Sounds/Funk.aiff";

    struct Config {
        int total_seconds = DEFAULT_SECONDS;
        bool dry_run = false;
        std::string runner_command;
    };

    class CliError : public std::runtime_error {
      public:
        explicit CliError(const std::string& message) : std::runtime_error(message) {}
    };

    Config parse_cli_options(int argc, char** argv);

}  // namespace app::eggtimer
