
if (CMAKE_VERSION VERSION_LESS 3.1.0)
    message(FATAL_ERROR "Qt 5 Bluetooth module requires at least CMake version 3.1.0")
endif()

get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
# Use original install prefix when loaded through a
# cross-prefix symbolic link such as /lib -> /usr/lib.
get_filename_component(_realCurr "${_IMPORT_PREFIX}" REALPATH)
get_filename_component(_realOrig "/usr/lib/cmake/Qt5Bluetooth" REALPATH)
if(_realCurr STREQUAL _realOrig)
    get_filename_component(_qt5Bluetooth_install_prefix "/usr/lib/../" ABSOLUTE)
else()
    get_filename_component(_qt5Bluetooth_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)
endif()
unset(_realOrig)
unset(_realCurr)
unset(_IMPORT_PREFIX)

# For backwards compatibility only. Use Qt5Bluetooth_VERSION instead.
set(Qt5Bluetooth_VERSION_STRING 5.12.8)

set(Qt5Bluetooth_LIBRARIES Qt5::Bluetooth)

macro(_qt5_Bluetooth_check_file_exists file)
    if(NOT EXISTS "${file}" )
        message(FATAL_ERROR "The imported target \"Qt5::Bluetooth\" references the file
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

macro(_populate_Bluetooth_target_properties Configuration LIB_LOCATION IMPLIB_LOCATION)
    set_property(TARGET Qt5::Bluetooth APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})

    set(imported_location "${_qt5Bluetooth_install_prefix}/lib/${LIB_LOCATION}")
    _qt5_Bluetooth_check_file_exists(${imported_location})
    set_target_properties(Qt5::Bluetooth PROPERTIES
        "INTERFACE_LINK_LIBRARIES" "${_Qt5Bluetooth_LIB_DEPENDENCIES}"
        "IMPORTED_LOCATION_${Configuration}" ${imported_location}
        "IMPORTED_SONAME_${Configuration}" "libQt5Bluetooth.so.5"
        # For backward compatibility with CMake < 2.8.12
        "IMPORTED_LINK_INTERFACE_LIBRARIES_${Configuration}" "${_Qt5Bluetooth_LIB_DEPENDENCIES}"
    )

endmacro()

