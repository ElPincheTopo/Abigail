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


#ifndef PREFERENCESTAB_H
#define PREFERENCESTAB_H

#include "tab.h"

namespace Ui {
class PreferencesTab;
}

class PreferencesTab : public Tab
{
    Q_OBJECT

public:
    explicit PreferencesTab(QWidget *parent = 0);
    ~PreferencesTab();
    void loadPreferences();

private slots:
    void on_lineWrapCheck_stateChanged(int state);
    void on_columnLineCheck_stateChanged(int state);
    void on_columnLineBox_valueChanged(int value);
    void on_fontSizeBox_valueChanged(int value);
    void on_centerOnScrollCheck_stateChanged(int state);
    void on_tabLengthBox_valueChanged(int value);

private:
    Ui::PreferencesTab *ui;
};

#endif // PREFERENCESTAB_H
