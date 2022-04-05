
# A very simple example of a configured file that might need to be
# converted to one that is publicly installed in the case that
# you are developing a library

set (configured_file_dir "${CMAKE_BINARY_DIR}/configured_files/include/internal_use_only")

set (configured_file "${configured_file_dir}/config.hpp")

configure_file ("config.hpp.in" "${configured_file}" ESCAPE_QUOTES @ONLY)

include (GNUInstallDirs)

set (file_install_dir "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")

install (FILES "${configured_file}" 
		 DESTINATION "${file_install_dir}"
		 COMPONENT "${PROJECT_NAME}")

add_library (configured_header_interface INTERFACE)

target_include_directories (configured_header_interface INTERFACE 
							$<BUILD_INTERFACE:${configured_file_dir}>
							$<INSTALL_INTERFACE:${file_install_dir}>)

target_sources (configured_header_interface INTERFACE
				$<BUILD_INTERFACE:${configured_file}>
				$<INSTALL_INTERFACE:${file_install_dir}/config.hpp>)

unset (configured_file)
unset (configured_file_dir)
unset (file_install_dir)
