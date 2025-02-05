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

echo "export CC=/usr/bin/gcc-10" >> ~/.bashrc
echo "export CXX=/usr/bin/g++-10" >> ~/.bashrc

source ~/.bashrc
