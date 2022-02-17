# sdl example
add_subdirectory(sdl)

# Add executable
add_executable(intro main.cpp)

# Find dependencies:
set(DEPENDENCIES_CONFIGURED fmt spdlog docopt)

foreach(DEPENDENCY ${DEPENDENCIES_CONFIGURED})
  find_package(${DEPENDENCY} CONFIG REQUIRED)
endforeach()

# Link dependencies
target_link_libraries(
  intro
  PRIVATE project_options
          project_warnings
          docopt::docopt
          fmt::fmt
          spdlog::spdlog)
