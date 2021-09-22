from conans import ConanFile


class CppStarterProject(ConanFile):
    name = "CppStarterProject"
    version = "0.1"
    requires = (
        "catch2/2.13.7",
        "docopt.cpp/0.6.2",
        "fmt/8.0.1",
        "spdlog/1.9.2",
        # "imgui-sfml/2.1@bincrafters/stable"
        # "sdl2/2.0.10@bincrafters/stable"
    )
    generators = "cmake", "gcc", "txt", "cmake_find_package"