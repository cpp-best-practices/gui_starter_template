# Copyright Tomas Zeman 2019-2020.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#
# See https://github.com/zemasoft/clangformat-cmake

function(prefix_clangformat_setup prefix)
  if(NOT CLANGFORMAT_EXECUTABLE)
    set(CLANGFORMAT_EXECUTABLE clang-format)
  endif()

  if(NOT EXISTS ${CLANGFORMAT_EXECUTABLE})
    find_program(clangformat_executable_tmp ${CLANGFORMAT_EXECUTABLE})
    if(clangformat_executable_tmp)
      set(CLANGFORMAT_EXECUTABLE ${clangformat_executable_tmp})
      unset(clangformat_executable_tmp)
    else()
      message(FATAL_ERROR "ClangFormat: ${CLANGFORMAT_EXECUTABLE} not found! Aborting")
    endif()
  endif()

  foreach(clangformat_source ${ARGN})
    get_filename_component(clangformat_source ${clangformat_source} ABSOLUTE)
    list(APPEND clangformat_sources ${clangformat_source})
  endforeach()

  add_custom_target(${prefix}_clangformat
    COMMAND
      ${CLANGFORMAT_EXECUTABLE}
      -style=file
      -i
      ${clangformat_sources}
    WORKING_DIRECTORY
      ${CMAKE_SOURCE_DIR}
    COMMENT
      "Formatting ${prefix} with ${CLANGFORMAT_EXECUTABLE} ..."
  )

  if(TARGET clangformat)
    add_dependencies(clangformat ${prefix}_clangformat)
  else()
    add_custom_target(clangformat DEPENDS ${prefix}_clangformat)
  endif()
endfunction()

function(clangformat_setup)
  prefix_clangformat_setup(${PROJECT_NAME} ${ARGN})
endfunction()

function(target_clangformat_setup target)
  get_target_property(target_sources ${target} SOURCES)
  prefix_clangformat_setup(${target} ${target_sources})
endfunction()
