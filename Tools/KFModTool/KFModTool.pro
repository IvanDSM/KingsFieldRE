QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Use the GitHub Actions run ID
RUNID = $$(GITHUB_RUN_NUMBER)

!isEmpty(RUNID) {
    DEFINES += "RUNID=\\\"$$RUNID\\\""
}
isEmpty(RUNID) {
    DEFINES += "RUNID=\\\"DEVELOPMENT\\\""
}

CONFIG += c++17

RC_ICONS = KFModTool.ico

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

HEADERS += \
    aboutdialog.h \
    core/icons.h \
    core/kfmtcore.h \
    core/kfmterror.h \
    core/kfmtfile.h \
    core/prettynames.h \
    datahandlers/gamedb.h \
    datahandlers/gameexe.h \
    datahandlers/kfmtdatahandler.h \
    datahandlers/map.h \
    datahandlers/model.h \
    datahandlers/soundbank.h \
    datahandlers/texturedb.h \
    datahandlers/tileseticons.h \
    editors/exeeditor.h \
    editors/gamedbeditwidget.h \
    editors/kfmteditor.h \
    editors/mapeditwidget.h \
    editors/modelviewerwidget.h \
    editors/texturedbviewer.h \
    editors/subwidgets/mapviewer.h \
    editors/subwidgets/mapviewer3d.h \
    editors/subwidgets/modelglview.h \
    games/kf2.h \
    mainwindow.h \
    models/armorstatslistmodel.h \
    models/armorstatstablemodel.h \
    models/entityclasslistmodel.h \
    models/entityclasstablemodel.h \
    models/entityinstancelistmodel.h \
    models/entityinstancetablemodel.h \
    models/entitystatetablemodel.h \
    models/filelistmodel.h \
    models/magiclistmodel.h \
    models/magictablemodel.h \
    models/modelanimationlistmodel.h \
    models/modelobjecttablemodel.h \
    models/objectclasslistmodel.h \
    models/objectclasstablemodel.h \
    models/objectinstancelistmodel.h \
    models/objectinstancetablemodel.h \
    models/playerleveldatatablemodel.h \
    models/shoplistmodel.h \
    models/shoptablemodel.h \
    models/stringtablemodels.h \
    models/texturelistmodel.h \
    models/tilecontentslistmodel.h \
    models/vfxinstancetablemodel.h \
    models/weaponstatslistmodel.h \
    models/weaponstatstablemodel.h \
    utilities.h
    
SOURCES += \
    aboutdialog.cpp \
    core/icons.cpp \
    core/kfmtcore.cpp \
    core/kfmterror.cpp \
    core/kfmtfile.cpp \
    core/prettynames.cpp \
    datahandlers/gamedb.cpp \
    datahandlers/gameexe.cpp \
    datahandlers/map.cpp \
    datahandlers/model.cpp \
    datahandlers/soundbank.cpp \
    datahandlers/texturedb.cpp \
    datahandlers/tileseticons.cpp \
    editors/exeeditor.cpp \
    editors/gamedbeditwidget.cpp \
    editors/mapeditwidget.cpp \
    editors/modelviewerwidget.cpp \
    editors/texturedbviewer.cpp \
    editors/subwidgets/mapviewer.cpp \
    editors/subwidgets/mapviewer3d.cpp \
    editors/subwidgets/modelglview.cpp \
    games/kf2.cpp \
    main.cpp \
    mainwindow.cpp \
    models/armorstatslistmodel.cpp \
    models/armorstatstablemodel.cpp \
    models/entityclasslistmodel.cpp \
    models/entityclasstablemodel.cpp \
    models/entityinstancelistmodel.cpp \
    models/entityinstancetablemodel.cpp \
    models/entitystatetablemodel.cpp \
    models/filelistmodel.cpp \
    models/magiclistmodel.cpp \
    models/magictablemodel.cpp \
    models/modelanimationlistmodel.cpp \
    models/modelobjecttablemodel.cpp \
    models/objectclasslistmodel.cpp \
    models/objectclasstablemodel.cpp \
    models/objectinstancelistmodel.cpp \
    models/objectinstancetablemodel.cpp \
    models/playerleveldatatablemodel.cpp \
    models/shoplistmodel.cpp \
    models/shoptablemodel.cpp \
    models/stringtablemodels.cpp \
    models/texturelistmodel.cpp \
    models/tilecontentslistmodel.cpp \
    models/vfxinstancetablemodel.cpp \
    models/weaponstatslistmodel.cpp \
    models/weaponstatstablemodel.cpp

FORMS += \
    aboutdialog.ui \
    editors/exeeditor.ui \
    editors/gamedbeditwidget.ui \
    editors/mapeditwidget.ui \
    editors/modelviewerwidget.ui \
    editors/texturedbviewer.ui \
    mainwindow.ui
    
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
