# cpp_starter_project

[![codecov](https://codecov.io/gh/lefticus/cpp_starter_project/branch/master/graph/badge.svg)](https://codecov.io/gh/lefticus/cpp_starter_project)

[![Build Status](https://travis-ci.org/lefticus/cpp_starter_project.svg?branch=master)](https://travis-ci.org/lefticus/cpp_starter_project)

[![Build status](https://ci.appveyor.com/api/projects/status/ro4lbfoa7n0sy74c/branch/master?svg=true)](https://ci.appveyor.com/project/lefticus/cpp-starter-project/branch/master)


## Getting Started

First, click the green `Use this template` button near the top of this page.
This will take you to Github's ['Generate Repository'](https://github.com/lefticus/cpp_starter_project/generate) page. 
Fill in a repository name and short description, and click 'Create repository from template'. 
This will allow you to create a new repository in your Github account, 
prepopulated with the contents of this project. 
Now you can clone the project locally and get to work!

    $ git clone https://github.com/<user>/<your_new_repo>.git

If you know you're not going to use one or more of the optional gui/graphics 
frameworks (fltk, gtkmm, imgui, etc.), you can remove them with `git rm`:

    $ git rm -r src/<unnecessary_framework>

## Necessary Dependencies

1. A C++ compiler that supports C++17 (gcc 7+, clang 6+, Visual Studio 2019)
2. [Conan](https://conan.io/) - it's recommended that you install using 
[pip](https://pip.pypa.io/en/stable/) 
3. [CMake](https://cmake.org/)
4. Other Linux dependencies. If you are using Linux, there may be other 
    dependencies you will need to install, depending on what frameworks you 
    are using. Please see the documentation for your particular framework for 
    details:
    
    - [FLTK](https://www.fltk.org/doc-1.4/index.html)
    - [GTKMM](https://www.gtkmm.org/en/documentation.html)
    - [IMGUI](https://github.com/ocornut/imgui/tree/master/docs)
    - [NANA](http://nanapro.org/en-us/documentation/)
    - [QT](https://doc.qt.io/)
    - [SDL](http://wiki.libsdl.org/FrontPage)
    - [SFML](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php)

## Build Instructions

Before we can build, we need to make a build directory. For these directions,
we will use an in-source build directory; if you prefer using an out-of-source
build directory, adjust these directions accordingly.

    $ mkdir build && cd build

To configure the project and write makefiles, you could use `cmake` with a
bunch of command line options. The easier option is to run cmake interactively,
with the Cmake Curses Dialog Command Line tool:  

    $ ccmake ..

Once ccmake has finished setting up, press 'c' to configure the project.
Once you have selected all the options you would like to use, you can build the 
project:

    $ cmake --build .   # build all targets

### Build using an alternate compiler

If you need to use a compiler other than the system default, you will need to 
do two things:

* Tell Conan which compiler to use, via the environment variables CC and CXX
* Tell CMake which compiler to use, via the CMake variables CMAKE_C_COMPILER 
  and CMAKE_CXX_COMPILER

Be aware that CMake will detect which compiler was used to build each of the 
Conan targets, and if it doesn't match CMAKE_C_COMPILER or CMAKE_CXX_COMPILER,
the project will fail to build.

To build using clang, you can use these commands:

    $ CC=clang CXX=clang++ ccmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
    $ CC=clang CXX=clang++ cmake --build .
