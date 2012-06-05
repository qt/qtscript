TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS += script
!contains(QT_CONFIG, no-widgets): SUBDIRS += scripttools
