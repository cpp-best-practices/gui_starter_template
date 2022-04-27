# cmake_conan_boilerplate_template

[![ci](https://github.com/cpp-best-practices/cmake_conan_boilerplate_template/actions/workflows/ci.yml/badge.svg)](https://github.com/cpp-best-practices/cmake_conan_boilerplate_template/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/cpp-best-practices/cmake_conan_boilerplate_template/branch/main/graph/badge.svg)](https://codecov.io/gh/cpp-best-practices/cmake_conan_boilerplate_template)
[![Language grade: C++](https://img.shields.io/lgtm/grade/cpp/github/cpp-best-practices/cmake_conan_boilerplate_template)](https://lgtm.com/projects/g/cpp-best-practices/cmake_conan_boilerplate_template/context:cpp)
[![CodeQL](https://github.com/cpp-best-practices/cmake_conan_boilerplate_template/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/cpp-best-practices/cmake_conan_boilerplate_template/actions/workflows/codeql-analysis.yml)

## About cmake_conan_boilerplate_template

This is a C++ Best Practices GitHub template for getting up and running with C++ quickly.

By default (collectively known as `ENABLE_DEVELOPER_MODE`)

 * Address Sanitizer and Undefined Behavior Sanitizer enabled where possible
 * Warnings as errors
 * clang-tidy and cppcheck static analysis
 * conan for dependencies

It includes

 * a basic CLI example
 * examples for fuzz, unit, and constexpr testing
 * large github action testing matrix

It requires

 * cmake
 * conan
 * a compiler

If you want a more complex example project, check out the [cpp_starter_project](https://github.com/cpp-best-practices/cpp_starter_project).

Ths Boilerplate project will merge new features first, then they will be merged (as appropriate) into cpp_starter_project.

## Getting Started

### Use the Github template
First, click the green `Use this template` button near the top of this page.
This will take you to Github's ['Generate Repository'](https://github.com/cpp-best-practices/cmake_conan_boilerplate_template/generate) page.
Fill in a repository name and short description, and click 'Create repository from template'.
This will allow you to create a new repository in your Github account,
prepopulated with the contents of this project.

After creating the project please wait until the cleanup workflow has finished 
setting up your project and commited the changes.

Now you can clone the project locally and get to work!

    git clone https://github.com/<user>/<your_new_repo>.git

## More Details

 * [Dependency Setup](README_dependencies.md)
 * [Building Details](README_building.md)
 * [Troubleshooting](README_troubleshooting.md)
 * [Docker](README_docker.md)

## Testing

See [Catch2 tutorial](https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md)

## Fuzz testing

See [libFuzzer Tutorial](https://github.com/google/fuzzing/blob/master/tutorial/libFuzzerTutorial.md)


