CONFIG += testcase

QT = core testlib
include(../src/src.pri)

mac:CONFIG -= app_bundle

DEFINES	+= QSHAREDMEMORY_DEBUG
DEFINES	+= QSYSTEMSEMAPHORE_DEBUG

SOURCES += ../tst_qsharedmemory.cpp
TARGET = tst_qsharedmemory

DEFINES += SRCDIR=\\\"$$PWD\\\"
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
