
if (CMAKE_VERSION VERSION_LESS 3.1.0)
    message(FATAL_ERROR "Qt 5 Sql module requires at least CMake version 3.1.0")
endif()

get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
# Use original install prefix when loaded through a
# cross-prefix symbolic link such as /lib -> /usr/lib.
get_filename_component(_realCurr "${_IMPORT_PREFIX}" REALPATH)
get_filename_component(_realOrig "/usr/lib/cmake/Qt5Sql" REALPATH)
if(_realCurr STREQUAL _realOrig)
    get_filename_component(_qt5Sql_install_prefix "/usr/lib/../" ABSOLUTE)
else()
    get_filename_component(_qt5Sql_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)
endif()
unset(_realOrig)
unset(_realCurr)
unset(_IMPORT_PREFIX)

# For backwards compatibility only. Use Qt5Sql_VERSION instead.
set(Qt5Sql_VERSION_STRING 5.12.8)

set(Qt5Sql_LIBRARIES Qt5::Sql)

macro(_qt5_Sql_check_file_exists file)
    if(NOT EXISTS "${file}" )
        message(FATAL_ERROR "The imported target \"Qt5::Sql\" references the file
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

macro(_populate_Sql_target_properties Configuration LIB_LOCATION IMPLIB_LOCATION)
    set_property(TARGET Qt5::Sql APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})

    set(imported_location "${_qt5Sql_install_prefix}/lib/${LIB_LOCATION}")
    _qt5_Sql_check_file_exists(${imported_location})
    set_target_properties(Qt5::Sql PROPERTIES
        "INTERFACE_LINK_LIBRARIES" "${_Qt5Sql_LIB_DEPENDENCIES}"
        "IMPORTED_LOCATION_${Configuration}" ${imported_location}
        "IMPORTED_SONAME_${Configuration}" "libQt5Sql.so.5"
        # For backward compatibility with CMake < 2.8.12
        "IMPORTED_LINK_INTERFACE_LIBRARIES_${Configuration}" "${_Qt5Sql_LIB_DEPENDENCIES}"
    )

endmacro()

