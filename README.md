# ystdlib-cpp
An open-source C++ library developed and used at YScope.

# Usage

## Via CMake's add_subdirectory()
> Note: this is not accurate in this branch, which is a work in progress to use ystdlib-cpp as a
CMake library

Clone `ystdlib-cpp` into your project. Then, in your project's `CMakeLists.txt`, add the following:
```cmake
# Set `ystdlib_BUILD_TESTING` to an accepted `FALSE` class value to skip building unit tests.
# option(ystdlib_BUILD_TESTING "" OFF)
add_subdirectory(/path/to/ystdlib-cpp EXCLUDE_FROM_ALL)
target_link_libraries(<target_name> <link_options>
    ystdlib::<lib_1> ystdlib::<lib_2> ... ystdlib::<lib_N>
    # other libs...
)
```
Ensure that `ystdlib-cpp` is either within a subdirectory of the folder containing `CMakeLists.txt`
or at the same level.

# Contributing
Follow the steps below to develop and contribute to the project.

## Requirements
* Python 3.10 or higher
* [Task] 3.40.0 or higher

## Set up
Initialize and update submodules:
```shell
git submodule update --init --recursive
```

If you want to open the project in an IDE, run the following command to install any necessary
dependencies from source:
```shell
task deps:install-all
```

## Building
To build all targets:
```shell
task build:all
```

To build an executable containing all unit tests:
```shell
task build:unit-test-all
```

To build an executable containing a single library's unit tests:
```shell
task build:unit-test-<lib_name>
```

## Testing
To build and run all unit tests:
```shell
task test-all
```

To build and run unit tests for a specific library:
```shell
task test-<lib_name>
```

When generating a testing target, the CMake variable `BUILD_TESTING` is followed (unless overruled
by setting `ystdlib_BUILD_TESTING` to false). By default, if built as a top-level project,
`BUILD_TESTING` is set to true and unit tests are built.

## Linting
Before submitting a pull request, ensure you’ve run the linting commands below and have fixed all
violations and suppressed all warnings.

To run all linting checks:
```shell
task lint:check
```

To run all linting checks AND fix some violations:
```shell
task lint:fix
```

To see how to run a subset of linters for a specific file type:
```shell
task -a
```
Look for all tasks under the `lint` namespace (identified by the `lint:` prefix).

[Task]: https://taskfile.dev