if (NOT TARGET Qt5::Bluetooth)

    set(_Qt5Bluetooth_OWN_INCLUDE_DIRS "${_qt5Bluetooth_install_prefix}/include/qt5/" "${_qt5Bluetooth_install_prefix}/include/qt5/QtBluetooth")
    set(Qt5Bluetooth_PRIVATE_INCLUDE_DIRS
        "${_qt5Bluetooth_install_prefix}/include/qt5/QtBluetooth/5.12.8"
        "${_qt5Bluetooth_install_prefix}/include/qt5/QtBluetooth/5.12.8/QtBluetooth"
    )

    foreach(_dir ${_Qt5Bluetooth_OWN_INCLUDE_DIRS})
        _qt5_Bluetooth_check_file_exists(${_dir})
    endforeach()

    # Only check existence of private includes if the Private component is
    # specified.
    list(FIND Qt5Bluetooth_FIND_COMPONENTS Private _check_private)
    if (NOT _check_private STREQUAL -1)
        foreach(_dir ${Qt5Bluetooth_PRIVATE_INCLUDE_DIRS})
            _qt5_Bluetooth_check_file_exists(${_dir})
        endforeach()
    endif()

    set(Qt5Bluetooth_INCLUDE_DIRS ${_Qt5Bluetooth_OWN_INCLUDE_DIRS})

    set(Qt5Bluetooth_DEFINITIONS -DQT_BLUETOOTH_LIB)
    set(Qt5Bluetooth_COMPILE_DEFINITIONS QT_BLUETOOTH_LIB)
    set(_Qt5Bluetooth_MODULE_DEPENDENCIES "Core")


    set(Qt5Bluetooth_OWN_PRIVATE_INCLUDE_DIRS ${Qt5Bluetooth_PRIVATE_INCLUDE_DIRS})

    set(_Qt5Bluetooth_FIND_DEPENDENCIES_REQUIRED)
    if (Qt5Bluetooth_FIND_REQUIRED)
        set(_Qt5Bluetooth_FIND_DEPENDENCIES_REQUIRED REQUIRED)
    endif()
    set(_Qt5Bluetooth_FIND_DEPENDENCIES_QUIET)
    if (Qt5Bluetooth_FIND_QUIETLY)
        set(_Qt5Bluetooth_DEPENDENCIES_FIND_QUIET QUIET)
    endif()
    set(_Qt5Bluetooth_FIND_VERSION_EXACT)
    if (Qt5Bluetooth_FIND_VERSION_EXACT)
        set(_Qt5Bluetooth_FIND_VERSION_EXACT EXACT)
    endif()

    set(Qt5Bluetooth_EXECUTABLE_COMPILE_FLAGS "")

    foreach(_module_dep ${_Qt5Bluetooth_MODULE_DEPENDENCIES})
        if (NOT Qt5${_module_dep}_FOUND)
            find_package(Qt5${_module_dep}
                5.12.8 ${_Qt5Bluetooth_FIND_VERSION_EXACT}
                ${_Qt5Bluetooth_DEPENDENCIES_FIND_QUIET}
                ${_Qt5Bluetooth_FIND_DEPENDENCIES_REQUIRED}
                PATHS "${CMAKE_CURRENT_LIST_DIR}/.." NO_DEFAULT_PATH
            )
        endif()

        if (NOT Qt5${_module_dep}_FOUND)
            set(Qt5Bluetooth_FOUND False)
            return()
        endif()

        list(APPEND Qt5Bluetooth_INCLUDE_DIRS "${Qt5${_module_dep}_INCLUDE_DIRS}")
        list(APPEND Qt5Bluetooth_PRIVATE_INCLUDE_DIRS "${Qt5${_module_dep}_PRIVATE_INCLUDE_DIRS}")
        list(APPEND Qt5Bluetooth_DEFINITIONS ${Qt5${_module_dep}_DEFINITIONS})
        list(APPEND Qt5Bluetooth_COMPILE_DEFINITIONS ${Qt5${_module_dep}_COMPILE_DEFINITIONS})
        list(APPEND Qt5Bluetooth_EXECUTABLE_COMPILE_FLAGS ${Qt5${_module_dep}_EXECUTABLE_COMPILE_FLAGS})
    endforeach()
    list(REMOVE_DUPLICATES Qt5Bluetooth_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt5Bluetooth_PRIVATE_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt5Bluetooth_DEFINITIONS)
    list(REMOVE_DUPLICATES Qt5Bluetooth_COMPILE_DEFINITIONS)
    list(REMOVE_DUPLICATES Qt5Bluetooth_EXECUTABLE_COMPILE_FLAGS)

    set(_Qt5Bluetooth_LIB_DEPENDENCIES "Qt5::Core")


    add_library(Qt5::Bluetooth SHARED IMPORTED)

    set_property(TARGET Qt5::Bluetooth PROPERTY
      INTERFACE_INCLUDE_DIRECTORIES ${_Qt5Bluetooth_OWN_INCLUDE_DIRS})
    set_property(TARGET Qt5::Bluetooth PROPERTY
      INTERFACE_COMPILE_DEFINITIONS QT_BLUETOOTH_LIB)

    set_property(TARGET Qt5::Bluetooth PROPERTY INTERFACE_QT_ENABLED_FEATURES bluez)
    set_property(TARGET Qt5::Bluetooth PROPERTY INTERFACE_QT_DISABLED_FEATURES )

    set(_Qt5Bluetooth_PRIVATE_DIRS_EXIST TRUE)
    foreach (_Qt5Bluetooth_PRIVATE_DIR ${Qt5Bluetooth_OWN_PRIVATE_INCLUDE_DIRS})
        if (NOT EXISTS ${_Qt5Bluetooth_PRIVATE_DIR})
            set(_Qt5Bluetooth_PRIVATE_DIRS_EXIST FALSE)
        endif()
    endforeach()

    if (_Qt5Bluetooth_PRIVATE_DIRS_EXIST)
        add_library(Qt5::BluetoothPrivate INTERFACE IMPORTED)
        set_property(TARGET Qt5::BluetoothPrivate PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES ${Qt5Bluetooth_OWN_PRIVATE_INCLUDE_DIRS}
        )
        set(_Qt5Bluetooth_PRIVATEDEPS)
        foreach(dep ${_Qt5Bluetooth_LIB_DEPENDENCIES})
            if (TARGET ${dep}Private)
                list(APPEND _Qt5Bluetooth_PRIVATEDEPS ${dep}Private)
            endif()
        endforeach()
        set_property(TARGET Qt5::BluetoothPrivate PROPERTY
            INTERFACE_LINK_LIBRARIES Qt5::Bluetooth ${_Qt5Bluetooth_PRIVATEDEPS}
        )
    endif()

    _populate_Bluetooth_target_properties(RELEASE "libQt5Bluetooth.so.5.12.8" "" )




    file(GLOB pluginTargets "${CMAKE_CURRENT_LIST_DIR}/Qt5Bluetooth_*Plugin.cmake")

    macro(_populate_Bluetooth_plugin_properties Plugin Configuration PLUGIN_LOCATION)
        set_property(TARGET Qt5::${Plugin} APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})

        set(imported_location "${_qt5Bluetooth_install_prefix}/lib/qt/plugins/${PLUGIN_LOCATION}")
        _qt5_Bluetooth_check_file_exists(${imported_location})
        set_target_properties(Qt5::${Plugin} PROPERTIES
            "IMPORTED_LOCATION_${Configuration}" ${imported_location}
        )
    endmacro()

    if (pluginTargets)
        foreach(pluginTarget ${pluginTargets})
            include(${pluginTarget})
        endforeach()
    endif()




_qt5_Bluetooth_check_file_exists("${CMAKE_CURRENT_LIST_DIR}/Qt5BluetoothConfigVersion.cmake")

endif()
