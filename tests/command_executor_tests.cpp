#include <catch2/catch_all.hpp>
#include <app/command_executor.hpp>

TEST_CASE("Command Executor - Successful Execution", "[command_executor]") {
    std::string output = app::eggtimer::execute_command("echo hello");
    REQUIRE(output == "hello\n");
}

TEST_CASE("Command Executor - Command Not Found", "[command_executor]") {
    REQUIRE_THROWS_AS(app::eggtimer::execute_command("non_existent_command_12345"), app::eggtimer::CommandExecutionError);
}

TEST_CASE("Command Executor - Non-Zero Exit Code", "[command_executor]") {
    REQUIRE_THROWS_AS(app::eggtimer::execute_command("false"), app::eggtimer::CommandExecutionError);
}
