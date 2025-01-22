ystdlib-cpp
===================================
An open-source C++ library developed and used at YScope.

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

## Linting
Before submitting a pull request, ensure you’ve run the linting commands below to fix violations or
suppress warnings.

To run all linting checks:
```shell
task lint:check
```

To run all linting checks AND automatically fix any fixable issues:
```shell
task lint:fix
```

To see which linters are available and how to run a specific linter:
```shell
task --list-all
```
[Task]: https://taskfile.dev
