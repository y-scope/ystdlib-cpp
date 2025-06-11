# Examples

The example program `linking-tests` references all of ystdlib's library targets to ensure they can
be installed and link correctly.

## Building

First ensure ystdlib has been installed. For example, after [building](../README.md#building)
[install](../README.md#building) by running:

```shell
cmake --install "./build" --prefix "./build/examples/ystdlib"
```

To build the examples run:

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
