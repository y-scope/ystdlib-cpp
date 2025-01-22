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
Before submitting a pull request, ensure you’ve run the linting commands below and either fixed any
violations or suppressed the warnings.

To run all linting checks:
```shell
task lint:check
```

To run all linting checks AND automatically fix any fixable issues:
```shell
task lint:fix
```

To see which linters are available and run the linters for a specific file type, run
```shell
task -a
```
and check for all tasks under the `lint` namespace (marked with the `lint:` prefix).

[Task]: https://taskfile.dev
