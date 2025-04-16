!host_build {
    QMAKE_CFLAGS    += --sysroot=$$[QT_SYSROOT]
    QMAKE_CXXFLAGS  += --sysroot=$$[QT_SYSROOT]
    QMAKE_LFLAGS    += --sysroot=$$[QT_SYSROOT]
}
host_build {
    QT_ARCH = x86_64
    QT_BUILDABI = x86_64-little_endian-lp64
    QT_TARGET_ARCH = arm
    QT_TARGET_BUILDABI = arm-little_endian-ilp32-eabi-hardfloat
} else {
    QT_ARCH = arm
    QT_BUILDABI = arm-little_endian-ilp32-eabi-hardfloat
}
QT.global.enabled_features = cross_compile shared c++11 c++14 c++1z c99 c11 thread future concurrent pkg-config
QT.global.disabled_features = framework rpath appstore-compliant debug_and_release simulator_and_device build_all force_asserts separate_debug_info static
PKG_CONFIG_SYSROOT_DIR = /home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/arm-buildroot-linux-gnueabihf/sysroot
PKG_CONFIG_LIBDIR = /home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/pkgconfig:/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/share/pkgconfig:/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/arm-buildroot-linux-gnueabihf/pkgconfig
CONFIG += cross_compile shared release
QT_CONFIG += shared release c++11 c++14 c++1z concurrent dbus reduce_exports release_tools stl
QT_VERSION = 5.12.8
QT_MAJOR_VERSION = 5
QT_MINOR_VERSION = 12
QT_PATCH_VERSION = 8
QT_GCC_MAJOR_VERSION = 7
QT_GCC_MINOR_VERSION = 5
QT_GCC_PATCH_VERSION = 0
QT_EDITION = OpenSource
