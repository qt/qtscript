QT += script widgets uitools
RESOURCES += calculator.qrc
SOURCES += main.cpp
QMAKE_PROJECT_NAME = scripted_calculator

contains(QT_CONFIG, scripttools): QT += scripttools

# install
target.path = $$[QT_INSTALL_EXAMPLES]/qtscript/script/calculator
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS *.pro *.js *.ui
sources.path = $$[QT_INSTALL_EXAMPLES]/qtscript/script/calculator
INSTALLS += target sources

maemo5: CONFIG += qt_example
