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


#include "document.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

Document::Document(QWidget *parent) : QWidget(parent)
{
    this->file = 0;
    this->title = 0;
    this->layout = new QGridLayout(this);
    this->layout->setSpacing(2);
    this->layout->setMargin(0);
    this->setLayout(layout);
    this->textArea = new QTextEdit(this);
    this->textArea->setLineWrapMode(QTextEdit::NoWrap);
    this->textArea->setAcceptDrops(true);
    this->textArea->setAcceptRichText(true);
    this->textArea->setUndoRedoEnabled(true);
    this->textArea->setFont(QFont("Mono" , 11));
    this->layout->addWidget(textArea);
    this->textArea->show();
    this->textArea->setFocus();
}

Document::~Document()
{
    delete layout;
    delete file;
    delete textArea;
    delete title;
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
    return this->title;
}

void Document::save()
{
    file->open(QIODevice::WriteOnly);
    QTextStream stream(file);
    stream << textArea->document()->toPlainText();
    file->close();
}

QString* Document::open(QString archivo)
{
    this->file = new QFile(archivo);
    this->file->open(QIODevice::ReadOnly);
    QTextStream stream(file);
    this->textArea->setText(stream.readAll());
    file->close();
    QStringList list = archivo.split("/");
    this->title = new QString(list[list.size()-1]);
    return this->title;
}

void Document::close()
{

}