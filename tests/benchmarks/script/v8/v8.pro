CONFIG += testcase
TEMPLATE = app
TARGET = tst_bench_v8
RESOURCES += v8.qrc
SOURCES += tst_v8.cpp

QT = core script testlib

symbian* {
    TARGET.EPOCHEAPSIZE  = 0x20000 0x2000000 // Min 128kB, Max 32MB
    TARGET.EPOCSTACKSIZE = 0x14000
}
