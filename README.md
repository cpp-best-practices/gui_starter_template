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

Note about install commands: 
- for Windows, we use [choco](https://chocolatey.org/install).
- for MacOS, we use [brew](https://brew.sh/). 
- In case of an error in cmake, make sure that the dependencies are on the PATH.

### Necessary Dependencies
1. A C++ compiler that supports C++17.
See [cppreference.com](https://en.cppreference.com/w/cpp/compiler_support)
to see which features are supported by each compiler.
The following compilers should work:

	* [gcc 7+](https://gcc.gnu.org/)
		<details>
		<summary>Install command</summary>

				- Debian/Ubuntu:
					sudo apt install build-essential

				- Windows:
					choco install mingw -y

				- MacOS:
					brew install gcc

		</details>

	* [clang 6+](https://clang.llvm.org/)
		<details>
		<summary>Install command</summary>

				- Debian/Ubuntu:
					bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"

				- Windows:
					choco install llvm -y

				- MacOS:
			 		brew install llvm

		</details>

	* [Visual Studio 2017 or higher](https://visualstudio.microsoft.com/)
		<details>
		<summary>Install command</summary>

			  - Visual Studio IDE - 2019 Community:
			  	  choco install -y visualstudio2019community --package-parameters "add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended --includeOptional --passive --locale en-US"

				// The minimum compiler version is 19.15, which ships with version 15.8 of the IDE.

		</details>


2. [Conan](https://conan.io/)
	<details>
	<summary>Install Command</summary>

			- Via pip - https://docs.conan.io/en/latest/installation.html#install-with-pip-recommended
				pip install conan

			- Windows:
				choco install conan -y

			- MacOS:
			 	brew install conan

	</details>

3. [CMake 3.15+](https://cmake.org/)
	<details>
	<summary>Install Command</summary>

		- Debian/Ubuntu:
			sudo apt-get install cmake

		- Windows:
			choco install cmake -y

		- MacOS:
	 		brew install cmake

	</details>

### Optional Dependencies
#### C++ Tools
- [Doxygen](http://doxygen.nl/)
	<details>
	<summary>Install Command</summary>

		- Debian/Ubuntu:
			sudo apt-get install doxygen
			sudo apt-get install graphviz

		- Windows:
			choco install doxygen.install -y
			choco install graphviz -y

		- MacOS:
	 		brew install doxygen
	 		brew install graphviz

	</details>

- [ccache](https://ccache.dev/)
	<details>
	<summary>Install Command</summary>

		- Debian/Ubuntu:
			sudo apt-get install ccache

		- Windows:
			choco install ccache -y

		- MacOS:
	 		brew install ccache

	</details>

- [Cppcheck](http://cppcheck.sourceforge.net/)
	<details>
	<summary>Install Command</summary>

		- Debian/Ubuntu:
			sudo apt-get install cppcheck

		- Windows:
			choco install cppcheck -y

		- MacOS:
	 		brew install cppcheck

	</details>

- [include-what-you-use](https://include-what-you-use.org/)
	<details>
	<summary>Install Command</summary>

		Follow instructions here:
		https://github.com/include-what-you-use/include-what-you-use#how-to-install
	</details>

#### GUI libraries
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

To configure the project and write makefiles, you could use `cmake` with a bunch of command line options.
The easier option is to run cmake interactively:

#### **Configure via cmake-gui**:

1) Open cmake-gui from the project directory:
```
cmake-gui .
```
2) Set the build directory:

![build_dir](https://user-images.githubusercontent.com/16418197/82524586-fa48e380-9af4-11ea-8514-4e18a063d8eb.jpg)

3) Configure the generator (and compilers):

<details>
<summary>Windows - MinGW and Clang</summary>
You still need to install Visual Studio because of the SDK and libraries that ship with it.

In cmake-gui, from the upper menu select `Tools/Configure`.

Choose MinGW Makefiles and 2nd option (specify native compilers):

<img src="https://user-images.githubusercontent.com/16418197/82525058-1731e680-9af6-11ea-8d0a-98d2e5a24710.png" alt="mingw">

Give the path to the compilers:

<img src="https://user-images.githubusercontent.com/16418197/82523856-f025e580-9af2-11ea-9ba7-29c536082cba.png" alt="compilers">

</details>

<details>
<summary>Windows - Visual Studio and default compilers</summary>

In cmake-gui, from the upper menu select `Tools/Configure`.

Choose "Visual Studio 16 2019" as the generator:

<img src="https://user-images.githubusercontent.com/16418197/82524696-32502680-9af5-11ea-9697-a42000e900a6.jpg" alt="default_vs">

</details>

<details>

<summary>Windows - Visual Studio and Clang</summary>

Install llvm-utils:
```
git clone https://github.com/zufuliu/llvm-utils.git
cd llvm-utils/VS2017
.\install.bat
```

In cmake-gui, from the upper menu select `Tools/Configure`.

Choose "Visual Studio 16 2019" as the generator. Set `LLVM_v142` for Visual Studio 2019. See [here](https://github.com/zufuliu/llvm-utils#llvm-for-visual-studio-2017-and-2019) for others. Choose the "specify native compilers" option.

<img src="https://user-images.githubusercontent.com/16418197/82524065-94a82780-9af3-11ea-8547-364f96596258.png" alt="visual_studio">


Give the path to the Clang compilers:

<img src="https://user-images.githubusercontent.com/16418197/82523856-f025e580-9af2-11ea-9ba7-29c536082cba.png" alt="compilers">
</details>
<br/>

4) Choose the Cmake options and then generate:

![generate](https://user-images.githubusercontent.com/16418197/82582146-3876ef00-9b57-11ea-9b30-af3d2d85809e.jpg)

#### **Configure via ccmake**:
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
