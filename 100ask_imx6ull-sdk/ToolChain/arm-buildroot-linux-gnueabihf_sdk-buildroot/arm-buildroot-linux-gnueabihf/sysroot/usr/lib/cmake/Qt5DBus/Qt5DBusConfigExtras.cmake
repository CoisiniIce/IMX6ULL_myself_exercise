
if (NOT TARGET Qt5::qdbuscpp2xml)
    add_executable(Qt5::qdbuscpp2xml IMPORTED)

    set(imported_location "/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/bin/qdbuscpp2xml")
    _qt5_DBus_check_file_exists(${imported_location})

    set_target_properties(Qt5::qdbuscpp2xml PROPERTIES
        IMPORTED_LOCATION ${imported_location}
    )
endif()

if (NOT TARGET Qt5::qdbusxml2cpp)
    add_executable(Qt5::qdbusxml2cpp IMPORTED)

    set(imported_location "/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/bin/qdbusxml2cpp")
    _qt5_DBus_check_file_exists(${imported_location})

    set_target_properties(Qt5::qdbusxml2cpp PROPERTIES
        IMPORTED_LOCATION ${imported_location}
    )
endif()

set(Qt5DBus_QDBUSCPP2XML_EXECUTABLE Qt5::qdbuscpp2xml)
set(Qt5DBus_QDBUSXML2CPP_EXECUTABLE Qt5::qdbusxml2cpp)
