#!/usr/bin/env bash

# This script is intended to be run from an Ubuntu 18.04 Docker image.
# Since it uses `apt-get` to install dependencies required by the examples,
# it may also run on other versions of Ubuntu, or other Debian-derived distros.
# It will definitely not run without `apt-get` installed!

set -euo pipefail

DEFAULT_BUILD_DIR="build"
BUILD_DIR="${DEFAULT_BUILD_DIR}"
SCRIPT_NAME=$(basename $0)
PROJECT_DIRNAME=$(dirname $(readlink -f $0))
USAGE="Usage: ${SCRIPT_NAME} [options]...

Options:
  -h, --help                  Print this message
  -b, --build-dir  BUILD_DIR  Build examples in BUILD_DIR instead of default '${DEFAULT_BUILD_DIR}'
  --all                       Build all the examples available
  --fltk                      Build fltk example
  --gtkmm                     Build gtkmm example
  --imgui                     Build imgui example
  --nana                      Build nana example
  --qt                        Build qt example
  --sdl                       Build sdl example
"

function build_fltk() {
  apt-get install -y --no-install-recommends libfltk1.3-dev libgl1-mesa-dev fluid
  BUILD_DIR="${1:-build-fltk}"
  mkdir -p "${BUILD_DIR}"
  cmake -S "${PROJECT_DIRNAME}" -B "${BUILD_DIR}" -DCPP_STARTER_USE_FLTK=ON
  cmake --build "${BUILD_DIR}" -j
}

function build_gtkmm() {
  apt-get install -y --no-install-recommends pkg-config libgtkmm-3.0-dev
  BUILD_DIR="${1:-build-gtkmm}"
  mkdir -p "${BUILD_DIR}"
  cmake -S "${PROJECT_DIRNAME}" -B "${BUILD_DIR}" -DCPP_STARTER_USE_GTKMM=ON
  cmake --build "${BUILD_DIR}" -j
}

function build_imgui() {
  apt-get install -y --no-install-recommends pkg-config libgl1-mesa-dev
  BUILD_DIR="${1:-build-imgui}"
  mkdir -p "${BUILD_DIR}"
  cmake -S "${PROJECT_DIRNAME}" -B "${BUILD_DIR}" -DCPP_STARTER_USE_IMGUI=ON
  cmake --build "${BUILD_DIR}" -j
}

function build_nana() {
  # CMakeLists.txt is 'supposed' to install all of these automatically, but for
  # some reason it doesn't always work. Installing them manually does work.
  apt-get install -y --no-install-recommends libjpeg8-dev libpng-dev \
    libasound2-dev alsa-utils alsa-oss libx11-dev libxft-dev libxcursor-dev
  BUILD_DIR="${1:-build-nana}"
  mkdir -p "${BUILD_DIR}"
  # Note: Nana's headers trigger the -Wshadow warning, and cannot be compiled with -Werror.
  # Supposedly, this is fixed in the develop-1.8 branch, but I cannot confirm.
  cmake -S "${PROJECT_DIRNAME}" -B "${BUILD_DIR}" -DCPP_STARTER_USE_NANA=ON -DWARNINGS_AS_ERRORS=FALSE
  cmake --build "${BUILD_DIR}" -j
}

function build_qt() {
  apt-get install -y --no-install-recommends qt5-default qtbase5-dev
  BUILD_DIR="${1:-build-qt}"
  mkdir -p "${BUILD_DIR}"
  cmake -S "${PROJECT_DIRNAME}" -B "${BUILD_DIR}" -DCPP_STARTER_USE_QT=ON
  cmake --build "${BUILD_DIR}" -j
}

function build_sdl() {
  pip install mako
  BUILD_DIR="${1:-build-sdl}"
  mkdir -p "${BUILD_DIR}"
  cmake -S "${PROJECT_DIRNAME}" -B "${BUILD_DIR}" -DCPP_STARTER_USE_SDL=ON
  cmake --build "${BUILD_DIR}" -j
}

function build_all() {
  build_fltk
  build_gtkmm
  build_imgui
  build_nana
  build_qt
  build_sdl
}

# Parse the available options
PARSED_OPTIONS=$(getopt -n "$0" -o h: --long "fltk,gtkmm,imgui,nana,qt,sdl,all,help,build:" -- "$@")
eval set -- "${PARSED_OPTIONS}"

# Handle all the options
while true;
do
  case "$1" in
    --help|-h)
      echo "${USAGE}"
      shift;;
    --build-dir|-b)
      if [ -n "$2" ];
      then
        BUILD_DIR="$2"
        echo "Using BUILD_DIR='${BUILD_DIR}'"
      fi
      shift 2;;
    --all)
      build_all $BUILD_DIR
      shift;;
    --fltk)
      build_fltk $BUILD_DIR
      shift;;
    --gtkmm)
      build_gtkmm $BUILD_DIR
      shift;;
    --imgui)
      build_imgui $BUILD_DIR
      shift;;
    --nana)
      build_nana $BUILD_DIR
      shift;;
    --qt)
      build_qt $BUILD_DIR
      shift;;
    --sdl)
      build_sdl $BUILD_DIR
      shift;;
    --)
      shift
      break;;
  esac
done
