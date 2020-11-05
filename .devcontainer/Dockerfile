# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.145.1/containers/ubuntu/.devcontainer/base.Dockerfile

# [Choice] Ubuntu version: bionic, focal
ARG VARIANT="focal"
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}

# Install build tools here
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y -qq install --no-install-recommends \
    clang-format clang-tidy clang-tools clang clangd \
    libc++-dev libc++1 libc++abi-dev libc++abi1 \
    libclang-dev libclang1 liblldb-dev libllvm-ocaml-dev \
    libomp-dev libomp5 lld lldb llvm-dev llvm-runtime llvm \
    python-clang python3 python3-pip cmake ninja-build build-essential \ 
    && pip3 install conan

# Install additional tools here
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y -qq install --no-install-recommends \
    cppcheck ccache doxygen valgrind graphviz cmake-curses-gui \
    pkg-config libtool automake

# Enable GUI support here
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y -qq install --no-install-recommends \
#     cmake-gui xorg-dev libsfml-dev libx11-xcb-dev xkb-data libgtkmm-3.0-dev \
#     libudev-dev 'libxcb-*' libglvnd0 libgl1 libglx0 libegl1 libfltk1.3-dev \
#     libxext6 libx11-6 libgl1-mesa-dev qt5-default glmark2 \
#     && rm -rf /var/lib/apt/lists/*
# ENV NVIDIA_VISIBLE_DEVICES all
# ENV NVIDIA_DRIVER_CAPABILITIES graphics,utility,compute
