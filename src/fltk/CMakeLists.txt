project(myproject_fltk)

find_package(FLTK CONFIG)
clangformat_setup(test_fltk.cpp)
add_executable(test_fltk test_fltk.cpp)
target_link_libraries(test_fltk PRIVATE project_warnings project_options fltk::fltk)
