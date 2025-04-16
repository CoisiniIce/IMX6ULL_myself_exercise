import sys
import gdb

# Update module path.
dir_ = '/home/book/100ask_imx6ull-sdk/Buildroot_2020.02.x/output/host/share/glib-2.0/gdb'
if not dir_ in sys.path:
    sys.path.insert(0, dir_)

from glib_gdb import register
register (gdb.current_objfile ())
