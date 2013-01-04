TARGET     = QtScriptTools
QT         = core-private
QT_PRIVATE = gui widgets-private script

DEFINES   += QT_NO_USING_NAMESPACE
#win32-msvc*|win32-icc:QMAKE_LFLAGS += /BASE:0x66000000

load(qt_module)

include(debugging/debugging.pri)
