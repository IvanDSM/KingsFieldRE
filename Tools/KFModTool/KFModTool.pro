QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
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
    model.cpp \
    modelglview.cpp \
    models/armorstatstablemodel.cpp \
    models/entityclasstablemodel.cpp \
    models/entityinstancetablemodel.cpp \
    models/magictablemodel.cpp \
    models/modelanimationlistmodel.cpp \
    models/modelobjecttablemodel.cpp \
    models/objectclasstablemodel.cpp \
    models/objectinstancetablemodel.cpp \
    models/playerleveldatatablemodel.cpp \
    models/vfxinstancetablemodel.cpp \
    models/weaponstatstablemodel.cpp \
    modelviewerwidget.cpp \
    prettynamer.cpp \
    texture.cpp \
    textureviewer.cpp \
    tfile.cpp

HEADERS += \
    aboutdialog.h \
    checksum.h \
    gamedb.h \
    gamedbeditwidget.h \
    kfmterror.h \
    kfmttreewidgetitem.h \
    kftypes.h \
    mainwindow.h \
    map.h \
    mapeditwidget.h \
    mapviewer.h \
    model.h \
    modelglview.h \
    models/armorstatstablemodel.h \
    models/entityclasstablemodel.h \
    models/entityinstancetablemodel.h \
    models/magictablemodel.h \
    models/modelanimationlistmodel.h \
    models/modelobjecttablemodel.h \
    models/objectclasstablemodel.h \
    models/objectinstancetablemodel.h \
    models/playerleveldatatablemodel.h \
    models/vfxinstancetablemodel.h \
    models/weaponstatstablemodel.h \
    modelviewerwidget.h \
    prettynamer.h \
    soundbank.h \
    texture.h \
    textureviewer.h \
    tfile.h \
    utilities.h

FORMS += \
    aboutdialog.ui \
    gamedbeditwidget.ui \
    mainwindow.ui \
    mapeditwidget.ui \
    modelviewerwidget.ui \
    textureviewer.ui

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
