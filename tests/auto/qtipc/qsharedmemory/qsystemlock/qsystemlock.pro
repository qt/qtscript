CONFIG += testcase
QT = core testlib

include(../src/src.pri)
win32: CONFIG += console
mac:CONFIG -= app_bundle

DEFINES += SRCDIR=\\\"$$PWD\\\"

DEFINES	+= QSHAREDMEMORY_DEBUG
DEFINES	+= QSYSTEMSEMAPHORE_DEBUG

SOURCES		+= tst_qsystemlock.cpp 
TARGET		= tst_qsystemlock


