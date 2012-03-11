#-------------------------------------------------
#
# Project created by QtCreator 2012-03-08T16:40:59
#
#-------------------------------------------------

QT       += core gui

TARGET = Abigail
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/about.cpp

HEADERS  += src/mainwindow.h \
    src/about.h

FORMS    += ui/mainwindow.ui \
    ui/about.ui

OTHER_FILES += \
    README.md \
    COPYING

RESOURCES += \
    resources/icons.qrc
