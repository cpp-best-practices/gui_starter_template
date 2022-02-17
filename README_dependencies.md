## Dependencies

Note about install commands:
- for Windows, we use [choco](https://chocolatey.org/install).
- for MacOS, we use [brew](https://brew.sh/).
- In case of an error in cmake, make sure that the dependencies are on the PATH.


### Too Long, Didn't Install

This is a really long list of dependencies, and it's easy to mess up. That's why:

#### Docker
We have a Docker image that's already set up for you. See the [Docker instructions](#docker-instructions).

#### Setup-cpp

We have [setup-cpp](https://github.com/aminya/setup-cpp) that is a cross-platform tool to install all the compilers and dependencies on the system.

Please check [the setup-cpp documentation](https://github.com/aminya/setup-cpp) for more information.

For example, on Windows, you can run the following to install llvm, cmake, ninja, ccache, conan, and cppcheck.
```ps1
# windows example (open shell as admin)
curl -LJO "https://github.com/aminya/setup-cpp/releases/download/v0.5.7/setup_cpp_windows.exe"
./setup_cpp_windows --compiler llvm --cmake true --ninja true --ccache true --conan true --cppcheck true

RefreshEnv.cmd # reload the environment
```

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

		Visual Studio 2019 ships with LLVM (see the Visual Studio section). However, to install LLVM separately:

			choco install llvm -y

		llvm-utils for using external LLVM with Visual Studio generator:

			git clone https://github.com/zufuliu/llvm-utils.git
			cd llvm-utils/VS2017
			.\install.bat

	- MacOS:

			brew install llvm
	</details>

  * [Visual Studio 2019 or higher](https://visualstudio.microsoft.com/)
	<details>
	<summary>Install command + Environment setup</summary>

	On Windows, you need to install Visual Studio 2019 because of the SDK and libraries that ship with it.

  	Visual Studio IDE - 2019 Community (installs Clang too):

  	  	choco install -y visualstudio2019community --package-parameters "add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended --includeOptional --passive --locale en-US"

	Put MSVC compiler, Clang compiler, and vcvarsall.bat on the path:

			choco install vswhere -y
			refreshenv

			# change to x86 for 32bit
			$clpath = vswhere -products * -latest -prerelease -find **/Hostx64/x64/*
			$clangpath = vswhere -products * -latest -prerelease -find **/Llvm/bin/*
			$vcvarsallpath =  vswhere -products * -latest -prerelease -find **/Auxiliary/Build/*

			$path = [System.Environment]::GetEnvironmentVariable("PATH", "User")
			[Environment]::SetEnvironmentVariable("Path", $path + ";$clpath" + ";$clangpath" + ";$vcvarsallpath", "User")
			refreshenv

	</details>


2. [Conan](https://conan.io/)
	<details>
	<summary>Install Command</summary>

	- Via pip - https://docs.conan.io/en/latest/installation.html#install-with-pip-recommended

			pip install --user conan

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
  * [Doxygen](http://doxygen.nl/)
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


  * [ccache](https://ccache.dev/)
	<details>
	<summary>Install Command</summary>

	- Debian/Ubuntu:

			sudo apt-get install ccache

	- Windows:

			choco install ccache -y

	- MacOS:

			brew install ccache

	</details>


  * [Cppcheck](http://cppcheck.sourceforge.net/)
	<details>
	<summary>Install Command</summary>

	- Debian/Ubuntu:

			sudo apt-get install cppcheck

	- Windows:

			choco install cppcheck -y

	- MacOS:

			brew install cppcheck

	</details>


  * [include-what-you-use](https://include-what-you-use.org/)
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


