TARGET = tst_qscriptjstestsuite
CONFIG += testcase
QT = core-private script testlib
SOURCES  += tst_qscriptjstestsuite.cpp
RESOURCES += qscriptjstestsuite.qrc
include(../qscriptv8testsuite/abstracttestsuite.pri)

!symbian: DEFINES += SRCDIR=\\\"$$PWD\\\"

wince*|symbian: {
testFiles.files = tests
testFiles.path = .
DEPLOYMENT += testFiles
}

win32:CONFIG += insignificant_test # QTBUG-24426
