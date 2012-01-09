CONFIG += testcase
QT = core testlib

include(../qsharedmemory/src/src.pri)
win32: CONFIG += console
mac:CONFIG -= app_bundle

DEFINES	+= QSHAREDMEMORY_DEBUG
DEFINES	+= QSYSTEMSEMAPHORE_DEBUG

SOURCES		+= tst_qsystemsemaphore.cpp 
TARGET		= tst_qsystemsemaphore

RESOURCES += files.qrc

DEFINES += SRCDIR=\\\"$$PWD/\\\"
