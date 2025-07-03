Revised Plan: Add CLI Options for Egg Timer Timeout (Modular Approach)

Goal: Implement command-line options --seconds, --minutes, and --hours to set the egg timer's timeout, storing the parsed values in a Config struct, within a dedicated cli module.

Phase 1: Define Configuration Structure and CLI Interface

1. Create `include/app/cli.hpp`:
    * Add `#pragma once`.
    * Add `#include <string>` and `#include <stdexcept>` (for potential exceptions).
    * Define a `struct Config` within the `app` namespace (e.g., `namespace app { struct Config { int total_seconds = 0; }; }`).
    * Declare a function `app::Config parse_cli_options(int argc, char** argv);` that will parse the command-line arguments and return a `Config` object.
    * Declare a custom exception class (e.g., `class CliError : public std::runtime_error`) for CLI parsing errors, to be thrown by `parse_cli_options`.

Phase 2: Implement CLI Option Parsing Logic

1. Create `src/cli.cpp`:
    * Add `#include <app/cli.hpp>`.
    * Add `#include <vendor/cxxopts.hpp>`.
    * Add `#include <spdlog/spdlog.h>` (for logging, if needed, or remove if not used).
    * Implement the `app::Config parse_cli_options(int argc, char** argv)` function:
        * Create an `cxxopts::Options` object, providing a program name and description.
        * Define the following options:
            * `--seconds` (short `-s`): `cxxopts::value<int>()`. Add a descriptive help string.
            * `--minutes` (short `-m`): `cxxopts::value<int>()`. Add a descriptive help string.
            * `--hours` (short `-h`): `cxxopts::value<std::string>()`. Add a descriptive help string.
            * `--help` (short `-?`): `cxxopts::value<bool>()`.
        * Use a `try-catch` block for `options.parse(argc, argv)`:
            * In the `catch` block for `cxxopts::exceptions::OptionException`, throw a `app::CliError` with the error message and help text.
        * Check if `--help` was requested. If so, throw a `app::CliError` with only the help text (this allows `main` to print and exit cleanly).
        * Initialize a `app::Config` object.
        * Implement logic to calculate `total_seconds` based on the provided options:
            * Prioritize `--hours`, then `--minutes`, then `--seconds`.
            * Parse the "H:M" string for `--hours` into hours and minutes, then convert to seconds.
            * Convert minutes/seconds to total seconds.
            * Add validation for positive values and reasonable ranges. If validation fails, throw a `app::CliError`.
        * Return the populated `app::Config` object.

Phase 3: Integrate CLI Module into Main Application

1. Update `src/main.cpp`:
    * Add `#include <app/cli.hpp>`.
    * In the `main` function:
        * Use a `try-catch` block around the call to `app::parse_cli_options(argc, argv)`.
        * In the `try` block, call `app::parse_cli_options` and store the returned `app::Config` object.
        * In the `catch` block for `app::CliError`, print the error message (which might just be the help text) and exit with an appropriate status code.
        * Add a temporary `spdlog::info` message to print the `total_seconds` from the `Config` struct to verify parsing.

Phase 4: Create Unit Tests for CLI Module

1. Create `tests/cli_tests.cpp`:
    * Add `#include <catch2/catch_all.hpp>`.
    * Add `#include <app/cli.hpp>`.
    * Write `TEST_CASE` blocks to test `app::parse_cli_options`:
        * Test valid combinations of `--seconds`, `--minutes`, `--hours`.
        * Test invalid inputs (e.g., non-numeric values, negative values, invalid `--hours` format).
        * Test the `--help` option.
        * Verify that `app::CliError` is thrown for expected error conditions.

Phase 5: Update CMake Configuration

1. Update `CMakeLists.txt`:
    * Add `src/cli.cpp` to the `eggtimer-app` target's source files.
    * Add `tests/cli_tests.cpp` to the `unit_tests` target's source files. (Alternatively, create a new `cli_tests` executable target if preferred, but for now, adding to `unit_tests` is simpler).