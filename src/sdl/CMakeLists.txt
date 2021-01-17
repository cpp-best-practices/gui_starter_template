add_executable(test_sdl main.cpp)
target_link_libraries(test_sdl PRIVATE CONAN_PKG::sdl2)
