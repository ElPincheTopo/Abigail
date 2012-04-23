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


#include "tabmanager.h"
#include <QTabBar>
#include <algorithm>

TabManager::TabManager(QWidget *parent) : QTabWidget(parent)
{

}

TabManager::~TabManager()
{

}

void TabManager::newDoc()
{
    Document *doc = new Document();
    int index = this->addTab(doc, "New Tab");
    this->setCurrentIndex(index);
    doc->textArea->setFocus();
}

void TabManager::save(int index)
{
    // Checar si no esta guardado
    dynamic_cast<Document*>(widget(index))->save();
}

void TabManager::saveCurrentDoc()
{
    int index = currentIndex();
    save(index);
}

void TabManager::saveAll()
{
    for (int i=0; i<count(); ++i) {
        save(i);
    }
}

void TabManager::saveAs(QString archivo)
{
    QString* title = dynamic_cast<Document*>(currentWidget())->saveAs(archivo);
    this->setTabText(this->currentIndex(), *title);
}

void TabManager::open(QString archivo)
{
    Document *doc = new Document();
    int index = this->addTab(doc, "");
    this->setCurrentIndex(index);
    QString* title = doc->open(archivo);
    this->setTabText(index, *title);
    doc->textArea->setFocus();
}

void TabManager::open(QStringList archivos)
{
    foreach (QString archivo, archivos)
        open(archivo);
}

