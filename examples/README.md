# Examples

The example program `linking-tests` references all of ystdlib's library targets to ensure they can
be installed and linked correctly.

## Building

### Task

To build the examples, run one of the following task commands:

```shell
# debug build
task build:examples-debug

# release build
task build:examples-release
```

### CMake

First, ensure ystdlib has been installed. For example, after
[building ystdlib](../README.md#building), [install it](../README.md#installing) by running:

```shell
cmake --install "./build" --prefix "./build/examples/ystdlib"
```

To build the examples, run:

```shell
cmake -S "./examples" -B "./build/examples" -Dystdlib_ROOT="./build/examples/ystdlib"

cmake --build "./build/examples"
```

Setting `ystdlib_ROOT` is not necessary if `ystdlib` is installed on a path CMake searches by
default.

## Running

Run the example program as follows:

```shell
./build/examples/debug/linking-tests
```

On success, the exit code will be 0 with no output printed.
