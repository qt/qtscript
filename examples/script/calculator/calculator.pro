QT += script widgets uitools
RESOURCES += calculator.qrc
SOURCES += main.cpp
QMAKE_PROJECT_NAME = scripted_calculator

contains(QT_CONFIG, scripttools): QT += scripttools

target.path = $$[QT_INSTALL_EXAMPLES]/script/calculator
INSTALLS += target

maemo5: CONFIG += qt_example
