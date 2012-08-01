TARGET = tst_headersclean
CONFIG += testcase
SOURCES  += tst_headersclean.cpp
QT = core testlib

contains(QT_CONFIG,script): QT += script
contains(QT_CONFIG,scripttools): QT += scripttools
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
