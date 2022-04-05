add_subdirectory(sdl)
add_subdirectory(fltk)

find_package(fmt CONFIG)
find_package(spdlog CONFIG)
find_package(docopt CONFIG)

# Generic test that uses conan libs
add_executable(intro main.cpp)
target_link_libraries(
  intro
  PRIVATE project_options
          project_warnings
          configured_header_interface
          docopt::docopt
          fmt::fmt
          spdlog::spdlog)
