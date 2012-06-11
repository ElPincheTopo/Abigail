#-------------------------------------------------
#
#    Abigail, A lightweight, powerful and customizable cross-platform IDE.
#    Copyright (C) 2012 Roberto Lapuente topo@asustin.net
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program. If not, see <http://www.gnu.org/licenses/>.
#
#    For more information visit https://github.com/ElPincheTopo/Abigail
#    or send an e-mail to topo@asustin.net.
#
#
# Project created by QtCreator 2012-03-08T16:40:59
#
#-------------------------------------------------

QT       += core gui

TARGET = Abigail
#QMAKE_CXXFLAGS += -m64
TEMPLATE = app


SOURCES += code/main.cpp\
        code/mainwindow.cpp \
    code/about.cpp \
    code/document.cpp \
    code/tabmanager.cpp \
    code/codeeditor.cpp

HEADERS  += code/mainwindow.h \
    code/about.h \
    code/document.h \
    code/tabmanager.h \
    code/codeeditor.h \
    code/strings.h

FORMS    += ui/mainwindow.ui \
    ui/about.ui

OTHER_FILES += \
    README.md \
    COPYING \
    resources/images/logos/abigail.png

RESOURCES += \
    resources/icons.qrc \
    resources/logos.qrc
