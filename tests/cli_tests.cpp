#include <catch2/catch_all.hpp>
#include <app/cli.hpp>

TEST_CASE("CLI Option Parsing - Seconds", "[cli]") {
    char* argv[] = {(char*)"eggtimer-app", (char*)"--seconds", (char*)"30", nullptr};
    int argc = sizeof(argv) / sizeof(argv[0]) - 1;

    app::eggtimer::Config config = app::eggtimer::parse_cli_options(argc, argv);
    REQUIRE(config.total_seconds == 30);
}

TEST_CASE("CLI Option Parsing - Minutes", "[cli]") {
    char* argv[] = {(char*)"eggtimer-app", (char*)"--minutes", (char*)"2", nullptr};
    int argc = sizeof(argv) / sizeof(argv[0]) - 1;

    app::eggtimer::Config config = app::eggtimer::parse_cli_options(argc, argv);
    REQUIRE(config.total_seconds == 120);
}

TEST_CASE("CLI Option Parsing - Hours", "[cli]") {
    char* argv[] = {(char*)"eggtimer-app", (char*)"--hours", (char*)"1:30", nullptr};
    int argc = sizeof(argv) / sizeof(argv[0]) - 1;

    app::eggtimer::Config config = app::eggtimer::parse_cli_options(argc, argv);
    REQUIRE(config.total_seconds == 5400);
}

TEST_CASE("CLI Option Parsing - Help", "[cli]") {
    char* argv[] = {(char*)"eggtimer-app", (char*)"--help", nullptr};
    int argc = sizeof(argv) / sizeof(argv[0]) - 1;

    auto config = app::eggtimer::parse_cli_options(argc, argv);
    REQUIRE(config.dry_run);
}

TEST_CASE("CLI Option Parsing - Invalid Hours Format", "[cli]") {
    char* argv[] = {(char*)"eggtimer-app", (char*)"--hours", (char*)"1-30", nullptr};
    int argc = sizeof(argv) / sizeof(argv[0]) - 1;

    REQUIRE_THROWS_AS(app::eggtimer::parse_cli_options(argc, argv), app::eggtimer::CliError);
}

TEST_CASE("CLI Option Parsing - Negative Timeout", "[cli]") {
    char* argv[] = {(char*)"eggtimer-app", (char*)"--seconds", (char*)"-10", nullptr};
    int argc = sizeof(argv) / sizeof(argv[0]) - 1;

    REQUIRE_THROWS_AS(app::eggtimer::parse_cli_options(argc, argv), app::eggtimer::CliError);
}
