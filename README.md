# ystdlib

An open-source C++ library developed and used at YScope.

# Usage

## Via CMake's `find_package`

First, [install](#installing-header) `ystdlib` onto your system. Then, in your project's `CMakeLists.txt`,
add the following:

```cmake
# If `BUILD_TESTING` is set, set `ystdlib_BUILD_TESTING` to an accepted `FALSE` class value to skip
# building ystdlib's unit tests.
# option(ystdlib_BUILD_TESTING "" OFF)
# If ystdlib is not installed to a path that is searched by default, set `ystdlib_ROOT` to manually
# specify the location.
# set(ystdlib_ROOT "<PATH_TO_INSTALLATION>")
find_package(ystdlib REQUIRED)
target_link_libraries(<target_name> <link_options>
    ystdlib::<lib_1> ystdlib::<lib_2> ... ystdlib::<lib_N>
    # other libs...
)
```

# Contributing
Follow the steps below to develop and contribute to the project.

## Requirements

* CMake 3.23 or higher
* Python 3.10 or higher
* [Task] 3.40.0 or higher
* [uv] 0.7.10 or higher

## Set up
Initialize and update submodules:
```shell
git submodule update --init --recursive
```

If you want to open the project in an IDE, run the following command to install any necessary
dependencies from source:

```shell
task deps:all
```

## Building

To build all libraries (targets) run:

```shell
task build:build-all-release
```

To build a single library (target) use the format:

```shell
task build:build-<target>-<build type>
e.g.:
task build:build-error_handling-release
```

## Installing {#installing-header}

To build and install ystdlib run:

```shell
task build:install-all-release INSTALL_PREFIX="/install/prefix/path"
```

To build and install a single library (target) use the format:

```shell
task build:install-<target>-<build type> INSTALL_PREFIX="<prefix path>"
e.g.:
task build:install-error_handling-release
```

## Testing

To build and run all unit tests use:

```shell
task test:test-all-debug
```

To build and run the unit tests for a single library (target) use the format:

```shell
task test:test-<target>-<build type>
e.g.:
task test:test-error_handling-release
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
[uv]: https://docs.astral.sh/uv
