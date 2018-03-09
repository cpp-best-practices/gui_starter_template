cmake_minimum_required(VERSION 3.2)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" FALSE)

if(CMAKE_COMPILER_IS_GNUCC)
  option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

  if(ENABLE_COVERAGE)
    add_compile_options(--coverage -O0)
  endif()
endif()

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(intro main.cpp)
target_compile_features(intro PRIVATE cxx_lambda_init_captures)
target_link_libraries(intro --coverage)

enable_testing()

add_executable(tester tester.cpp)
target_link_libraries(tester --coverage)
add_test(Tester tester)

find_package(FLTK REQUIRED)
add_executable(test_fltk fltk/test_fltk.cpp)
target_link_libraries(test_fltk PRIVATE ${FLTK_LIBRARIES})
target_include_directories(test_fltk PRIVATE ${FLTK_INCLUDE_DIR})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
add_executable(test_gtkmm gtkmm/main.cpp gtkmm/hello_world.cpp)
target_link_libraries(test_gtkmm PRIVATE ${GTKMM_LIBRARIES})
target_include_directories(test_gtkmm PRIVATE ${GTKMM_INCLUDE_DIRS})

find_package(SFML COMPONENTS graphics window system)
find_package(OpenGL)
add_library(imgui
            imgui/lib/imgui.cpp
            imgui/lib/imgui_draw.cpp
            imgui/lib/imgui-SFML.cpp
            imgui/lib/test.cpp)
target_link_libraries(imgui INTERFACE ${SFML_LIBRARIES} ${OPENGL_gl_LIBRARY})
add_executable(test_imgui imgui/test.cpp)
target_link_libraries(test_imgui imgui)
target_include_directories(test_imgui PRIVATE ${SFML_INCLUDE_DIR})

