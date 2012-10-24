TARGET  = qtscriptdbus

PLUGIN_TYPE = script
load(qt_plugin)

QT = core gui script
CONFIG += qdbus

SOURCES += main.cpp
HEADERS += main.h
