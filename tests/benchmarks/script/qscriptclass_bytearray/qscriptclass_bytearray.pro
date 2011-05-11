load(qttest_p4)
TEMPLATE = app
TARGET = tst_bench_qscriptclass_bytearray

SOURCES += tst_qscriptclass_bytearray.cpp
RESOURCES += qscriptclass_bytearray.qrc

include($$PWD/../../../../examples/script/customclass/bytearrayclass.pri)

QT = core script
