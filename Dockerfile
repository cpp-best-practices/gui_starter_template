FROM ubuntu:bionic

# Set up dependencies
ENV GCC_VER "10"
ENV LLVM_VER "11"
ENV CC gcc-${GCC_VER}
ENV CXX g++-${GCC_VER}

# Add ability to install PPAs
RUN apt-get update -qq
RUN apt-get -y install software-properties-common wget git

# Add repo for gcc-10
RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test
# Add repo for clang-11
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
RUN add-apt-repository -y "deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-${LLVM_VER} main"
# Add repo for current cmake/ccmake, from Kitware
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null \
    | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
RUN apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'
RUN apt-get update -qq

# Install all the packages
RUN apt-get install -y python3 python3-pip doxygen graphviz ccache cppcheck \
    gcc-${GCC_VER} g++-${GCC_VER} \
    clang-${LLVM_VER} lldb-${LLVM_VER} lld-${LLVM_VER} clangd-${LLVM_VER} \
    llvm-${LLVM_VER}-dev libclang-${LLVM_VER}-dev clang-tidy-${LLVM_VER} \
    cmake cmake-curses-gui \
    neovim emacs
#   ^ Don't get stuck in a Docker image with no way to edit files

# Set the default clang-tidy, so CMake can find it
RUN update-alternatives --install /usr/bin/clang-tidy clang-tidy $(which clang-tidy-${LLVM_VER}) 1

# Install conan
RUN python3 -m pip install --upgrade pip setuptools
RUN python3 -m pip install conan

# Fail if we can't run Conan
RUN conan --version

# Install include-what-you-use
RUN mkdir -p /home/iwyu && cd /home/iwyu
RUN git clone --branch clang_${LLVM_VER} \
    https://github.com/include-what-you-use/include-what-you-use.git
RUN mkdir build && cd build
RUN cmake -G "Unix Makefiles" -DCMAKE_PREFIX_PATH=/usr/lib/llvm-${LLVM_VER} ../include-what-you-use
RUN make -j && make install
RUN cd /

# Per https://github.com/include-what-you-use/include-what-you-use#how-to-install:
# `You need to copy the Clang include directory to the expected location before
#  running (similarly, use include-what-you-use -print-resource-dir to learn
#  exactly where IWYU wants the headers).`
RUN mkdir -p $(include-what-you-use -print-resource-dir 2>/dev/null)
RUN ln -s $(readlink -f /usr/lib/clang/${LLVM_VER}/include) \
    $(include-what-you-use -print-resource-dir 2>/dev/null)/include

# Include project
ADD . /starter_project
WORKDIR /starter_project

CMD ["/bin/bash"]
