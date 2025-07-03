## Plan: Enhanced Egg Timer with Alternate Runners and `std::popen`

**Goal:** Refactor the eggtimer application to support configurable "runners" (actions to perform after the timer expires) using `std::popen` for external command execution, and extract the core timer logic into its own module.

---

### Phase 1: Extract Core Timer Logic

1.  **Create `include/app/timer.hpp`:**
    *   Declare a function, e.g., `void countdown(int total_seconds);` within the `app::eggtimer` namespace. This function will contain the main countdown loop.
2.  **Create `src/timer.cpp`:**
    *   Implement `app::eggtimer::countdown(int total_seconds)`.
    *   Move the existing countdown loop and related `spdlog` messages from `src/main.cpp` into this function.
3.  **Update `src/main.cpp`:**
    *   Remove the countdown loop.
    *   Call `app::eggtimer::countdown(config.total_seconds);` after successful CLI parsing.
4.  **Update `CMakeLists.txt`:**
    *   Add `src/timer.cpp` to the `eggtimer-app` target's source files.

---

### Phase 2: Implement `std::popen` Command Execution Wrapper

1.  **Create `include/app/command_executor.hpp`:**
    *   Declare a function, e.g., `std::string execute_command(const std::string& command);` within the `app::eggtimer` namespace. This function will execute a shell command and return its standard output.
    *   Declare a custom exception class, e.g., `CommandExecutionError`, for errors during command execution (e.g., command not found, non-zero exit code).
2.  **Create `src/command_executor.cpp`:**
    *   Implement `app::eggtimer::execute_command(const std::string& command)` using `std::popen`.
    *   Handle potential errors (e.g., `popen` returning `nullptr`, non-zero exit status from `pclose`). Throw `CommandExecutionError` on failure.
    *   Capture and return the command's standard output.
3.  **Create `tests/command_executor_tests.cpp`:**
    *   Add unit tests for `app::eggtimer::execute_command`:
        *   Test successful command execution (e.g., `echo "hello"`).
        *   Test command execution with errors (e.g., non-existent command, command returning non-zero exit code).
        *   Verify captured output.
4.  **Update `CMakeLists.txt`:**
    *   Add `src/command_executor.cpp` to the `eggtimer-app` target's source files.
    *   Add `tests/command_executor_tests.cpp` to the `unit_tests` target's source files.

---

### Phase 3: Define Runner Interface and Default Timer Runner

1.  **Create `include/app/runner.hpp`:**
    *   Define an abstract base class `IRunner` within `app::eggtimer` with a pure virtual method, e.g., `virtual void run() = 0;`.
    *   Define a concrete class `DefaultTimerRunner` that inherits from `IRunner`.
    *   The constructor for `DefaultTimerRunner` will take the `total_seconds` as an argument.
    *   Implement `DefaultTimerRunner::run()` to call `app::eggtimer::countdown(total_seconds);`.
2.  **Create `src/runner.cpp`:**
    *   Implement any necessary parts of `DefaultTimerRunner` that are not in the header.
3.  **Update `app/eggtimer/cli.hpp`:**
    *   Modify the `Config` struct to include a way to specify the desired runner. For now, let's add a `std::string runner_command;` field, which will hold the command to execute for a custom runner, or be empty for the default timer.
4.  **Update `CMakeLists.txt`:**
    *   Add `src/runner.cpp` to the `eggtimer-app` target's source files.

---

### Phase 4: Integrate Runners with CLI and Main Application

1.  **Update `src/cli.cpp`:**
    *   Add a new CLI option, e.g., `--run-command <command_string>` (short `-c`), to specify an external command to run after the timer. This option will populate `config.runner_command`.
    *   Ensure that if `--run-command` is used, the timer options (`--seconds`, `--minutes`, `--time`) are still parsed to set `total_seconds`.
2.  **Update `src/main.cpp`:**
    *   After parsing the `Config` object:
        *   If `config.runner_command` is empty, create a `DefaultTimerRunner` instance and call its `run()` method.
        *   If `config.runner_command` is not empty, create a `CustomCommandRunner` (see Phase 5) instance, passing `config.runner_command` to its constructor, and call its `run()` method.
3.  **Update `tests/cli_tests.cpp`:**
    *   Add test cases for the new `--run-command` option.

---

### Phase 5: Implement Custom Command Runner

1.  **Update `include/app/runner.hpp`:**
    *   Define a concrete class `CustomCommandRunner` that inherits from `IRunner`.
    *   The constructor for `CustomCommandRunner` will take the command string as an argument.
    *   Implement `CustomCommandRunner::run()` to:
        *   Call `app::eggtimer::countdown(total_seconds);` (the timer still runs first).
        *   Then call `app::eggtimer::execute_command(command_string);` and log its output.
        *   Handle `CommandExecutionError` from `execute_command`.
2.  **Update `src/runner.cpp`:**
    *   Implement any necessary parts of `CustomCommandRunner` that are not in the header.
3.  **Update `tests/cli_tests.cpp`:**
    *   Add test cases to verify the interaction between timer options and `--run-command`.
