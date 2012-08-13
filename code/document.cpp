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

#include <QTextStream>
#include <QStringList>

#include "document.h"

Document::Document(Tab *parent) : Tab(parent)
{
    this->file = 0;
    this->docHasChanged = false;
    this->layout = new QGridLayout(this);
    this->layout->setSpacing(2);
    this->layout->setMargin(0);
    this->setLayout(layout);
    this->textArea = new CodeEditor(this);
    this->layout->addWidget(textArea);
    this->docHasChanged = false;
    this->isCopyAvailable = false;
    this->isCutAvailable = false;
    this->isUndoAvailable = false;
    this->isRedoAvailable = false;

    QObject::connect(textArea, SIGNAL(textChanged()), this, SLOT(textChanges()));
    QObject::connect(textArea, SIGNAL(copyAvailable(bool)), this, SLOT(changeCutAvailability(bool)));
    QObject::connect(textArea, SIGNAL(copyAvailable(bool)), this, SLOT(changeCopyAvailability(bool)));
    QObject::connect(textArea, SIGNAL(undoAvailable(bool)), this, SLOT(changeUndoAvailability(bool)));
    QObject::connect(textArea, SIGNAL(redoAvailable(bool)), this, SLOT(changeRedoAvailability(bool)));
}

Document::~Document()
{
    delete file;
    delete textArea;
    delete layout;
}

QString* Document::saveAs(QString archivo)
{
    this->file = new QFile(archivo);
    file->open(QIODevice::WriteOnly);
    QTextStream stream(file);
    stream << textArea->document()->toPlainText();
    file->close();
    QStringList list = archivo.split("/");
    this->title = new QString(list[list.size()-1]);
    this->docHasChanged = false;
    return this->title;
}

void Document::save()
{
    file->open(QIODevice::WriteOnly);
    QTextStream stream(file);
    stream << textArea->document()->toPlainText();
    file->close();
    this->docHasChanged = false;
}

QString* Document::open(QString archivo)
{
    this->file = new QFile(archivo);
    this->file->open(QIODevice::ReadOnly);
    QTextStream stream(file);
    this->textArea->setPlainText(stream.readAll());
    file->close();
    QStringList list = archivo.split(Preferences::SLASH);
    this->title = new QString(list[list.size()-1]);
    this->docHasChanged = false;
    return this->title;
}

void Document::close()
{

}

void Document::textChanges()
{
    if (!docHasChanged) {
        docHasChanged = true;
        emit textChanged(this);
    }
}

void Document::changeCopyAvailability(bool available)
{
    emit this->copyAvailable(available);
}

void Document::changeCutAvailability(bool available)
{
    emit this->cutAvailable(available);
}

void Document::changeUndoAvailability(bool available)
{
    emit this->undoAvailable(available);
}

void Document::changeRedoAvailability(bool available)
{
    emit this->redoAvailable(available);
}

QString Document::fileName()
{
    return (this->file != 0 ? this->file->fileName() : 0);
}
