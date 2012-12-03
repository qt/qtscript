QT += widgets script
RESOURCES += defaultprototypes.qrc
SOURCES += main.cpp prototypes.cpp
HEADERS += prototypes.h

# install
target.path = $$[QT_INSTALL_EXAMPLES]/qtscript/script/defaultprototypes
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS *.js defaultprototypes.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/qtscript/script/defaultprototypes
INSTALLS += target sources

maemo5: CONFIG += qt_example