if (NOT TARGET Qt5::Sql)

    set(_Qt5Sql_OWN_INCLUDE_DIRS "${_qt5Sql_install_prefix}/include/qt5/" "${_qt5Sql_install_prefix}/include/qt5/QtSql")
    set(Qt5Sql_PRIVATE_INCLUDE_DIRS
        "${_qt5Sql_install_prefix}/include/qt5/QtSql/5.12.8"
        "${_qt5Sql_install_prefix}/include/qt5/QtSql/5.12.8/QtSql"
    )

    foreach(_dir ${_Qt5Sql_OWN_INCLUDE_DIRS})
        _qt5_Sql_check_file_exists(${_dir})
    endforeach()

    # Only check existence of private includes if the Private component is
    # specified.
    list(FIND Qt5Sql_FIND_COMPONENTS Private _check_private)
    if (NOT _check_private STREQUAL -1)
        foreach(_dir ${Qt5Sql_PRIVATE_INCLUDE_DIRS})
            _qt5_Sql_check_file_exists(${_dir})
        endforeach()
    endif()

    set(Qt5Sql_INCLUDE_DIRS ${_Qt5Sql_OWN_INCLUDE_DIRS})

    set(Qt5Sql_DEFINITIONS -DQT_SQL_LIB)
    set(Qt5Sql_COMPILE_DEFINITIONS QT_SQL_LIB)
    set(_Qt5Sql_MODULE_DEPENDENCIES "Core")


    set(Qt5Sql_OWN_PRIVATE_INCLUDE_DIRS ${Qt5Sql_PRIVATE_INCLUDE_DIRS})

    set(_Qt5Sql_FIND_DEPENDENCIES_REQUIRED)
    if (Qt5Sql_FIND_REQUIRED)
        set(_Qt5Sql_FIND_DEPENDENCIES_REQUIRED REQUIRED)
    endif()
    set(_Qt5Sql_FIND_DEPENDENCIES_QUIET)
    if (Qt5Sql_FIND_QUIETLY)
        set(_Qt5Sql_DEPENDENCIES_FIND_QUIET QUIET)
    endif()
    set(_Qt5Sql_FIND_VERSION_EXACT)
    if (Qt5Sql_FIND_VERSION_EXACT)
        set(_Qt5Sql_FIND_VERSION_EXACT EXACT)
    endif()

    set(Qt5Sql_EXECUTABLE_COMPILE_FLAGS "")

    foreach(_module_dep ${_Qt5Sql_MODULE_DEPENDENCIES})
        if (NOT Qt5${_module_dep}_FOUND)
            find_package(Qt5${_module_dep}
                5.12.8 ${_Qt5Sql_FIND_VERSION_EXACT}
                ${_Qt5Sql_DEPENDENCIES_FIND_QUIET}
                ${_Qt5Sql_FIND_DEPENDENCIES_REQUIRED}
                PATHS "${CMAKE_CURRENT_LIST_DIR}/.." NO_DEFAULT_PATH
            )
        endif()

        if (NOT Qt5${_module_dep}_FOUND)
            set(Qt5Sql_FOUND False)
            return()
        endif()

        list(APPEND Qt5Sql_INCLUDE_DIRS "${Qt5${_module_dep}_INCLUDE_DIRS}")
        list(APPEND Qt5Sql_PRIVATE_INCLUDE_DIRS "${Qt5${_module_dep}_PRIVATE_INCLUDE_DIRS}")
        list(APPEND Qt5Sql_DEFINITIONS ${Qt5${_module_dep}_DEFINITIONS})
        list(APPEND Qt5Sql_COMPILE_DEFINITIONS ${Qt5${_module_dep}_COMPILE_DEFINITIONS})
        list(APPEND Qt5Sql_EXECUTABLE_COMPILE_FLAGS ${Qt5${_module_dep}_EXECUTABLE_COMPILE_FLAGS})
    endforeach()
    list(REMOVE_DUPLICATES Qt5Sql_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt5Sql_PRIVATE_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt5Sql_DEFINITIONS)
    list(REMOVE_DUPLICATES Qt5Sql_COMPILE_DEFINITIONS)
    list(REMOVE_DUPLICATES Qt5Sql_EXECUTABLE_COMPILE_FLAGS)

    set(_Qt5Sql_LIB_DEPENDENCIES "Qt5::Core")


    add_library(Qt5::Sql SHARED IMPORTED)

    set_property(TARGET Qt5::Sql PROPERTY
      INTERFACE_INCLUDE_DIRECTORIES ${_Qt5Sql_OWN_INCLUDE_DIRS})
    set_property(TARGET Qt5::Sql PROPERTY
      INTERFACE_COMPILE_DEFINITIONS QT_SQL_LIB)

    set_property(TARGET Qt5::Sql PROPERTY INTERFACE_QT_ENABLED_FEATURES sqlmodel)
    set_property(TARGET Qt5::Sql PROPERTY INTERFACE_QT_DISABLED_FEATURES )

    set(_Qt5Sql_PRIVATE_DIRS_EXIST TRUE)
    foreach (_Qt5Sql_PRIVATE_DIR ${Qt5Sql_OWN_PRIVATE_INCLUDE_DIRS})
        if (NOT EXISTS ${_Qt5Sql_PRIVATE_DIR})
            set(_Qt5Sql_PRIVATE_DIRS_EXIST FALSE)
        endif()
    endforeach()

    if (_Qt5Sql_PRIVATE_DIRS_EXIST)
        add_library(Qt5::SqlPrivate INTERFACE IMPORTED)
        set_property(TARGET Qt5::SqlPrivate PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES ${Qt5Sql_OWN_PRIVATE_INCLUDE_DIRS}
        )
        set(_Qt5Sql_PRIVATEDEPS)
        foreach(dep ${_Qt5Sql_LIB_DEPENDENCIES})
            if (TARGET ${dep}Private)
                list(APPEND _Qt5Sql_PRIVATEDEPS ${dep}Private)
            endif()
        endforeach()
        set_property(TARGET Qt5::SqlPrivate PROPERTY
            INTERFACE_LINK_LIBRARIES Qt5::Sql ${_Qt5Sql_PRIVATEDEPS}
        )
    endif()

    _populate_Sql_target_properties(RELEASE "libQt5Sql.so.5.12.8" "" )




    file(GLOB pluginTargets "${CMAKE_CURRENT_LIST_DIR}/Qt5Sql_*Plugin.cmake")

    macro(_populate_Sql_plugin_properties Plugin Configuration PLUGIN_LOCATION)
        set_property(TARGET Qt5::${Plugin} APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})

        set(imported_location "${_qt5Sql_install_prefix}/lib/qt/plugins/${PLUGIN_LOCATION}")
        _qt5_Sql_check_file_exists(${imported_location})
        set_target_properties(Qt5::${Plugin} PROPERTIES
            "IMPORTED_LOCATION_${Configuration}" ${imported_location}
        )
    endmacro()

    if (pluginTargets)
        foreach(pluginTarget ${pluginTargets})
            include(${pluginTarget})
        endforeach()
    endif()




_qt5_Sql_check_file_exists("${CMAKE_CURRENT_LIST_DIR}/Qt5SqlConfigVersion.cmake")

endif()
