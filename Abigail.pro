#-------------------------------------------------
#
# Project created by QtCreator 2012-03-08T16:40:59
#
#-------------------------------------------------

QT       += core gui

TARGET = Abigail
TEMPLATE = app


SOURCES += code/main.cpp\
        code/mainwindow.cpp \
    code/about.cpp \
    code/document.cpp \
    code/tabmanager.cpp

HEADERS  += code/mainwindow.h \
    code/about.h \
    code/document.h \
    code/tabmanager.h

FORMS    += ui/mainwindow.ui \
    ui/about.ui

OTHER_FILES += \
    README.md \
    COPYING \
    resources/images/logos/abigail.png

RESOURCES += \
    resources/icons.qrc \
    resources/logos.qrc
