# Examples

This directory contains example programs that demonstrate how to use the ystdlib library.

The example program `linking-tests` references all of ystdlib's library targets to ensure they can
be installed and linked correctly.

## Building

### Using Task

#### Requirements

See the [ystdlib Requirements section](../README.md#Requirements).

#### Commands

```shell
# debug build
task examples:build-debug

# release build
task examples:build-release
```

### Using CMake

#### Requirements

[Build](../README.md#building) and [install](../README.md#installing) ystdlib. The commands below
assume you've built and installed ystdlib to `./build/examples/ystdlib`. If you installed it to a
different location, adjust the paths accordingly.

#### Commands

```shell
cmake -S "./examples" -B "./build/examples" -Dystdlib_ROOT="./build/examples/ystdlib"

cmake --build "./build/examples"
```

## Running

```shell
./build/examples/linking-tests
```

On success, the exit code will be 0 with no output printed.
