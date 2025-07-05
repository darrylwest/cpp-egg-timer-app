# Test Code Coverage

## Overview

Set up code coverage analysis for the C++23 project using gcov/lcov in GitHub Actions workflows.

## CMakeLists.txt Additions

```
# Set coverage flags
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()
```

Actions:

```bash
./mk clobber
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
make test
```

Generate the coverage report

```bash
lcov -capture -directory . -output-file coverage.info
lcov -remove coverage.info "/usr/*" "*/test/*" "*/tests/*" -output-file coverage.info
genhtml coverage.info -output-directory coverage_html
```

## CI/CD Github Workflow

### Implementation Steps

1. Add coverage compiler flags
   - Add `-fprofile-arcs -ftest-coverage` to compile flags
   - Add `-lgcov` to link flags

2. Install required tools in the workflow
   ```yaml
   - name: Install coverage tools
     run: |
       sudo apt-get update
       sudo apt-get install -y lcov
   ```

3. Create a workflow step to generate coverage reports
   ```yaml
   - name: Generate coverage report
     run: |
       # Build with coverage flags
       cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON .
       make
       
       # Run tests
       ctest --output-on-failure
       
       # Generate coverage report
       lcov --capture --directory . --output-file coverage.info
       lcov --remove coverage.info '/usr/*' --output-file coverage.info
       lcov --list coverage.info
   ```

4. Upload coverage reports as artifacts
   ```yaml
   - name: Upload coverage report
     uses: actions/upload-artifact@v4
     with:
       name: coverage-report
       path: coverage.info
   ```

5. (Optional) Add coverage reporting service integration
   - Consider integrating with services like Codecov or Coveralls
   - Add appropriate GitHub Actions steps for chosen service

### Configuration

Add these CMake configurations to enable coverage:

```cmake
if(ENABLE_COVERAGE)
    add_compile_options(-fprofile-arcs -ftest-coverage)
    add_link_options(-lgcov)
endif()
```

### Notes
- Coverage analysis should be run on Debug builds
- Consider excluding external dependencies and test files from coverage reports
- Regular CI builds should not include coverage to maintain build performance

### Verification
- [ ] Compiler flags are properly set
- [ ] Coverage tools are installed in workflow
- [ ] Tests run successfully with coverage enabled
- [ ] Coverage reports are generated
- [ ] Reports are properly uploaded as artifacts
- [ ] Coverage reporting service integration works (if implemented)

