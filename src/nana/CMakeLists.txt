include(ExternalProject)
ExternalProject_Add(
  Nana
  GIT_REPOSITORY https://github.com/cnjinhao/nana.git
  GIT_TAG v1.6.2
  CMAKE_CACHE_ARGS "-DNANA_CMAKE_SHARED_LIB:BOOL=TRUE"
  INSTALL_COMMAND "")

# ExternalProject_Get_Property(Nana NANA_INCLUDE_DIR)
ExternalProject_Get_Property(Nana SOURCE_DIR BINARY_DIR)
add_executable(test_nana main.cpp)
target_include_directories(test_nana PRIVATE ${SOURCE_DIR}/include)
add_dependencies(test_nana Nana)
target_link_libraries(
  test_nana
  PRIVATE project_warnings
          project_options
          ${BINARY_DIR}/libnana.so
          ${NANA_LINKS})
