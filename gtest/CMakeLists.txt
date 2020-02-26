include(GoogleTest)
add_executable(gtests main_gtests.cpp tests.cpp)
target_include_directories(gtests PRIVATE ${CONAN_GTEST_ROOT}/include)

target_link_libraries(
        gtests
        PUBLIC CONAN_PKG::gtest)
