TEMPLATE = subdirs

module_qtscript_src.subdir = src
module_qtscript_src.target = module-qtscript-src

module_qtscript_examples.subdir = examples
module_qtscript_examples.target = module-qtscript-examples
module_qtscript_examples.depends = module_qtscript_src

module_qtscript_tests.subdir = tests
module_qtscript_tests.target = module-qtscript-tests
module_qtscript_tests.depends = module_qtscript_src
module_qtscript_tests.CONFIG = no_default_install
!contains(QT_BUILD_PARTS,tests):module_qtscript_tests.CONFIG += no_default_target

SUBDIRS += module_qtscript_src \
           module_qtscript_examples \
           module_qtscript_tests \
