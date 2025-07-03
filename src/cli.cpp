#include <spdlog/spdlog.h>

#include <app/cli.hpp>
#include <vendor/cxxopts.hpp>
#include <iostream>

namespace app::eggtimer {

    Config parse_cli_options(int argc, char** argv) {
        Config config;

        try {
            cxxopts::Options options("eggtimer-app", "Egg Timer Application");

            options.add_options()("s,seconds", "Timeout in seconds", cxxopts::value<int>())(
                "m,minutes", "Timeout in minutes", cxxopts::value<int>())(
                "t,time", "Timeout in hours (H:M format)", cxxopts::value<std::string>())
                ("d,dry-run", "Dry run mode", cxxopts::value<bool>()->default_value("false"))
                ("h,help", "Print help");

            auto result = options.parse(argc, argv);

            if (result.count("help")) {
                std::cout << options.help() << '\n';
                config.dry_run = true;
                return config;
            }

            if (result.count("dry-run")) {
                config.dry_run = result["dry-run"].as<bool>();
            }

            if (result.count("time")) {
                std::string hours_str = result["time"].as<std::string>();
                size_t colon_pos = hours_str.find(':');
                if (colon_pos == std::string::npos) {
                    throw CliError("Invalid --hours format. Use H:M.");
                }
                int hours = std::stoi(hours_str.substr(0, colon_pos));
                int minutes = std::stoi(hours_str.substr(colon_pos + 1));
                config.total_seconds = (hours * 3600) + (minutes * 60);
            } else if (result.count("minutes")) {
                config.total_seconds = result["minutes"].as<int>() * 60;
            } else if (result.count("seconds")) {
                config.total_seconds = result["seconds"].as<int>();
            }

            if (config.total_seconds < 0) {
                throw CliError("Timeout value cannot be negative.");
            }

        } catch (const cxxopts::OptionException& e) {
            throw CliError(std::string("Error parsing options: ") + e.what());
        }

        return config;
    }

}  // namespace app::eggtimer
