load(qt_module)

TARGET  = qtscriptdbus
include($$QT_SOURCE_TREE/src/plugins/qpluginbase.pri)
QT = core gui script
CONFIG += qdbus

SOURCES += main.cpp
HEADERS += main.h

DESTDIR = $$QT_BUILD_TREE/plugins/script
target.path += $$[QT_INSTALL_PLUGINS]/script
INSTALLS += target
