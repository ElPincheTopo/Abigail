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
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

TabManager::TabManager(QWidget *parent) : QTabWidget(parent)
{
    newDoc();
}

TabManager::~TabManager()
{

}

void TabManager::newDoc()
{
    Document *doc = new Document();
    int index = this->addTab(doc, "Untitled");
    this->setCurrentIndex(index);
    QObject::connect(doc, SIGNAL(textChanged(Document*)), this, SLOT(textChanges(Document*)));
    doc->textArea->setFocus();
}

void TabManager::save(int index)
{
    // Checar si no esta guardado
    Document *doc = dynamic_cast<Document*>(widget(index));
    doc->title == 0 ? saveAs() : doc->save(); // If the document has no title it's a new document and 'saveAs()' should be called instead
    if (doc->title != 0) { // If the Save as was canceled then end
        QString str = *(doc->title);
        this->setTabText(index, str);
    }
}

void TabManager::saveCurrentDoc()
{
    int index = currentIndex();
    if (index >=0) save(index);

}

void TabManager::saveAll()
{
    for (int i=0; i<count(); ++i)
        save(i);
}

void TabManager::saveAs()
{
    Document* doc = dynamic_cast<Document*>(currentWidget());
    if (doc != 0) {
        QString archivo = QFileDialog::getSaveFileName(this, "Save As", "/home/Untitled.txt");
        if (archivo != "") {
            QString* title = doc->saveAs(archivo);
            this->setTabText(this->currentIndex(), *title);
        }
    }
}

void TabManager::open(QString archivo)
{
    Document* doc = new Document();
    int index = this->addTab(doc, "");
    this->setCurrentIndex(index);
    QString* title = doc->open(archivo);
    this->setTabText(index, *title);
    QObject::connect(doc, SIGNAL(textChanged(int)), this, SLOT(textChanges(int)));
    doc->textArea->setFocus();
}

void TabManager::open()
{
    QStringList archivos = QFileDialog::getOpenFileNames(this, "Select a file to open...", "/home");
    foreach (QString archivo, archivos)
        open(archivo);
}

void TabManager::textChanges(Document* doc)
{
    QString title = doc->title == 0 ? "Untitled" : *(doc->title);
    this->setTabText(this->indexOf(doc), title.append("*"));
}

void TabManager::tabRemoved(int index)
{

}
