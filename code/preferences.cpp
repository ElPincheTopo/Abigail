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
#include <QFile>

#include "preferences.h"

#include <QDebug>

Preferences::Preferences()
{

}

void Preferences::readPreferences()
{
    QFile file(PREFERENCESDIR + "/.abigail/preferences");
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().replace(" ", "");
            if (line[0] != '#') {
                line = line.toLower();
                QStringList list = line.split("=");
                if (list.length() == 2) {
                    if(list[0] == "linewrap")
                        setLineWrap(list[1] == "true" ? true : false);
                    else if (list[0] == "columnline")
                        setColumnLine(list[1] == "true" ? true : false);
                    else if (list[0] == "columnofline")
                        setColumnOfLine(list[1].toInt());
                    else if (list[0] == "font")
                        setFont(list[1]);
                    else if (list[0] == "fontsize")
                        setFontSize(list[1].toInt());
                }
            }


        }
        file.close();
    } else {
        qDebug() << "No encontró el archivo";
        generatePreferencesFile();
    }

}

void Preferences::writePreferences()
{

}

void Preferences::generatePreferencesFile()
{
    // Read preference files
    QFile inFile(":/resources/documents/preferences");
    inFile.open(QIODevice::ReadOnly);
    QTextStream in(&inFile);
    QString text = in.readAll();
    inFile.close();

    qDebug() << text;

    // Write in user home
    QFile outFile(PREFERENCESDIR + "/.abigail/preferences");
    outFile.open(QIODevice::WriteOnly);
    QTextStream out(&outFile);
    out << text;
    outFile.close();

}

void Preferences::setLineWrap(bool value)
{
    // Call Tabs Manager set line wrap
    Preferences::lineWrap = value;
}

void Preferences::setColumnLine(bool value)
{
    Preferences::columnLine = value;
}

void Preferences::setColumnOfLine(int column)
{
    Preferences::columnOfLine = column;
}

void Preferences::setFont(QString font)
{
    Preferences::font = font;
}

void Preferences::setFontSize(int size)
{
    Preferences::fontSize = size;
}

// Preferences Variables
bool Preferences::lineWrap = false;
bool Preferences::columnLine = true;
int Preferences::columnOfLine = 80;
QString Preferences::font = "Mono";
int Preferences::fontSize = 10;

// Constants
const QString Preferences::SLASH = _SLASH;
const QString Preferences::FILESTR = _FILESTR;
const QString Preferences::HOME = QDir::homePath();
const QString Preferences::DEFAULTFILENAME = Preferences::HOME + "/Untitled.txt";
const QString Preferences::HOMEPAGE = "http://elpinchetopo.github.com/Abigail/";
const QString Preferences::WIKI = "https://github.com/ElPincheTopo/Abigail/wiki";
const QString Preferences::REPO = "https://github.com/ElPincheTopo/Abigail";
const QString Preferences::PREFERENCESDIR = _PREFERENCESDIR;
