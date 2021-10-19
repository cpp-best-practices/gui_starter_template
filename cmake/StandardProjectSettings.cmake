# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
  set(CMAKE_BUILD_TYPE
      RelWithDebInfo
      CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui, ccmake
  set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
             "Debug"
             "Release"
             "MinSizeRel"
             "RelWithDebInfo")
endif()

# Generate compile_commands.json to make it easier to work with clang based tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_IPO "Enable Interprocedural Optimization, aka Link Time Optimization (LTO)" OFF)

if(ENABLE_IPO)
  include(CheckIPOSupported)
  check_ipo_supported(
    RESULT
    result
    OUTPUT
    output)
  if(result)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
  else()
    message(SEND_ERROR "IPO is not supported: ${output}")
  endif()
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  add_compile_options(-fcolor-diagnostics)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
else()
  message(STATUS "No colored compiler diagnostic set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
endif()

option(USE_OUTPUT_PATH "build all libaries and runtime files at lib and bin directory" YES)
set(OUTPUT_LIB_PATH "/lib" CACHE STRING "Choose the output path of library targets.")
set(OUTPUT_BIN_PATH "/bin" CACHE STRING "Choose the output path of binary targets.")
if(USE_OUTPUT_PATH)
  # -----------------------------------------------------------------------
  # Where to put all the LIBRARY targets when built. This variable is used to initialize the
  # LIBRARY_OUTPUT_DIRECTORY property on all the targets.
  # -----------------------------------------------------------------------
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}${OUTPUT_LIB_PATH})

  # -----------------------------------------------------------------------
  # Where to put all the RUNTIME targets when built. This variable is used to initialize the
  # RUNTIME_OUTPUT_DIRECTORY property on all the targets.
  # -----------------------------------------------------------------------
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}${OUTPUT_BIN_PATH})
endif()