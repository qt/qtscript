load(qt_module)

TARGET     = QtScriptTools
QPRO_PWD   = $$PWD
QT         = core-private gui widgets widgets-private script

CONFIG += module
MODULE_PRI = ../../modules/qt_scripttools.pri

DEFINES   += QT_BUILD_SCRIPTTOOLS_LIB
DEFINES   += QT_NO_USING_NAMESPACE
#win32-msvc*|win32-icc:QMAKE_LFLAGS += /BASE:0x66000000

unix|win32-g++*:QMAKE_PKGCONFIG_REQUIRES = QtCore QtGui QtScript

include($$QT_SOURCE_TREE/src/qbase.pri)

HEADERS += qtscripttoolsversion.h

include(debugging/debugging.pri)

symbian:TARGET.UID3=0x2001E625
