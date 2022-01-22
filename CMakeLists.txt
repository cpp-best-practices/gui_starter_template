cmake_minimum_required(VERSION 3.16)

# uncomment to set a default CXX standard for the external tools like clang-tidy and cppcheck
# and the targets that do not specify a standard.
# If not set, the latest supported standard for your compiler is used
# You can later set fine-grained standards for each target using `target_compile_features`
# set(CMAKE_CXX_STANDARD 17)

# Add project_options v0.12.3
# https://github.com/cpp-best-practices/project_options
include(FetchContent)
FetchContent_Declare(_project_options
                     URL https://github.com/cpp-best-practices/project_options/archive/refs/tags/v0.12.3.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

# uncomment to enable vcpkg:
# # Setup vcpkg - should be called before defining project()
# run_vcpkg()

# Set the project name and language
project(myproject LANGUAGES CXX)

# Add global CMake options
include(${_project_options_SOURCE_DIR}/src/GlobalOptions.cmake)
# Initialize project_options variable related to this project
# This overwrites `project_options` and sets `project_warnings`
# uncomment the options to enable them:
project_options(
  ENABLE_CACHE # ccache on Unix, to avoid rebuilding the same file with clean builds
  WARNINGS_AS_ERRORS # force warnings to be dealt with, by making them hard errors
  ${CPPCHECK} # cppcheck is a standalone static analysis tool with helpful checks
  ${CLANG_TIDY} # clang-tidy is a static analysis tool that's part of the llvm toolchain
  ENABLE_CONAN # package manager for getting dependencies with nice cmake integration
  ENABLE_COVERAGE # analyze and report coverage of code lines
  # ENABLE_IPO                     # inter-procedural-optimization, aka whole program optimization aka link-time-optimization (LTO)
  # ENABLE_INCLUDE_WHAT_YOU_USE    # analysis to make sure #includes are handled properly
  # ENABLE_PCH                     # pre-compiled headers. Can speed up compilation in some cases
  # PCH_HEADERS
  # ENABLE_DOXYGEN                 # build documentation with the doxygen tool
  # ENABLE_USER_LINKER
  # ENABLE_BUILD_WITH_TIME_TRACE   # generates report of where compile-time is spent
  # ENABLE_UNITY                   # merge C++ files into larger C++ files, can speed up compilation sometimes
  ${ADDRESS_SANITIZER} # make memory errors into hard runtime errors (windows/linux/macos)
  # ENABLE_SANITIZER_LEAK          # make memory leaks into hard runtime errors
  ${UNDEFINED_BEHAVIOR_SANITIZER} # make certain types (numeric mostly) of undefined behavior into runtime errors
  # ENABLE_SANITIZER_THREAD        # make thread race conditions into hard runtime errors
  # ENABLE_SANITIZER_MEMORY
  # CONAN_OPTIONS
)
target_compile_features(project_options INTERFACE cxx_std_17)

# Adding the src:
add_subdirectory(src)

# Adding the tests:
option(ENABLE_TESTING "Enable the tests" ON)
if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests. Be sure to check out test/constexpr_tests for constexpr
testing")
  add_subdirectory(test)
endif()

option(ENABLE_FUZZING "Enable the fuzz tests" OFF)
if(ENABLE_FUZZING)
  message("Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
  add_subdirectory(fuzz_test)
endif()
