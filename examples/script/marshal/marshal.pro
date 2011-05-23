QT = core script
CONFIG += console
SOURCES += main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/qtscript/script/marshal
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS marshal.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/qtscript/script/marshal
INSTALLS += target sources

symbian: CONFIG += qt_example
maemo5: CONFIG += qt_example

symbian: warning(This example does not work on Symbian platform)
