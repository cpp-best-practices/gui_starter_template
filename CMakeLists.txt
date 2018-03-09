cmake_minimum_required(VERSION 3.2)

# Link this 'library' to use the following warnings
add_library(project_warnings INTERFACE)

if (CMAKE_COMPILER_IS_GNUCC)
  option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

  if (ENABLE_COVERAGE)
    add_compile_options(--coverage -O0)
  endif()
endif()

if (MSVC)
  target_compile_options(project_warnings INTERFACE /W4)
else()
  target_compile_options(project_warnings INTERFACE -Wall -Wextra -Wpedantic)
endif()

add_executable(intro main.cpp)
target_compile_features(intro PRIVATE cxx_lambda_init_captures)
target_link_libraries(intro PRIVATE project_warnings)

target_link_libraries(intro --coverage)

enable_testing()

add_executable(tester tester.cpp)
target_link_libraries(tester PRIVATE project_warnings)

target_link_libraries(tester --coverage)
add_test(Tester tester)


