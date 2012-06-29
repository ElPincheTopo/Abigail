/*
    Abigail, A lightweight, powerful and customizable cross-platform IDE.
    Copyright (C) 2012 Roberto Lapuente topo@asustin.net

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.

    For more information visit https://github.com/ElPincheTopo/Abigail
    or send an e-mail to topo@asustin.net.
*/

#ifndef STRINGS_H
#define STRINGS_H

#include <QString>

#define QT4 // Define the Qt version in use.

#if defined(_WIN32) || defined(__WIN32)
    #define WINDOWS
    #define _SLASH "\\"
    #define _FILESTR "file:///"
    #define _PREFERENCESDIR QCoreApplication::applicationDirPath();
#else
    #define UNIX
    #define _SLASH "/"
    #define _FILESTR "file://"
    #define _PREFERENCESDIR Preferences::HOME
#endif

class Preferences
{
public:
    Preferences();
    ~Preferences();
    static void readPreferences();
    static void writePreferences();
    static void generatePreferencesFile();

    // Preference variables
    static bool lineWrap;
    static bool centerOnScroll;
    static bool columnLine;
    static int columnOfLine;
    static int tabLength;
    static QString font;
    static int fontSize;
    static unsigned int vLineColor;
    static unsigned int currentLineColor;
    static unsigned int lineNumberArea;
    static unsigned int lineNumberColor;
    static unsigned int selectionColor;

    // Constants
    static const QString SLASH;
    static const QString FILESTR;
    static const QString HOME;
    static const QString DEFAULTFILENAME;
    static const QString HOMEPAGE;
    static const QString WIKI;
    static const QString REPO;
    static const QString PREFERENCESDIR;
    static const QString PREFERENCESFILE;
};

#endif // STRINGS_H
