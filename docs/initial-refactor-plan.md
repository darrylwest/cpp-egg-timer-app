  Here is the plan:

  Refactoring Plan: Rename 'tiny' to 'eggtimer'

  Phase 1: Rename Files and Directories


   1. Rename `include/app/tiny.hpp`:
       * Change include/app/tiny.hpp to include/app/eggtimer.hpp.

  Phase 2: Update File Contents


   1. Update `CMakeLists.txt`:
       * Change project(TinyApplication ...) to project(EggTimerApplication ...).
       * Change add_executable(tiny-app ...) to add_executable(eggtimer-app ...).
       * Update any other occurrences of "tiny" related to the application name or internal variables.


   2. Update `src/main.cpp`:
       * Change #include "app/tiny.hpp" to #include "app/eggtimer.hpp".
       * Update any class names, function names, or variable names that use "tiny" (e.g., TinyApp to EggTimerApp).


   3. Update `include/app/eggtimer.hpp` (formerly `tiny.hpp`):
       * Update class names, namespace names, or any other identifiers within this file that contain "tiny" to "eggtimer".


   4. Update `.github/workflows/build-test-run.yml`:
       * Change ${{github.workspace}}/build/tiny-app to ${{github.workspace}}/build/eggtimer-app in the "Run" step.
       * Change echo "=== Running tiny-app ===" to echo "=== Running eggtimer-app ===".


   5. Update `README.md` (if applicable):
       * Search for and replace "tiny" with "eggtimer" in any project descriptions, usage instructions, or examples.


   6. Update `docs/project-plan.md` (if applicable):
       * Search for and replace "tiny" with "eggtimer" in any project descriptions or references.

   7. Update `GEMINI.md` (if applicable):
       * Search for and replace "tiny" with "eggtimer" in any project descriptions or references.


  Phase 3: Verification

   1. Run local build: Execute ./mk all to ensure the project compiles successfully with the new names.
   2. Run tests: Execute ./build/unit_tests to confirm tests still pass.


  This plan covers the most likely locations for the "tiny" string. I will proceed with these changes once you approve.


