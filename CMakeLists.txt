cmake_minimum_required(VERSION 3.15)

# uncomment to set a default CXX standard for the external tools like clang-tidy and cppcheck
# and the targets that do not specify a standard.
# If not set, the latest supported standard for your compiler is used
# You can later set fine-grained standards for each target using `target_compile_features`
# set(CMAKE_CXX_STANDARD 17)

# Add ProjectOptions v0.10.0
# https://github.com/aminya/ProjectOptions
include(FetchContent)
FetchContent_Declare(projectoptions URL https://github.com/aminya/ProjectOptions/archive/refs/tags/v0.10.0.zip)
FetchContent_MakeAvailable(projectoptions)
include(${projectoptions_SOURCE_DIR}/Index.cmake)

# uncomment to enable vcpkg:
# # Setup vcpkg - should be called before defining project()
# run_vcpkg()

# Set the project name to your project name, my_project isn't very descriptive
project(myproject LANGUAGES CXX)

# Initialize ProjectOptions
# uncomment the options to enable them:
ProjectOptions(
      ENABLE_CACHE
      # WARNINGS_AS_ERRORS
      ENABLE_CPPCHECK
      ENABLE_CLANG_TIDY
      ENABLE_CONAN
      # ENABLE_IPO
      # ENABLE_INCLUDE_WHAT_YOU_USE
      # ENABLE_COVERAGE
      # ENABLE_PCH
      # PCH_HEADERS
      # ENABLE_DOXYGEN
      # ENABLE_USER_LINKER
      # ENABLE_BUILD_WITH_TIME_TRACE
      # ENABLE_UNITY
      # ENABLE_SANITIZER_ADDRESS
      # ENABLE_SANITIZER_LEAK
      # ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
      # ENABLE_SANITIZER_THREAD
      # ENABLE_SANITIZER_MEMORY
      # CONAN_OPTIONS
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
