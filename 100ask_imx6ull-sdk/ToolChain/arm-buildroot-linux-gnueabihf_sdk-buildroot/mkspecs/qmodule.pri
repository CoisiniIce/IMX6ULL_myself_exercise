host_build {
    QT_CPU_FEATURES.x86_64 = mmx sse sse2
} else {
    QT_CPU_FEATURES.arm = neon
}
QT.global_private.enabled_features = alloca_h alloca dbus dbus-linked gui libudev network posix_fallocate reduce_exports release_tools sql system-zlib testlib widgets xml
QT.global_private.disabled_features = sse2 alloca_malloc_h android-style-assets avx2 private_tests gc_binaries reduce_relocations stack-protector-strong
PKG_CONFIG_EXECUTABLE = /home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/bin/pkg-config
QMAKE_LIBS_DBUS = /home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/libdbus-1.so
QMAKE_INCDIR_DBUS = /home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/dbus-1.0 /home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/dbus-1.0/include
QMAKE_LIBS_LIBUDEV = /home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/libudev.so
QT_COORD_TYPE = double
QMAKE_LIBS_ZLIB = /home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/libz.so
CONFIG -= precompile_header
CONFIG += cross_compile compile_examples enable_new_dtags largefile neon
QT_BUILD_PARTS += examples libs
QT_HOST_CFLAGS_DBUS += -I/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/bin/../arm-buildroot-linux-gnueabihf/sysroot/usr/include/dbus-1.0 -I/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/bin/../arm-buildroot-linux-gnueabihf/sysroot/usr/lib/dbus-1.0/include
