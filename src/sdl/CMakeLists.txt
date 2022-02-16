add_executable(test_sdl main.cpp)

find_package(SDL2 CONFIG)
find_package(spdlog CONFIG)

target_link_libraries(test_sdl PRIVATE spdlog::spdlog SDL2::SDL2 SDL2::SDL2main project_warnings project_options)
