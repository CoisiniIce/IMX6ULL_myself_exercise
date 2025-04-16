GENCCODE_ASSEMBLY_TYPE=-a gcc
SO=so
SOBJ=so
A=a
LIBPREFIX=lib
LIB_EXT_ORDER=.65.1
COMPILE=/usr/bin/gcc -I/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/include -D_REENTRANT  -DU_HAVE_ELF_H=1 -DU_HAVE_STRTOD_L=1 -DU_HAVE_XLOCALE_H=0  -DU_DISABLE_RENAMING=1 -DU_ATTRIBUTE_DEPRECATED= -O2 -I/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/include -std=c11 -pedantic -Wshadow -Wpointer-arith -Wmissing-prototypes -Wwrite-strings   -c
LIBFLAGS=-I/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/include -DPIC -fPIC
GENLIB=/usr/bin/gcc -O2 -I/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/include -std=c11 -pedantic -Wshadow -Wpointer-arith -Wmissing-prototypes -Wwrite-strings   -L/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/lib -Wl,-rpath,/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/lib  -shared -Wl,-Bsymbolic
LDICUDTFLAGS=
LD_SONAME=-Wl,-soname -Wl,
RPATH_FLAGS=
BIR_LDFLAGS=-Wl,-Bsymbolic
AR=/usr/bin/ar
ARFLAGS=r
RANLIB=/usr/bin/ranlib
INSTALL_CMD=/usr/bin/install -c
