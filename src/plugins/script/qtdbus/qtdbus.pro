load(qt_module)

TARGET  = qtscriptdbus
DESTDIR = $$QT.script.plugins/script
load(qt_plugin)
QT = core gui script
CONFIG += qdbus

SOURCES += main.cpp
HEADERS += main.h

target.path += $$[QT_INSTALL_PLUGINS]/script
INSTALLS += target
