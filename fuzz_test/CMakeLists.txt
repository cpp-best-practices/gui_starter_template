# A fuzz test runs until it finds an error. This particular one is going to rely on libFuzzer.
#

find_package(fmt)

add_executable(fuzz_tester fuzz_tester.cpp)
target_link_libraries(
  fuzz_tester
  PRIVATE project_options
          project_warnings
          fmt::fmt
          -coverage
          -fsanitize=fuzzer,undefined,address)
target_compile_options(fuzz_tester PRIVATE -fsanitize=fuzzer,undefined,address)

# Allow short runs during automated testing to see if something new breaks
set(FUZZ_RUNTIME
    10
    CACHE STRING "Number of seconds to run fuzz tests during ctest run") # Default of 10 seconds

add_test(NAME fuzz_tester_run COMMAND fuzz_tester -max_total_time=${FUZZ_RUNTIME})
