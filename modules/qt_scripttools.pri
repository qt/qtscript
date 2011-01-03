QT_SCRIPTTOOLS_VERSION = $$QT_VERSION
QT_SCRIPTTOOLS_MAJOR_VERSION = $$QT_MAJOR_VERSION
QT_SCRIPTTOOLS_MINOR_VERSION = $$QT_MINOR_VERSION
QT_SCRIPTTOOLS_PATCH_VERSION = $$QT_PATCH_VERSION

QT.scripttools.name = QtScriptTools
QT.scripttools.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtScriptTools
QT.scripttools.private_includes = $$QT_MODULE_INCLUDE_BASE/QtScriptTools/private
QT.scripttools.sources = $$QT_MODULE_BASE/src/scripttools
QT.scripttools.libs = $$QT_MODULE_LIB_BASE
QT.scripttools.depends = script gui network
QT.scripttools.DEFINES = QT_SCRIPTTOOLS_LIB

QT_CONFIG += scripttools
