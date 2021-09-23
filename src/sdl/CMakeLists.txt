find_package(SDL2 CONFIG REQUIRED)

add_executable(test_sdl main.cpp)
target_link_libraries(test_sdl PRIVATE SDL2::SDL2)
target_link_libraries(test_sdl PRIVATE project_warnings project_options)
set_target_properties(test_sdl PROPERTIES UNITY_BUILD ${ENABLE_UNITY})

# NOTE: this quickfix was needed at leased with brew on OSX! CK
# target_include_directories(test_sdl PRIVATE ${SDL2_INCLUDE_DIRS}/..)

