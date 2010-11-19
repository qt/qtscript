load(qt_module)

TARGET     = QtScriptTools
QPRO_PWD   = $$PWD
QT         = core gui script
DEFINES   += QT_BUILD_SCRIPTTOOLS_LIB
DEFINES   += QT_NO_USING_NAMESPACE
#win32-msvc*|win32-icc:QMAKE_LFLAGS += /BASE:0x66000000

unix|win32-g++*:QMAKE_PKGCONFIG_REQUIRES = QtCore QtGui QtScript

include($$QT_SOURCE_TREE/src/qbase.pri)

include(debugging/debugging.pri)

INCLUDEPATH += $$OUT_PWD/../../include \
    $$OUT_PWD/../../include/QtScript \
    $$OUT_PWD/../../include/QtScript/private \
    $$OUT_PWD/../../include/QtScriptTools \
    $$OUT_PWD/../../include/QtScriptTools/private

symbian:TARGET.UID3=0x2001E625
