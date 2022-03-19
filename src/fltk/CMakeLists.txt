find_package(FLTK CONFIG)
add_executable(test_fltk test_fltk.cpp)
target_link_libraries(test_fltk PRIVATE project_warnings project_options fltk::fltk)
