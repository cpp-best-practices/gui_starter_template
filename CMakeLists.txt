cmake_minimum_required(VERSION 3.16)

# uncomment to set a default CXX standard for the external tools like clang-tidy and cppcheck
# and the targets that do not specify a standard.
# If not set, the latest supported standard for your compiler is used
# You can later set fine-grained standards for each target using `target_compile_features`
# Note: linking together projects compiled with different C++ standards may work, but
# it is not recommended because of possible issues with ABI
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

if(MSVC)
  # Make sure that all supported configuration types have their
  # associated conan packages available. You can reduce this
  # list to only the configuration types you use
  set(CMAKE_CONFIGURATION_TYPES
      Debug
      Release
      RelWithDebInfo
      MinSizeRel)
endif()

# Set defaults for options enabled with the project_options project
# and the GlobalOptions utility below
#
# Note: These defaults represent those suggested by Jason Turner in
# C++ Best Practices
set(ENABLE_CPPCHECK
    ON
    CACHE BOOL "Enable CppCheck analysis")
set(ENABLE_CLANG_TIDY
    ON
    CACHE BOOL "Enable clang-tidy analysis")
set(ENABLE_CACHE
    ON
    CACHE BOOL "Enable ccache")
set(ENABLE_COVERAGE
    ON
    CACHE BOOL "Enable coverage testing")
set(ENABLE_CONAN
    ON
    CACHE BOOL "Enable conan for dependencies")
set(ENABLE_SANITIZER_ADDRESS
    ON
    CACHE BOOL "Enable address sanitizer for runtime memory checking")
set(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
    ON
    CACHE BOOL "Enable undefined behavior sanitizer for runtime checking")
set(WARNINGS_AS_ERRORS
    ON
    CACHE BOOL "Enable undefined behavior sanitizer for runtime checking")

# Add global CMake options
include(${_project_options_SOURCE_DIR}/src/GlobalOptions.cmake)

# Initialize project_options variable related to this project
# This overwrites `project_options` and sets `project_warnings`
# uncomment the options to enable them:
project_options(
  ${ENABLE_CACHE} # ccache on Unix, to avoid rebuilding the same file with clean builds
  ${WARNINGS_AS_ERRORS} # force warnings to be dealt with, by making them hard errors
  ${ENABLE_CPPCHECK} # cppcheck is a standalone static analysis tool with helpful checks
  ${ENABLE_CLANG_TIDY} # clang-tidy is a static analysis tool that's part of the llvm toolchain
  ${ENABLE_CONAN} # package manager for getting dependencies with nice cmake integration
  ${ENABLE_COVERAGE} # analyze and report coverage of code lines
  ${ENABLE_IPO} # inter-procedural-optimization, aka whole program optimization aka link-time-optimization (LTO)
  ${ENABLE_INCLUDE_WHAT_YOU_USE} # analysis to make sure #includes are handled properly
  ${ENABLE_PCH} # pre-compiled headers. Can speed up compilation in some cases
  # PCH_HEADERS a_list_of.hpp headers_to_use.hpp  # This is a list of headers to pre-compile
  ${ENABLE_DOXYGEN} # build documentation with the doxygen tool
  ${ENABLE_USER_LINKER}
  ${ENABLE_BUILD_WITH_TIME_TRACE} # generates report of where compile-time is spent
  ${ENABLE_UNITY} # merge C++ files into larger C++ files, can speed up compilation sometimes
  ${ENABLE_SANITIZER_ADDRESS} # make memory errors into hard runtime errors (windows/linux/macos)
  ${ENABLE_SANITIZER_LEAK} # make memory leaks into hard runtime errors
  ${ENABLE_SANITIZER_UNDEFINED_BEHAVIOR} # make certain types (numeric mostly) of undefined behavior into runtime errors
  ${ENABLE_SANITIZER_THREAD} # make thread race conditions into hard runtime errors
  ${ENABLE_SANITIZER_MEMORY}
  # CONAN_OPTIONS # Extra options to pass to conan
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

# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment
# so that it behaves well with MSVC's debugger, and we can run the target from visual studio

function(get_all_targets var)
  set(targets)
  get_all_targets_recursive(targets ${CMAKE_CURRENT_SOURCE_DIR})
  set(${var}
      ${targets}
      PARENT_SCOPE)
endfunction()

macro(get_all_targets_recursive targets dir)
  get_property(
    subdirectories
    DIRECTORY ${dir}
    PROPERTY SUBDIRECTORIES)
  foreach(subdir ${subdirectories})
    get_all_targets_recursive(${targets} ${subdir})
  endforeach()

  get_property(
    current_targets
    DIRECTORY ${dir}
    PROPERTY BUILDSYSTEM_TARGETS)
  list(APPEND ${targets} ${current_targets})
endmacro()

if(MSVC)
  get_all_targets(all_targets)
  set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()

# set the startup project for the "play" button in MSVC
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT intro)
