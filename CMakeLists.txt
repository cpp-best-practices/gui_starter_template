cmake_minimum_required(VERSION 3.15)

# Set the project name to your project name, my project isn't very descriptive
project(myproject CXX)

# Add cmakelib
include(FetchContent)
FetchContent_Declare(cmakelib URL https://github.com/aminya/cmakelib/archive/refs/heads/main.zip)
FetchContent_MakeAvailable(cmakelib)
include(${cmakelib_SOURCE_DIR}/Index.cmake)

# Initialize cmakelib
# uncomment the options to enable them
cmakelib(
    Enable_CACHE
    ENABLE_CONAN
    WARNINGS_AS_ERRORS
    # ENABLE_CPPCHECK
    # ENABLE_CLANG_TIDY
    # ENABLE_INCLUDE_WHAT_YOU_USE
    # ENABLE_COVERAGE
    # ENABLE_PCH
    # ENABLE_DOXYGEN
    # ENABLE_IPO
    # ENABLE_USER_LINKER
    # ENABLE_BUILD_WITH_TIME_TRACE
    # ENABLE_UNITY
    # ENABLE_SANITIZER_ADDRESS
    # ENABLE_SANITIZER_LEAK
    # ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
    # ENABLE_SANITIZER_THREAD
    # ENABLE_SANITIZER_MEMORY
)

# project_options is defined inside cmakelib
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
