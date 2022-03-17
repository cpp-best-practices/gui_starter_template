
find_package(fmt)
find_package(spdlog)
find_package(docopt)
find_package(ImGui-SFML REQUIRED)

# Generic test that uses conan libs
add_executable(imgui-sfml-example main.cpp)
target_link_libraries(
  imgui-sfml-example
  PRIVATE project_options
          project_warnings
          docopt::docopt
          fmt::fmt
          spdlog::spdlog
          ImGui-SFML::ImGui-SFML)
