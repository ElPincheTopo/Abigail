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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QTextCursor>
#include <QTextDocument>

#include "about.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_actionAbout_activated();
    void on_actionQuit_activated();
    void on_actionAbigail_Home_Page_activated();
    void on_actionGet_Involved_activated();
    void on_actionSave_All_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    bool on_tabsManager_tabCloseRequested(int index);
    void on_actionSave_As_triggered();
    void on_actionFile_triggered();
    void on_actionCloseFile_triggered();
    void closeEvent(QCloseEvent *event);
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCopy_triggered();
    void on_actionCut_triggered();
    void on_actionPaste_triggered();
    void on_actionDelete_triggered();
    void on_tabsManager_currentChanged(QWidget *arg1);
    void on_action_Indent_triggered();
    void on_action_Unindent_triggered();
    void on_actionComment_triggered();
    void on_actionUncomment_triggered();
    void on_actionSearch_triggered();
    void on_searchTextEdit_textChanged(const QString);
    void on_action_Print_triggered();
    void on_searchNext_clicked();
    int search(QTextCursor *docCursor, QTextDocument::FindFlags flags = 0);
    void on_replace_clicked();
    void on_searchPrev_clicked();
    void on_searchBar_visibilityChanged(bool visible);
    void on_actionReplace_triggered();

    void on_actionLine_Wrap_triggered();

private:
    Ui::MainWindow *ui;
    bool replaceMode;
    QTextCursor *cursor;
};

#endif // MAINWINDOW_H
