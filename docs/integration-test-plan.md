## Plan: Add Integration Tests for `eggtimer-app`

**Goal:** Create integration tests that execute the compiled `eggtimer-app` with different command-line arguments, including `--seconds`, `--minutes`, `--time`, `--dry-run`, and `--run-command`, and verify the application's output and exit code.

---

### Phase 1: Define Integration Test Framework/Approach

1.  **Leverage `app::eggtimer::execute_command`:** We will use the existing `app::eggtimer::execute_command` function from `app/command_executor.hpp` to run the `eggtimer-app` executable. This function already captures stdout and throws `CommandExecutionError` for non-zero exit codes, which is suitable for testing expected failures (e.g., invalid CLI arguments).

---

### Phase 2: Create Integration Test File

1.  **Create `tests/integration_tests.cpp`:**
    *   Include necessary headers: `<catch2/catch_all.hpp>`, `<app/command_executor.hpp>`, `<string>`, `<vector>`, `<sstream>`.
    *   Define a helper function, `std::string run_eggtimer_app(const std::vector<std::string>& args)`:
        *   This function will construct the full command string, starting with `./build/eggtimer-app`.
        *   It will append the provided `args` to the command string.
        *   It will then call `app::eggtimer::execute_command` with the constructed command.
        *   It will return the captured `stdout`.

---

### Phase 3: Implement Integration Test Cases

1.  **Test Case: Basic Timer (`--seconds`)**
    *   **Command:** `./build/eggtimer-app --seconds 1`
    *   **Verification:** Check that the output contains "Time's up!" and "Egg timer finished."

2.  **Test Case: Basic Timer (`--minutes`)**
    *   **Command:** `./build/eggtimer-app --minutes 1`
    *   **Verification:** Similar to `--seconds` test.

3.  **Test Case: Basic Timer (`--time`)**
    *   **Command:** `./build/eggtimer-app --time 0:01`
    *   **Verification:** Similar to `--seconds` test.

4.  **Test Case: Dry Run (`--dry-run`)**
    *   **Command:** `./build/eggtimer-app --seconds 10 --dry-run`
    *   **Verification:** Check that the output contains "dry run: 10 seconds". Ensure the timer does not actually count down (implicitly by checking for the "dry run" message and absence of countdown messages).

5.  **Test Case: Run Command (`--run-command`) - Simple Echo**
    *   **Command:** `./build/eggtimer-app --seconds 1 --run-command "echo Integration Test Output"`
    *   **Verification:** Check that the output contains "Time's up!" and "Integration Test Output".

6.  **Test Case: Run Command (`--run-command`) - `ls -l`**
    *   **Command:** `./build/eggtimer-app --seconds 1 --run-command "ls -l"`
    *   **Verification:** Check that the output contains "Time's up!" and typical `ls -l` output (e.g., "total", "drwxr-xr-x").

7.  **Test Case: Invalid CLI Option (e.g., unknown option)**
    *   **Command:** `./build/eggtimer-app --invalid-option`
    *   **Verification:** Expect `app::eggtimer::CommandExecutionError` to be thrown by `run_eggtimer_app` (because `eggtimer-app` will exit with a non-zero code). Check the error message from `CommandExecutionError` for "CLI Error" or similar.

8.  **Test Case: Help Output (`--help`)**
    *   **Command:** `./build/eggtimer-app --help`
    *   **Verification:** Check that the output contains the expected help text (e.g., "Usage:", "-s, --seconds").

---

### Phase 4: Update CMake Configuration

1.  **Update `CMakeLists.txt`:**
    *   Add `tests/integration_tests.cpp` to the `unit_tests` target. (For simplicity, we'll add it to the existing `unit_tests` executable. In a larger project, a dedicated `integration_tests` executable might be created).
