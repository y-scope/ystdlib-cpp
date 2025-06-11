# Examples

The example program `linking-tests` references all of ystdlib's library targets to ensure they can
be installed and link correctly.

## Building

To build the examples, run one of the following task commands:

```shell
# debug build
task build:examples-debug

# release build
task build:examples-release
```

## Running

Run the example program as follows:

```shell
./build/examples/debug/linking-tests
```
