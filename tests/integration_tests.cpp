#include <app/command_executor.hpp>
#include <catch2/catch_all.hpp>
#include <sstream>
#include <string>
#include <vector>

// Helper function to run the eggtimer-app with given arguments
std::string run_eggtimer_app(const std::vector<std::string>& args) {
    std::stringstream command_stream;
    command_stream << "./build/eggtimer-app";
    for (const auto& arg : args) {
        command_stream << " \"" << arg << "\"";  // Quote arguments to handle spaces
    }
    return app::eggtimer::execute_command(command_stream.str());
}

TEST_CASE("Integration Test: Basic Timer --seconds", "[integration]") {
    std::string output = run_eggtimer_app({"--seconds", "1"});
    REQUIRE(output.find("Time's up!") != std::string::npos);
    REQUIRE(output.find("Egg timer finished.") != std::string::npos);
}

TEST_CASE("Integration Test: Basic Timer --minutes", "[integration]") {
    // Note: This will take 1 minute to run. Consider using a shorter time for CI/CD.
    std::string output = run_eggtimer_app({"--minutes", "1"});
    REQUIRE(output.find("Time's up!") != std::string::npos);
    REQUIRE(output.find("Egg timer finished.") != std::string::npos);
}

TEST_CASE("Integration Test: Basic Timer --time", "[integration]") {
    std::string output = run_eggtimer_app({"--time", "0:01"});
    REQUIRE(output.find("Time's up!") != std::string::npos);
    REQUIRE(output.find("Egg timer finished.") != std::string::npos);
}

TEST_CASE("Integration Test: Dry Run --dry-run", "[integration]") {
    std::string output = run_eggtimer_app({"--seconds", "10", "--dry-run"});
    REQUIRE(output.find("dry run: 10 seconds") != std::string::npos);
    REQUIRE(output.find("Time remaining:") == std::string::npos);  // Ensure no countdown messages
}

TEST_CASE("Integration Test: Run Command - Simple Echo", "[integration]") {
    std::string output = run_eggtimer_app({"--seconds", "1", "--run-command", "echo Integration Test Output"});
    REQUIRE(output.find("Time's up!") != std::string::npos);
    REQUIRE(output.find("Integration Test Output") != std::string::npos);
}

TEST_CASE("Integration Test: Run Command - ls -l", "[integration]") {
    std::string output = run_eggtimer_app({"--seconds", "1", "--run-command", "ls -l"});
    REQUIRE(output.find("Time's up!") != std::string::npos);
    REQUIRE(output.find("total") != std::string::npos);  // Check for typical ls -l output
}

TEST_CASE("Integration Test: Invalid CLI Option", "[integration]") {
    REQUIRE_THROWS_AS(run_eggtimer_app({"--invalid-option"}), app::eggtimer::CommandExecutionError);
}

TEST_CASE("Integration Test: Help Output", "[integration]") {
    std::string output = run_eggtimer_app({"--help"});
    REQUIRE(output.find("Usage:") != std::string::npos);
    REQUIRE(output.find("-s, --seconds") != std::string::npos);
}
