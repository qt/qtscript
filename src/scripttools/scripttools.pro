load(qt_module)

TARGET     = QtScriptTools
QPRO_PWD   = $$PWD
QT         = core-private

CONFIG += module

DEFINES   += QT_BUILD_SCRIPTTOOLS_LIB
DEFINES   += QT_NO_USING_NAMESPACE
#win32-msvc*|win32-icc:QMAKE_LFLAGS += /BASE:0x66000000

unix|win32-g++*:QMAKE_PKGCONFIG_REQUIRES = QtCore QtGui QtScript

load(qt_module_config)

HEADERS += qtscripttoolsversion.h

# private dependencies
QT += gui widgets-private script

include(debugging/debugging.pri)

symbian:TARGET.UID3=0x2001E625
