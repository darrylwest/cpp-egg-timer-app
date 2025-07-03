#include <spdlog/spdlog.h>

#include <app/command_executor.hpp>
#include <array>
#include <cstdio>  // For popen, pclose

namespace app::eggtimer {

    std::string execute_command(const std::string& command) {
        std::array<char, 128> buffer;
        std::string result;
        FILE* pipe = popen(command.c_str(), "r");
        if (!pipe) {
            throw CommandExecutionError("popen() failed!");
        }
        try {
            while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
                result += buffer.data();
            }
        } catch (...) {
            pclose(pipe);
            throw;
        }
        int return_code = pclose(pipe);

        if (return_code != 0) {
            spdlog::error("Command '{}' exited with code {}", command, return_code);
            throw CommandExecutionError("Command execution failed with non-zero exit code.");
        }

        return result;
    }

}  // namespace app::eggtimer
