QT       += core gui

defined(EMSCRIPTEN)
{
	QMAKE_CFLAGS += -s ASYNCIFY=1
	QMAKE_CXXFLAGS += -s ASYNCIFY=1
	QMAKE_LFLAGS += -s ASYNCIFY=1
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    gamedb.cpp \
    gamedbeditwidget.cpp \
    kfmttreewidgetitem.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mapeditwidget.cpp \
    mapviewer.cpp \
    prettynamer.cpp \
    texture.cpp \
    tfile.cpp

HEADERS += \
    checksum.h \
    gamedb.h \
    gamedbeditwidget.h \
    kfmttreewidgetitem.h \
    kftypes.h \
    mainwindow.h \
    map.h \
    mapeditwidget.h \
    mapviewer.h \
    prettynamer.h \
    texture.h \
    tfile.h

FORMS += \
    gamedbeditwidget.ui \
    mainwindow.ui \
    mapeditwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	resources.qrc
