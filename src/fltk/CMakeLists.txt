find_package(FLTK REQUIRED)
add_executable(test_fltk test_fltk.cpp)
target_link_libraries(test_fltk PRIVATE project_warnings project_options ${FLTK_LIBRARIES})
target_include_directories(test_fltk PRIVATE ${FLTK_INCLUDE_DIR})
