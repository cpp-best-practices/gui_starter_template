# cpp_starter_project

[![codecov](https://codecov.io/gh/lefticus/cpp_starter_project/branch/master/graph/badge.svg)](https://codecov.io/gh/lefticus/cpp_starter_project)

[![Build Status](https://travis-ci.org/lefticus/cpp_starter_project.svg?branch=master)](https://travis-ci.org/lefticus/cpp_starter_project)

[![Build status](https://ci.appveyor.com/api/projects/status/ro4lbfoa7n0sy74c/branch/master?svg=true)](https://ci.appveyor.com/project/lefticus/cpp-starter-project/branch/master)

![CMake](https://github.com/lefticus/cpp_starter_project/workflows/CMake/badge.svg)


## Getting Started

### Use the Github template
First, click the green `Use this template` button near the top of this page.
This will take you to Github's ['Generate Repository'](https://github.com/lefticus/cpp_starter_project/generate) page. 
Fill in a repository name and short description, and click 'Create repository from template'. 
This will allow you to create a new repository in your Github account, 
prepopulated with the contents of this project. 
Now you can clone the project locally and get to work!

    $ git clone https://github.com/<user>/<your_new_repo>.git

### Remove frameworks you're not going to use
If you know you're not going to use one or more of the optional gui/graphics 
frameworks (fltk, gtkmm, imgui, etc.), you can remove them with `git rm`:

    $ git rm -r src/<unnecessary_framework>

## Dependencies

### Necessary Dependencies
1. A C++ compiler that supports C++17. 
See [cppreference.com](https://en.cppreference.com/w/cpp/compiler_support)
to see which features are supported by each compiler.
The following compilers should work:
  * [gcc 7+](https://gcc.gnu.org/)
  * [clang 6+](https://clang.llvm.org/)
  * [Visual Studio 2017](https://visualstudio.microsoft.com/) or higher. 
  The minimum compiler version is 19.15; this version ships with version 15.8 of the IDE. 
2. [Conan](https://conan.io/) - it's recommended that you install using 
[pip](https://pip.pypa.io/en/stable/) 
3. [CMake 3.15+](https://cmake.org/)

### Optional Dependencies
This project can be made to work with several optional GUI frameworks. 
    
If desired, you should install the following optional dependencies as 
directed by their documentation, linked here:
 
- [FLTK](https://www.fltk.org/doc-1.4/index.html)
- [GTKMM](https://www.gtkmm.org/en/documentation.html)
- [QT](https://doc.qt.io/)

The following dependencies can be downloaded automatically by CMake and Conan. 
All you need to do to install them is to turn on a CMake flag during 
configuration.
If you run into difficulty using them, please refer to their documentation,
linked here:

- [NANA](http://nanapro.org/en-us/documentation/)
- [SDL](http://wiki.libsdl.org/FrontPage)
- [IMGUI](https://github.com/ocornut/imgui/tree/master/docs): 
  This framework depends on SFML, and if you are using Linux, you may need
  to install several of SFML's dependencies using your package manager. See 
  [the SFML build tutorial](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php)
  for specifics.

## Build Instructions

### Make a build directory

    $ mkdir build && cd build

### Configure your build

To configure the project and write makefiles, you could use `cmake` with a
bunch of command line options. The easier option is to run cmake interactively,
with the Cmake Curses Dialog Command Line tool:  

    $ ccmake ..

Once `ccmake` has finished setting up, press 'c' to configure the project, 
press 'g' to generate, and 'q' to quit.

### Build
Once you have selected all the options you would like to use, you can build the 
project:

    $ cmake --build .   # build all targets

### Build using an alternate compiler

Conan and CMake use the environment variables CC and CXX to decide which 
compiler to use. If you don't set these variables yourself, the system 
default compiler will be used.

Be aware that CMake will detect which compiler was used to build each of the 
Conan targets. 
If you build all of your Conan targets with one compiler, and then build your 
CMake targets with a different compiler, the project may fail to build. 

To build using clang, you can use these commands:

    $ CC=clang CXX=clang++ ccmake ..
    $ CC=clang CXX=clang++ cmake --build .

## Troubleshooting

### Update Conan
Many problems that users have can be resolved by updating Conan, so if you are 
having any trouble with this project, you should start by doing that.

To update conan: 

    $ pip install --user --upgrade conan 

You may need to use `pip3` instead of `pip` in this command, depending on your 
platform.

### Clear Conan cache
If you continue to have trouble with your Conan dependencies, you can try 
clearing your Conan cache:

    $ conan remove -f '*'
    
The next time you run `cmake` or `cmake --build`, your Conan dependencies will
be rebuilt. If you aren't using your system's default compiler, don't forget to 
set the CC, CXX, CMAKE_C_COMPILER, and CMAKE_CXX_COMPILER variables, as 
described in the 'Build using an alternate compiler' section above.

### Identifying misconfiguration of Conan dependencies

If you have a dependency 'A' that requires a specific version of another 
dependency 'B', and your project is trying to use the wrong version of 
dependency 'B', Conan will produce warnings about this configuration error 
when you run CMake. These warnings can easily get lost between a couple 
hundred or thousand lines of output, depending on the size of your project. 

If your project has a Conan configuration error, you can use `conan info` to 
find it. `conan info` displays information about the dependency graph of your 
project, with colorized output in some terminals.

    $ cd build
    $ conan info .

In my terminal, the first couple lines of `conan info`'s output show all of the
project's configuration warnings in a bright yellow font. 

For example, the package `spdlog/1.5.0` depends on the package `fmt/6.1.2`.
If you were to modify the file `cmake/Conan.cmake` so that it requires an 
earlier version of `fmt`, such as `fmt/6.0.0`, and then run:

    $ conan remove -f '*'       # clear Conan cache
    $ rm -rf build              # clear previous CMake build
    $ mkdir build && cd build
    $ cmake ..                  # rebuild Conan dependencies
    $ conan info .

...the first line of output would be a warning that `spdlog` needs a more recent
version of `fmt`.

## Testing
See [Catch2 tutorial](https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md)

## Fuzz testing

See [libFuzzer Tutorial](https://github.com/google/fuzzing/blob/master/tutorial/libFuzzerTutorial.md)
