TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += script
!isEmpty(QT.widgets.name): SUBDIRS += scripttools
