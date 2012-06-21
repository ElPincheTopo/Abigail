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
#include <QTextStream>

#include "preferences.h"

Preferences::Preferences()
{

}

void Preferences::readPreferences()
{
    QFile file(Preferences::PREFERENCESFILE);
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().replace(" ", "");
            if (line[0] != '#') {
                line = line.toLower();
                QStringList list = line.split("=");
                if (list.length() == 2) {
                    // Utilities Section
                    if(list[0] == "linewrap")
                        Preferences::lineWrap = (list[1] == "true" ? true : false);

                    // Text Area Section
                    else if (list[0] == "columnline")
                        Preferences::columnLine = (list[1] == "true" ? true : false);
                    else if (list[0] == "columnofline")
                        Preferences::columnOfLine = (list[1].toInt());
                    else if (list[0] == "verticallinecolor")
                        Preferences::vLineColor = (list[1].toUInt());
                    else if (list[0] == "currentlinecolor")
                        Preferences::currentLineColor = (list[1].toUInt());
                    else if (list[0] == "linenumberarea")
                        Preferences::lineNumberArea = (list[1].toUInt());
                    else if (list[0] == "linenumbercolor")
                        Preferences::lineNumberColor = (list[1].toUInt());
                    else if (list[0] == "font")
                        Preferences::font = (list[1]);
                    else if (list[0] == "fontsize")
                        Preferences:: fontSize = (list[1].toInt());

                    // Find & Replace Section
                    else if (list[0] == "selectioncolor")
                        Preferences::selectionColor = (list[1].toUInt());
                }
            }
        }
        file.close();
    } else {
        generatePreferencesFile();
    }

}

void Preferences::writePreferences()
{
    QString preferencesFile = Preferences::PREFERENCESFILE;
    QString newPreferencesFile = Preferences::PREFERENCESDIR + "/preferences.tmp";

    QFile file(preferencesFile);
    QFile tmp(newPreferencesFile);

    tmp.open(QIODevice::WriteOnly);

    if(file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QTextStream out(&tmp);
        while (!in.atEnd()) {
            QString originalLine = in.readLine();
            QString line = QString(originalLine).replace(" ", "");
            QString writeLine = "";

            if (line[0] != '#' && line != "") {
                line = line.toLower();
                QStringList list = line.split("=");

                if (list.length() == 2) {
                    // Utilities Section
                    if(list[0] == "linewrap")
                        writeLine = QString("Line Wrap = ") + (Preferences::lineWrap ? "TRUE" : "FALSE");

                    // Text Area Section
                    else if (list[0] == "columnline")
                        writeLine = QString("Column Line = ") + (Preferences::columnLine ? "TRUE" : "FALSE");
                    else if (list[0] == "columnofline")
                        writeLine = "Column Of Line = " + QString::number(Preferences::columnOfLine);
                    else if (list[0] == "verticallinecolor")
                        writeLine = "Vertical Line Color = " + QString::number(Preferences::vLineColor);
                    else if (list[0] == "currentlinecolor")
                        writeLine = "Current Line Color = " + QString::number(Preferences::currentLineColor);
                    else if (list[0] == "linenumberarea")
                        writeLine = "Line Number Area = " + QString::number(Preferences::lineNumberArea);
                    else if (list[0] == "linenumbercolor")
                        writeLine = "Line Number Color = " + QString::number(Preferences::lineNumberColor);
                    else if (list[0] == "font")
                        writeLine = "Font = " + Preferences::font;
                    else if (list[0] == "fontsize")
                        writeLine = "Font Size = " + QString::number(Preferences::fontSize);

                    // Find & Replace Section
                    else if (list[0] == "selectioncolor")
                        writeLine = "Selection Color = " + QString::number(Preferences::selectionColor);
                }
            }
            // Write the line to the new file
            out << (writeLine == "" ? originalLine : writeLine) << endl;
        }
        // Close Files
        file.close();
        tmp.close();

        // Remove preference file & rename new file
        file.remove();
        tmp.rename(preferencesFile);
    } else {
        Preferences::generatePreferencesFile();
        Preferences::writePreferences();
    }
}

void Preferences::generatePreferencesFile()
{
    // Read preference files
    QFile inFile(":/resources/documents/preferences");
    inFile.open(QIODevice::ReadOnly);
    QTextStream in(&inFile);
    QString text = in.readAll();
    inFile.close();

    // Write in user home
    QFile outFile(Preferences::PREFERENCESFILE);
    if (outFile.open(QIODevice::WriteOnly)) {
        QTextStream out(&outFile);
        out << text;
        outFile.close();
    }
}

// Preferences Variables
bool Preferences::lineWrap = false;
bool Preferences::columnLine = true;
int Preferences::columnOfLine = 80;
QString Preferences::font = __FONT;
int Preferences::fontSize = 10;
unsigned int Preferences::vLineColor = 4290822336u;
unsigned int Preferences::currentLineColor = 4293848831u;
unsigned int Preferences::lineNumberArea = 4293980400u;
unsigned int Preferences::lineNumberColor = 4283782485u;
unsigned int Preferences::selectionColor = 4294967040u;

// Constants
const QString Preferences::SLASH = _SLASH;
const QString Preferences::FILESTR = _FILESTR;
const QString Preferences::HOME = _HOME;
const QString Preferences::DEFAULTFILENAME = Preferences::HOME + "/Untitled.txt";
const QString Preferences::HOMEPAGE = "http://elpinchetopo.github.com/Abigail/";
const QString Preferences::WIKI = "https://github.com/ElPincheTopo/Abigail/wiki";
const QString Preferences::REPO = "https://github.com/ElPincheTopo/Abigail";
const QString Preferences::PREFERENCESDIR = _PREFERENCESDIR;
const QString Preferences::PREFERENCESFILE = _PREFERENCESFILE;
