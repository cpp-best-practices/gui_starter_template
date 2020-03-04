include(GoogleTest)
add_executable(gtests main_gtests.cpp tests.cpp)
target_include_directories(gtests PRIVATE ${CONAN_GTEST_ROOT}/include)

target_link_libraries(
        gtests
        PRIVATE project_warnings project_options
        PUBLIC CONAN_PKG::gtest)
