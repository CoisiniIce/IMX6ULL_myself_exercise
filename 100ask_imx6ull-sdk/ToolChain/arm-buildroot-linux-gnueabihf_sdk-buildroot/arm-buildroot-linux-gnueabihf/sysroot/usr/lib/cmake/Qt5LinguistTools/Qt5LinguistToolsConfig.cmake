
if (CMAKE_VERSION VERSION_LESS 2.8.3)
    message(FATAL_ERROR "Qt 5 requires at least CMake version 2.8.3")
endif()

get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
# Use original install prefix when loaded through a
# cross-prefix symbolic link such as /lib -> /usr/lib.
get_filename_component(_realCurr "${_IMPORT_PREFIX}" REALPATH)
get_filename_component(_realOrig "/usr/lib/cmake/Qt5LinguistTools" REALPATH)
if(_realCurr STREQUAL _realOrig)
    get_filename_component(_qt5_linguisttools_install_prefix "/usr/lib/../" ABSOLUTE)
else()
    get_filename_component(_qt5_linguisttools_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)
endif()
unset(_realOrig)
unset(_realCurr)
unset(_IMPORT_PREFIX)

macro(_qt5_LinguistTools_check_file_exists file)
    if(NOT EXISTS "${file}" )
        message(FATAL_ERROR "The package \"Qt5LinguistTools\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    endif()
endmacro()

if (NOT TARGET Qt5::lrelease)
    add_executable(Qt5::lrelease IMPORTED)

    set(imported_location "/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/bin/lrelease")
    _qt5_LinguistTools_check_file_exists(${imported_location})

    set_target_properties(Qt5::lrelease PROPERTIES
        IMPORTED_LOCATION ${imported_location}
    )
endif()

if (NOT TARGET Qt5::lupdate)
    add_executable(Qt5::lupdate IMPORTED)

    set(imported_location "/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/bin/lupdate")
    _qt5_LinguistTools_check_file_exists(${imported_location})

    set_target_properties(Qt5::lupdate PROPERTIES
        IMPORTED_LOCATION ${imported_location}
    )
endif()

if (NOT TARGET Qt5::lconvert)
    add_executable(Qt5::lconvert IMPORTED)

    set(imported_location "/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/bin/lconvert")
    _qt5_LinguistTools_check_file_exists(${imported_location})

    set_target_properties(Qt5::lconvert PROPERTIES
        IMPORTED_LOCATION ${imported_location}
    )
endif()

set(Qt5_LRELEASE_EXECUTABLE Qt5::lrelease)
set(Qt5_LUPDATE_EXECUTABLE Qt5::lupdate)

include("${CMAKE_CURRENT_LIST_DIR}/Qt5LinguistToolsMacros.cmake")
