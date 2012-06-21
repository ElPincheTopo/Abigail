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


#include "preferencestab.h"
#include "ui_preferencestab.h"
#include "preferences.h"

PreferencesTab::PreferencesTab(QWidget *parent) :
    Tab(parent),
    ui(new Ui::PreferencesTab)
{
    ui->setupUi(this);
}

PreferencesTab::~PreferencesTab()
{
    delete ui;
}

void PreferencesTab::loadPreferences()
{
    // Utilities
    ui->lineWrapCheck->setChecked(Preferences::lineWrap);

    // Text Area
    ui->columnLineCheck->setChecked(Preferences::columnLine);
    ui->columnLineBox->setValue(Preferences::columnOfLine);
    ui->fontSizeCheck->setValue(Preferences::fontSize);
}

void PreferencesTab::on_lineWrapCheck_stateChanged(int state)
{
    Preferences::lineWrap = (state != 0 ? true : false);
}

void PreferencesTab::on_columnLineCheck_stateChanged(int state)
{
    Preferences::columnLine = (state != 0 ? true : false);
}

void PreferencesTab::on_columnLineBox_valueChanged(int value)
{
    Preferences::columnOfLine = value;
}

void PreferencesTab::on_fontSizeCheck_valueChanged(int value)
{
    Preferences::fontSize = value;
}
