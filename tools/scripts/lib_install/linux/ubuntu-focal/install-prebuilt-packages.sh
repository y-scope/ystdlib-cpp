#!/usr/bin/env bash

# Exit on any error
set -e

# Error on undefined variable
set -u

apt-get update
DEBIAN_FRONTEND=noninteractive apt-get install --no-install-recommends -y \
    g++ \
    g++-11 \
    gcc \
    gcc-11

# Add alternatives for cpp-10, gcc-10, and g++-10
# NOTE: We use a low priority to avoid affecting the prioritization of any existing alternatives
# on the user's system.
update-alternatives --install /usr/bin/cc cc /usr/bin/gcc-11 0 \
  --slave /usr/share/man/man1/cc.1.gz cc.1.gz /usr/share/man/man1/gcc.1.gz
update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-11 0 \
  --slave /usr/share/man/man1/c++.1.gz c++.1.gz /usr/share/man/man1/g++.1.gz
update-alternatives --install /lib/cpp cpp /usr/bin/cpp-11 0

update-alternatives --config cc

update-alternatives --set cc /usr/bin/gcc-11
update-alternatives --set c++ /usr/bin/g++-11
update-alternatives --set cpp /usr/bin/cpp-11

update-alternatives --config cc
