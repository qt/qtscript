load(qttest_p4)
SOURCES  += tst_headersclean.cpp
QT = core

contains(QT_CONFIG,script): QT += script
contains(QT_CONFIG,scripttools): QT += scripttools
