TEMPLATE = subdirs
SUBDIRS = customclass
!contains(QT_CONFIG, no-gui):SUBDIRS += helloscript context2d defaultprototypes

!wince*:!contains(QT_CONFIG, no-gui):SUBDIRS += qscript marshal
!wince*:SUBDIRS *= marshal

isEmpty(QT.widgets.name):SUBDIRS -= \
    context2d \
    defaultprototypes \
    helloscript \
    qscript

# install
target.path = $$[QT_INSTALL_EXAMPLES]/qtscript/script
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS script.pro README
sources.path = $$[QT_INSTALL_EXAMPLES]/qtscript/script
INSTALLS += target sources

maemo5: CONFIG += qt_example
