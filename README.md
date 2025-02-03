ystdlib-cpp
===================================
An open-source C++ library developed and used at YScope.

# Usage
Clone `ystdlib-cpp` into your project. Then, in your project's `CMakeLists.txt`, add the following:
```cmake
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

# Building
To build all targets in `ystdlib-cpp`:
```shell
task build:target
```

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
