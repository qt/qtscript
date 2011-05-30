load(qt_module)

TARGET  = qtscriptdbus
load(qt_plugin)
QT = core gui script
CONFIG += qdbus

SOURCES += main.cpp
HEADERS += main.h

DESTDIR = $$QT_BUILD_TREE/plugins/script
target.path += $$[QT_INSTALL_PLUGINS]/script
INSTALLS += target
