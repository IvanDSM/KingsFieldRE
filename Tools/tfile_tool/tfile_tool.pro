QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# Get CFLAGS and LDFLAGS!
# I need this for doing proper Windows automatic builds.
QMAKE_CXXFLAGS += $$(CXXFLAGS)
QMAKE_CFLAGS += $$(CFLAGS)
QMAKE_LFLAGS += $$(LDFLAGS)

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
		../common/prettynamer.h \
		../common/tfile.h

SOURCES += \
        main.cpp \
        ../common/prettynamer.cpp \
        ../common/tfile.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
