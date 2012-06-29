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

#include <iostream>

#include <QtGui/QApplication>

#include "mainwindow.h"
#include "preferences.h"

int main(int argc, char *argv[])
{
    // License and info output to the terminal
    std::cout << "     Abigail, A lightweight, powerful and customizable cross-platform IDE.\n"
              << "     Copyright (C) 2012  Roberto Lapuente\n\n"
              << "     This program comes with ABSOLUTELY NO WARRANTY.\n"
              << "     This is free software, and you are welcome to redistribute it\n"
              << "     under certain conditions.\n\n"
              << "     Visit " << Preferences::HOMEPAGE.toStdString() << " for more information." << std::endl;

    // Command-line Argument Options

    // Load app preferences
    Preferences::readPreferences();

    // Run app
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int exec = a.exec();

    // Save app preferences
    Preferences::writePreferences();

    std::cout << "Goodbye!" << std::endl;
    return exec;
}
