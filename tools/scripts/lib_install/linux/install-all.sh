#!/usr/bin/env bash

# Exit on any error
set -e

# Error on undefined variable
set -u

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

OS=$(uname)
if [[ "Linux" != "${OS}" ]]; then
  echo "This is a Linux-specific script."
  exit 0
fi

echo "Checking for elevated privileges..."
privileged_command_prefix=""
USER_ID=${EUID:-$(id -u)}
if [[ 0 -ne ${USER_ID} ]] ; then
  sudo echo "Script can elevate privileges."
  privileged_command_prefix="${privileged_command_prefix} sudo"
fi

# Check if the system is running Ubuntu and determine the version
if [[ -f /etc/os-release ]]; then
  source /etc/os-release
  if [[ "${ID}" == "ubuntu" &&
      ( "${VERSION_CODENAME}" == "focal" ||
        "${VERSION_CODENAME}" == "jammy" ||
        "${VERSION_CODENAME}" == "noble" ) ]]; then
    dist_dir="${script_dir}/ubuntu-${VERSION_CODENAME}"
    for exe_file in \
        "${dist_dir}/install-prebuilt-packages.sh" "${dist_dir}/install-packages-from-source.sh"; do
	  [[ -f "${exe_file}"  ]] && ${privileged_command_prefix} "${exe_file}"
    done
    exit 0
  fi
fi

echo "Supports only Ubuntu LTS releases from Ubuntu 20.04 LTS onward." >&2
exit 1
