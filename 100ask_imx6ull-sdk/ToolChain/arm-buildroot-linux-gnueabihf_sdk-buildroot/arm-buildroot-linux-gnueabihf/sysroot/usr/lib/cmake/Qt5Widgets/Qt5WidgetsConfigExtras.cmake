
if (NOT TARGET Qt5::uic)
    add_executable(Qt5::uic IMPORTED)

    set(imported_location "/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/bin/uic")
    _qt5_Widgets_check_file_exists(${imported_location})

    set_target_properties(Qt5::uic PROPERTIES
        IMPORTED_LOCATION ${imported_location}
    )
endif()

include("${CMAKE_CURRENT_LIST_DIR}/Qt5Widgets_AccessibleFactory.cmake" OPTIONAL)

set(Qt5Widgets_UIC_EXECUTABLE Qt5::uic)
