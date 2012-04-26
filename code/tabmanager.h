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


#ifndef TABMANAGER_H
#define TABMANAGER_H

#include <QTabWidget>
#include "document.h"

class TabManager : public QTabWidget
{
    Q_OBJECT
public:
    explicit TabManager(QWidget *parent = 0);
    ~TabManager();
private:
    void save(int index);
    void open(QString archivo);

signals:
    void textChanged(int index);

public slots:
    void newDoc();
    void saveCurrentDoc();
    void saveAll();
    void saveAs();
    void open();
    void tabMoved(int from, int to);

private slots:
    void textChanges(int index);

};

#endif // TABMANAGER_H
