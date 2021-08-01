QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

# Stuff to build libimagequant
HEADERS += libimagequant/blur.h \
           libimagequant/kmeans.h \
           libimagequant/libimagequant.h \
           libimagequant/mediancut.h \
           libimagequant/mempool.h \
           libimagequant/nearest.h \
           libimagequant/pam.h

SOURCES += libimagequant/blur.c \
           libimagequant/kmeans.c \
           libimagequant/libimagequant.c \
           libimagequant/mediancut.c \
           libimagequant/mempool.c \
           libimagequant/nearest.c \
           libimagequant/pam.c

# Inherit system CFLAGS/CXXFLAGS into qmake
QMAKE_CFLAGS += $$(CFLAGS) -isystem $$[QT_INSTALL_HEADERS]
QMAKE_CXXFLAGS += $$(CXXFLAGS) -isystem $$[QT_INSTALL_HEADERS]

# Supress warnings for Qt stuff
QMAKE_CFLAGS += -isystem "$$[QT_INSTALL_HEADERS]/qt5" -isystem "$$[QT_INSTALL_HEADERS]/qt5/QtWidgets" \
                -isystem "$$[QT_INSTALL_HEADERS]/QtXml" -isystem "/usr/include/qt5/QtGui" \
                -isystem "$$[QT_INSTALL_HEADERS]/QtCore"
QMAKE_CXXFLAGS += -isystem "$$[QT_INSTALL_HEADERS]/qt5" -isystem "$$[QT_INSTALL_HEADERS]/qt5/QtWidgets" \
                  -isystem "$$[QT_INSTALL_HEADERS]/QtXml" -isystem "/usr/include/qt5/QtGui" \
                  -isystem "$$[QT_INSTALL_HEADERS]/QtCore"

SOURCES += \
    ../common/prettynamer.cpp \
    aboutdialog.cpp \
    gamedb.cpp \
    gamedbeditwidget.cpp \
    kfmterror.cpp \
    kfmttreewidgetitem.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mapeditwidget.cpp \
    mapviewer.cpp \
    mixfile.cpp \
    model.cpp \
    modelglview.cpp \
    models/armorstatstablemodel.cpp \
    models/entityclasstablemodel.cpp \
    models/entityinstancelistmodel.cpp \
    models/entityinstancetablemodel.cpp \
    models/entitystatetablemodel.cpp \
    models/magictablemodel.cpp \
    models/modelanimationlistmodel.cpp \
    models/modelobjecttablemodel.cpp \
    models/objectclasstablemodel.cpp \
    models/objectinstancelistmodel.cpp \
    models/objectinstancetablemodel.cpp \
    models/playerleveldatatablemodel.cpp \
    models/texturelistmodel.cpp \
    models/vfxinstancetablemodel.cpp \
    models/weaponstatstablemodel.cpp \
    modelviewerwidget.cpp \
    soundbank.cpp \
    texturedb.cpp \
    texturedbviewer.cpp \
    tfile.cpp

HEADERS += \
    ../common/prettynamer.h \
    aboutdialog.h \
    checksum.h \
    gamedb.h \
    gamedbeditwidget.h \
    kfmterror.h \
    kfmttreewidgetitem.h \
    kf2types.h \
    mainwindow.h \
    map.h \
    mapeditwidget.h \
    mapviewer.h \
    mixfile.h \
    model.h \
    modelglview.h \
    models/armorstatstablemodel.h \
    models/entityclasstablemodel.h \
    models/entityinstancelistmodel.h \
    models/entityinstancetablemodel.h \
    models/entitystatetablemodel.h \
    models/magictablemodel.h \
    models/modelanimationlistmodel.h \
    models/modelobjecttablemodel.h \
    models/objectclasstablemodel.h \
    models/objectinstancelistmodel.h \
    models/objectinstancetablemodel.h \
    models/playerleveldatatablemodel.h \
    models/texturelistmodel.h \
    models/vfxinstancetablemodel.h \
    models/weaponstatstablemodel.h \
    modelviewerwidget.h \
    soundbank.h \
    texturedb.h \
    texturedbviewer.h \
    tfile.h \
    utilities.h

FORMS += \
    aboutdialog.ui \
    gamedbeditwidget.ui \
    mainwindow.ui \
    mapeditwidget.ui \
    modelviewerwidget.ui \
    texturedbviewer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	resources.qrc

DISTFILES += \
    litCommon.frag \
    litMime.vert \
    litStatic.vert \
    unlitSimple.frag \
    unlitSimple.vert
