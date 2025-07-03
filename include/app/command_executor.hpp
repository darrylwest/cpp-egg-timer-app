#pragma once

#include <stdexcept>
#include <string>

namespace app::eggtimer {

    class CommandExecutionError : public std::runtime_error {
      public:
        explicit CommandExecutionError(const std::string& message) : std::runtime_error(message) {}
    };

    std::string execute_command(const std::string& command);

}  // namespace app::eggtimer
