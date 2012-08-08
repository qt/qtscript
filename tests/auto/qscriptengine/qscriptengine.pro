TARGET = tst_qscriptengine
CONFIG += testcase
QT = core gui widgets script script-private testlib
SOURCES += tst_qscriptengine.cpp 
RESOURCES += qscriptengine.qrc
include(../shared/util.pri)

wince* {
    DEFINES += SRCDIR=\\\"./\\\"
} else:!symbian {
    DEFINES += SRCDIR=\\\"$$PWD\\\"
}

wince*|symbian: {
   addFiles.files = script
   addFiles.path = .
   DEPLOYMENT += addFiles
}

symbian: {
   TARGET.UID3 = 0xE0340006
   DEFINES += SYMBIAN_SRCDIR_UID=$$lower($$replace(TARGET.UID3,"0x",""))
}
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
