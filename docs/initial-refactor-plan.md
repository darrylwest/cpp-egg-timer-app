Here is the plan:

Refactoring Plan: Rename 'tiny' to 'eggtimer'

Phase 1: Rename Files and Directories

1. Rename `include/app/tiny.hpp`:
    * Change `include/app/tiny.hpp` to `include/app/eggtimer.hpp`.

Phase 2: Update File Contents

1. Update `CMakeLists.txt`:
    * Change `project(TinyApplication ...)` to `project(EggTimerApplication ...)`.
    * Change `add_executable(tiny-app ...)` to `add_executable(eggtimer-app ...)`.
    * Change `foreach(target tiny-app unit_tests)` to `foreach(target eggtimer-app unit_tests)`.
    * Update any other occurrences of "tiny" related to the application name or internal variables.

2. Update `src/main.cpp`:
    * Change `#include "app/tiny.hpp"` to `#include "app/eggtimer.hpp"`.
    * Update any class names, function names, or variable names that use "tiny" (e.g., `TinyApp` to `EggTimerApp`).

3. Update `include/app/eggtimer.hpp` (formerly `tiny.hpp`):
    * Update class names, namespace names, or any other identifiers within this file that contain "tiny" to "eggtimer".

4. Update `.github/workflows/build-test-run.yml`:
    * Change `${{github.workspace}}/build/tiny-app` to `${{github.workspace}}/build/eggtimer-app` in the "Run" step.
    * Change `echo "=== Running tiny-app ==="` to `echo "=== Running eggtimer-app ==="`.

5. Update `README.md`:
    * Search for and replace "Tiny Application Starter" with "EggTimer Application Starter".
    * Update the file structure section to reflect `eggtimer.hpp` and `eggtimer-app`.
    * Search for and replace "tiny" with "eggtimer" in any project descriptions, usage instructions, or examples.

6. Update `docs/project-plan.md`:
    * Search for and replace "tiny" with "eggtimer" in any project descriptions or references.

7. Update `GEMINI.md`:
    * Update the title from "Gemini CLI Learnings for this project" to "Gemini CLI Learnings for egg-timer project".
    * Expand the "Local Development Workflow" section to detail the `mk` script's capabilities.

8. Update `mk` script:
    * Change `export project=tiny-app` to `export project=eggtimer-app`.

Phase 3: Verification

1. Run local build: Execute `./mk all` to ensure the project compiles successfully with the new names.
2. Run tests: Execute `./build/unit_tests` to confirm tests still pass.

This plan covers the most likely locations for the "tiny" string. I will proceed with these changes once you approve.