find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
add_executable(helloQt qtMain.cpp HelloQt.cpp)
# set_target_properties( helloQt PROPERTIES CMAKE_AUTOMOC ON )
target_link_libraries(
  helloQt
  project_warnings
  project_options
  Qt5::Widgets)
target_compile_features(helloQt PUBLIC cxx_nullptr cxx_lambdas)
