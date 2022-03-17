add_executable(sdl-example main.cpp)

find_package(SDL2 CONFIG)
find_package(spdlog CONFIG)

target_link_libraries(
  sdl-example
  PRIVATE spdlog::spdlog
          SDL2::SDL2
          SDL2::SDL2main
          project_warnings
          project_options)
