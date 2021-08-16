FROM gitpod/workspace-full-vnc

RUN sudo bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"
RUN sudo apt-get update && sudo apt-get install -y build-essential cmake valgrind doxygen graphviz ccache cppcheck \
        libfltk1.3 libfltk1.3-dev fltk1.3-doc \
        libgtkmm-3.0-dev \
        qt5-default \
        libsdl2-dev libsdl2-2.0-0 libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0
RUN sudo pip install --system conan

RUN echo 'export CC=clang' >> /home/gitpod/.bashrc
#RUN echo 'export CC=gcc' >> /home/gitpod/.bashrc

RUN echo 'export CCX=clang++' >> /home/gitpod/.bashrc
#RUN echo 'export CCX=g++' >> /home/gitpod/.bashrc
