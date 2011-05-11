%modules = ( # path to module name map
    "QtScript" => "$basedir/src/script",
    "QtScriptTools" => "$basedir/src/scripttools",
);
%moduleheaders = ( # restrict the module headers to those found in relative path
);
%classnames = (
    "qtscriptversion.h" => "QtScriptVersion",
    "qtscripttoolsversion.h" => "QtScriptToolsVersion",
);
%mastercontent = (
    "core" => "#include <QtCore/QtCore>\n",
    "gui" => "#include <QtGui/QtGui>\n",
    "script" => "#include <QtScript/QtScript>\n",
);
%modulepris = (
    "QtScript" => "$basedir/modules/qt_script.pri",
    "QtScriptTools" => "$basedir/modules/qt_scripttools.pri",
);
# Modules and programs, and their dependencies.
# Each of the module version specifiers can take one of the following values:
#   - A specific Git revision.
#   - "LATEST_REVISION", to always test against the latest revision.
#   - "LATEST_RELEASE", to always test against the latest public release.
#   - "THIS_REPOSITORY", to indicate that the module is in this repository.
%dependencies = (
    "QtScript" => {
        "QtCore" => "0c637cb07ba3c9b353e7e483a209537485cc4e2a",
    },
    "QtScriptTools" => {
        "QtCore" => "0c637cb07ba3c9b353e7e483a209537485cc4e2a",
        "QtGui" => "0c637cb07ba3c9b353e7e483a209537485cc4e2a",
        "QtScript" => "THIS_REPOSITORY",
    },
);
