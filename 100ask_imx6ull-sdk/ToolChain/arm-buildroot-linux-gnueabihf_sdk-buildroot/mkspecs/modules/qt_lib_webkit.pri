QT.webkit.VERSION = 5.9.1
QT.webkit.name = QtWebKit
QT.webkit.module = Qt5WebKit
QT.webkit.libs = $$QT_MODULE_LIB_BASE
QT.webkit.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtWebKit
QT.webkit.frameworks =
QT.webkit.bins = $$QT_MODULE_BIN_BASE
QT.webkit.depends = core gui network
QT.webkit.run_depends = sensors positioning qml quick webchannel sql core_private gui_private
QT.webkit.uses =
QT.webkit.module_config = v2
QT.webkit.DEFINES = QT_WEBKIT_LIB
QT.webkit.enabled_features =
QT.webkit.disabled_features =
QT_CONFIG +=
QT_MODULES += webkit
