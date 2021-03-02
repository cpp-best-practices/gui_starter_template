macro(run_conan)
  # Download automatically, you can also just copy the conan.cmake file
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
  endif()

  include(${CMAKE_BINARY_DIR}/conan.cmake)

  conan_add_remote(
    NAME
    bincrafters
    URL
    https://api.bintray.com/conan/bincrafters/public-conan)

  conan_cmake_run(
    CONANFILE
    conanfile.py
    OPTIONS
    cpp_starter_use_imgui=${CPP_STARTER_USE_IMGUI}
    cpp_starter_use_sdl=${CPP_STARTER_USE_SDL}
    BASIC_SETUP
    CMAKE_TARGETS # individual targets to link to
    BUILD
    missing)
endmacro()
