QT.scripttools.VERSION = 4.8.0
QT.scripttools.MAJOR_VERSION = 4
QT.scripttools.MINOR_VERSION = 8
QT.scripttools.PATCH_VERSION = 0

QT.scripttools.name = QtScriptTools
QT.scripttools.bins = $$QT_MODULE_BIN_BASE
QT.scripttools.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtScriptTools
QT.scripttools.private_includes = $$QT_MODULE_INCLUDE_BASE/QtScriptTools/$$QT.scripttools.VERSION
QT.scripttools.sources = $$QT_MODULE_BASE/src/scripttools
QT.scripttools.libs = $$QT_MODULE_LIB_BASE
QT.scripttools.plugins = $$QT_MODULE_PLUGIN_BASE
QT.scripttools.imports = $$QT_MODULE_IMPORT_BASE
QT.scripttools.depends = script gui network
QT.scripttools.DEFINES = QT_SCRIPTTOOLS_LIB

QT_CONFIG += scripttools
