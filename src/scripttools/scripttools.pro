load(qt_build_config)

TARGET     = QtScriptTools
QT         = core-private

DEFINES   += QT_NO_USING_NAMESPACE
#win32-msvc*|win32-icc:QMAKE_LFLAGS += /BASE:0x66000000

load(qt_module)

# private dependencies
QT += gui widgets-private script

include(debugging/debugging.pri)

symbian:TARGET.UID3=0x2001E625
