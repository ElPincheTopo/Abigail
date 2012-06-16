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

#include <QDir>

#include "preferences.h"



Preferences::Preferences()
{

}

// Preferences Variables
bool Preferences::lineWrap = false;
bool Preferences::columnLine = true;
int Preferences::columnOfLine = 80;

// Constants
const QString Preferences::SLASH = _SLASH;
const QString Preferences::FILESTR = _FILESTR;
const QString Preferences::HOME = QDir::homePath();
const QString Preferences::DEFAULTFILENAME = HOME + "/Untitled.txt";
const QString Preferences::HOMEPAGE = "http://elpinchetopo.github.com/Abigail/";
const QString Preferences::WIKI = "https://github.com/ElPincheTopo/Abigail/wiki";
const QString Preferences::REPO = "https://github.com/ElPincheTopo/Abigail";
const QString Preferences::DEFAULTFONT = "Mono";
const int Preferences::DEFAULTFONTSIZE = 10;
