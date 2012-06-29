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

#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QPlainTextEdit>
#include <QFile>

#include "tab.h"
#include "codeeditor.h"

class Document : public Tab
{
    Q_OBJECT
public:
    explicit Document(Tab *parent = 0);
    ~Document();
    CodeEditor *textArea;
    bool docHasChanged;
    bool isCopyAvailable;
    bool isCutAvailable;
    bool isUndoAvailable;
    bool isRedoAvailable;

private:
    QFile *file;
    QGridLayout *layout;

signals:
    void textChanged(Document* doc);
    void copyAvailable(bool available);
    void cutAvailable(bool available);
    void undoAvailable(bool available);
    void redoAvailable(bool available);

public slots:
    void save();
    QString* saveAs(QString archivo);
    QString* open(QString archivo);
    void close();

private slots:
    void textChanges();
    void changeCopyAvailability(bool available);
    void changeCutAvailability(bool available);
    void changeUndoAvailability(bool available);
    void changeRedoAvailability(bool available);

};

#endif // DOCUMENT_H
