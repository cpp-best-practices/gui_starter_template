cmake_minimum_required(VERSION 3.8)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" FALSE)

# Link this 'library' to use the following warnings
add_library(project_warnings INTERFACE)

if(CMAKE_COMPILER_IS_GNUCC)
  option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

  if(ENABLE_COVERAGE)
    add_compile_options(--coverage -O0)
  endif()
endif()

if(MSVC)
  target_compile_options(project_warnings INTERFACE /W4)
else()
  target_compile_options(project_warnings
                         INTERFACE
                         -Wall
                         -Wextra # reasonable and standard
                         -Wshadow # warn the user if a variable declaration shadows one from a
                                  # parent context
                         -Wnon-virtual-dtor # warn the user if a class with virtual functions has a
                                            # non-virtual destructor. This helps catch hard to
                                            # track down memory errors
                         -Wold-style-cast # warn for c-style casts
                         -Wcast-align # warn for potential performance problem casts
                         -Wunused # warn on anything being unused
                         -Woverloaded-virtual # warn if you overload (not override) a virtual
                                              # function
                         -Wpedantic # warn if non-standard C++ is used
                         -Wconversion # warn on type conversions that may lose data
                         -Wsign-conversion # warn on sign conversions
			 -Wmisleading-indentation # warn if identation implies blocks where blocks do not exist
			 -Wduplicated-cond # warn if if / else chain has duplicated conditions
			 -Wduplicated-branches # warn if if / else branches have duplicated code
                         -Wlogical-op # warn about logical operations being used where bitwise were
                                      # probably wanted
			 -Wnull-dereference # warn if a null dereference is detected
                         -Wuseless-cast # warn if you perform a cast to the same type
                         -Wdouble-promotion # warn if float is implicit promoted to double
                         -Wformat=2 # warn on security issues around functions that format output
                                    # (ie printf)
                         )
endif()

add_executable(intro main.cpp)
target_compile_features(intro PRIVATE cxx_std_17)
target_link_libraries(intro PRIVATE project_warnings --coverage)

enable_testing()

add_executable(tester tester.cpp)
target_link_libraries(tester PRIVATE project_warnings --coverage)

add_test(Tester tester)

#qt
if( DEFINED CPP_STARTER_USE_QT )
message( "Using Qt" )
add_subdirectory(qt)
endif()

#fltk test
if( DEFINED CPP_STARTER_USE_FLTK )
find_package(FLTK REQUIRED)
add_executable(test_fltk fltk/test_fltk.cpp)
target_link_libraries(test_fltk PRIVATE project_warnings ${FLTK_LIBRARIES})
target_include_directories(test_fltk PRIVATE ${FLTK_INCLUDE_DIR})
endif()

# gtkmm test
if( DEFINED CPP_STARTER_USE_GTKMM )
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
add_executable(test_gtkmm gtkmm/main.cpp gtkmm/hello_world.cpp)
target_link_libraries(test_gtkmm PRIVATE project_warnings ${GTKMM_LIBRARIES})
target_include_directories(test_gtkmm PRIVATE ${GTKMM_INCLUDE_DIRS})
endif()

# imgui example
if( DEFINED CPP_STARTER_USE_IMGUI )
find_package(SFML COMPONENTS graphics window system)
find_package(OpenGL)

# imgui + sfml built as a lib, intentionally not using full warning flags
add_library(imgui imgui/lib/imgui.cpp imgui/lib/imgui_draw.cpp imgui/lib/imgui-SFML.cpp)
target_link_libraries(imgui INTERFACE ${SFML_LIBRARIES} ${OPENGL_gl_LIBRARY})

# imgui test executable, with full warnings enabled
add_executable(test_imgui imgui/test.cpp)
target_link_libraries(test_imgui PRIVATE project_warnings imgui)
target_include_directories(test_imgui PRIVATE ${SFML_INCLUDE_DIR})
endif()

# Nana
if( DEFINED CPP_STARTER_USE_NANA )
include(ExternalProject)
ExternalProject_add(
  Nana
  GIT_REPOSITORY   https://github.com/cnjinhao/nana.git
  GIT_TAG          v1.5.6
  CMAKE_CACHE_ARGS "-DNANA_CMAKE_SHARED_LIB"
  INSTALL_COMMAND  ""
)

#ExternalProject_Get_Property(Nana NANA_INCLUDE_DIR)
ExternalProject_Get_Property(Nana SOURCE_DIR BINARY_DIR)
add_executable(test_nana nana/main.cpp)
target_include_directories(test_nana PRIVATE ${SOURCE_DIR}/include)
target_link_libraries(test_nana PRIVATE ${BINARY_DIR}/libnana.so ${NANA_LINKS})
endif()
