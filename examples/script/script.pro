TEMPLATE = subdirs
SUBDIRS = \
    customclass \
    qsdbg

!isEmpty(QT.widgets.name) {
    SUBDIRS += \
        helloscript \
        context2d \
        defaultprototypes

    !isEmpty(QT.uitools.name) {
        SUBDIRS += \
            calculator \
            qstetrix
    }

    !wince {
        SUBDIRS += \
            qscript
    }
}

!wince {
    SUBDIRS += \
        marshal
}

maemo5: CONFIG += qt_example
