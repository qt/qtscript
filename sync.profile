%modules = ( # path to module name map
    "QtScript" => "$basedir/src/script/api",
    "QtScriptTools" => "$basedir/src/scripttools",
);
%moduleheaders = ( # restrict the module headers to those found in relative path
);
%classnames = (
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
