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

#define QT4 // Define the Qt version in use.

#if defined(_WIN32) || defined(__WIN32)
    #define WINDOWS
    #define SLASH "\\"
    #define FILESTR "file:///"
#else
    #define UNIX
    #define SLASH "/"
    #define FILESTR "file://"
#endif

#define HOME QDir::homePath()
#define DEFAULTFILENAME QDir::homePath() + "/Untitled.txt"
#define HOMEPAGE "http://elpinchetopo.github.com/Abigail/"
#define WIKI "https://github.com/ElPincheTopo/Abigail/wiki"
#define REPO "https://github.com/ElPincheTopo/Abigail"
#define DEFAULTFONT "Mono"
#define DEFAULTFONTSIZE 10

#endif // STRINGS_H
