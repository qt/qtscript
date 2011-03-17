QT_SCRIPT_VERSION = $$QT_VERSION
QT_SCRIPT_MAJOR_VERSION = $$QT_MAJOR_VERSION
QT_SCRIPT_MINOR_VERSION = $$QT_MINOR_VERSION
QT_SCRIPT_PATCH_VERSION = $$QT_PATCH_VERSION

QT.script.name = QtScript
QT.script.bins = $$QT_MODULE_BIN_BASE
QT.script.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtScript
QT.script.private_includes = $$QT_MODULE_INCLUDE_BASE/QtScript/private
QT.script.sources = $$QT_MODULE_BASE/src/script
QT.script.libs = $$QT_MODULE_LIB_BASE
QT.script.imports = $$QT_MODULE_IMPORT_BASE
QT.script.depends = core
QT.script.DEFINES = QT_SCRIPT_LIB

QT_CONFIG += script
