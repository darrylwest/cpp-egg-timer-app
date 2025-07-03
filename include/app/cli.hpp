#pragma once

#include <stdexcept>
#include <string>

namespace app::eggtimer {

    struct Config {
        int total_seconds = 0;
    };

    class CliError : public std::runtime_error {
      public:
        explicit CliError(const std::string& message) : std::runtime_error(message) {}
    };

    Config parse_cli_options(int argc, char** argv);

}  // namespace app::eggtimer
