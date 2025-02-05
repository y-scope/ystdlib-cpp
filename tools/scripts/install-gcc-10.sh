#!/usr/bin/env bash

# Exit on any error
set -e

# Error on undefined variable
set -u

apt-get update
DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y \
    g++ \
    g++-10 \
    gcc \
    gcc-10

ln -s -f /usr/bin/gcc-10 /usr/bin/cc
ln -s -f /usr/bin/g++-10 /usr/bin/c++
ln -s -f /usr/bin/cpp-10 /usr/bin/cpp
