cmake_minimum_required(VERSION 2.8.11)

if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

project(minimal_qt)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

add_executable(
    minimal_qt
    main.cpp
)

target_link_libraries(minimal_qt
    Qt5::Widgets
)

if(WIN32)
    target_link_libraries(minimal_qt
        Qt5::WinMain
    )

    # Disable common Qt warnings
    set_target_properties(minimal_qt
        PROPERTIES COMPILE_FLAGS "/wd4127 /wd4244 /wd4251 /wd4800"
    )

    # Run windeployqt.exe to copy required Qt dlls into bin folder
    add_custom_command(
        TARGET minimal_qt
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E env
            PATH=${QT_DIR}/bin
            windeployqt.exe $<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>,$<CONFIG:RelWithDebInfo>>:--release> $<TARGET_FILE:minimal_qt>
    )
endif()

# Prevent console window popping up
if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE YES
    )
endif()
