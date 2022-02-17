# uncomment to enable the gui examples

# sdl
# add_subdirectory(sdl)

# qt
# add_subdirectory(qt)

# fltk test
# add_subdirectory(fltk)

# gtkmm test
# add_subdirectory(gtkmm)

# imgui example
# add_subdirectory(imgui)

# Nana
# add_subdirectory(nana)

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
