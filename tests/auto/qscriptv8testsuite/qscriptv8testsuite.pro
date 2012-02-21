TARGET = tst_qscriptv8testsuite
CONFIG += testcase
QT = core-private script testlib
SOURCES  += tst_qscriptv8testsuite.cpp
RESOURCES += qscriptv8testsuite.qrc
include(abstracttestsuite.pri)

win32:CONFIG += insignificant_test # QTBUG-24427
