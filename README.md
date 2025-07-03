# Egg Timer Application

```
 _______                    _______ __                      
|    ___|.-----.-----._____|_     _|__|.--------.-----.----.
|    ___||  _  |  _  |______||   | |  ||        |  -__|   _|
|_______||___  |___  |       |___| |__||__|__|__|_____|__|  
         |_____|_____|                                      
```

This is a simple command-line egg timer application with configurable timeouts and the ability to execute custom commands upon completion.

## Features

*   **Configurable Timer:** Set the countdown duration in seconds, minutes, or hours (H:M format).
*   **Dry Run Mode:** Test your timer settings without actually running the countdown or executing commands.
*   **Custom Runners:** Execute any shell command or script after the timer expires.
*   **Clear Output:** Provides visual feedback during the countdown and reports command output.

## Usage

To run the egg timer, use the `eggtimer-app` executable located in the `build/` directory after compiling the project.

### Basic Usage

Run the timer with the default timeout (300 seconds):

```bash
./build/eggtimer-app
```

### Setting Timeout

Set the timer duration using `--seconds`, `--minutes`, or `--time` (for hours and minutes):

*   **Seconds:**
    ```bash
    ./build/eggtimer-app --seconds 30
    ```

*   **Minutes:**
    ```bash
    ./build/eggtimer-app --minutes 5
    ```

*   **Hours and Minutes:**
    ```bash
    ./build/eggtimer-app --time 1:30
    ```

### Dry Run Mode

Use the `--dry-run` (or `-d`) option to see the parsed timeout without starting the countdown:

```bash
./build/eggtimer-app --seconds 60 --dry-run
```

### Custom Command Execution

Specify a command to run after the timer completes using `--run-command` (or `-c`). The timer will run first, and then the specified command will be executed.

*   **Play a sound (macOS example):**
    ```bash
    ./build/eggtimer-app --minutes 1 --run-command "afplay /System/Library/Sounds/Funk.aiff"
    ```

*   **Display a message:**
    ```bash
    ./build/eggtimer-app --seconds 5 --run-command "echo 'Time is up! Take a break!'"
    ```

*   **Run a script:**
    ```bash
    ./build/eggtimer-app --minutes 2 --run-command "/path/to/your/script.sh"
    ```

### Display Help

To see all available command-line options and their descriptions:

```bash
./build/eggtimer-app --help
```

## Build and Run

This project uses CMake for its build system and provides a convenient `mk` bash script for common development tasks.

*   **Full Build (including CMake configuration):**
    ```bash
    ./mk all
    ```

*   **Build and Run Unit Tests (after initial CMake configuration):**
    ```bash
    ./mk build test
    ```

*   **Run Integration Tests (explicitly):**
    ```bash
    ./mk integration
    ```

*   **Run the application (with default options):**
    ```bash
    ./mk run
    ```

---

**Note:** _Approximately 95% of this project's code, including planning sessions (see docs folder), was generated with the assistance of [gemini](https://github.com/google-gemini/gemini-cli)._

###### dpw | 2025-07-03 | 81NRnMY6T63H
