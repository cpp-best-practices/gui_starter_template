add_executable(test_sdl main.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(test_sdl PRIVATE ${SDL2_LIBRARIES})
