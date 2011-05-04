QT.script.VERSION = 4.8.0
QT.script.MAJOR_VERSION = 4
QT.script.MINOR_VERSION = 8
QT.script.PATCH_VERSION = 0

QT.script.name = QtScript
QT.script.bins = $$QT_MODULE_BIN_BASE
QT.script.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtScript
QT.script.private_includes = $$QT_MODULE_INCLUDE_BASE/QtScript/$$QT.script.VERSION
QT.script.sources = $$QT_MODULE_BASE/src/script
QT.script.libs = $$QT_MODULE_LIB_BASE
QT.script.plugins = $$QT_MODULE_PLUGIN_BASE
QT.script.imports = $$QT_MODULE_IMPORT_BASE
QT.script.depends = core
QT.script.DEFINES = QT_SCRIPT_LIB

QT_CONFIG += script
