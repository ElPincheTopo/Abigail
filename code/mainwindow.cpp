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

#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "document.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->projectExplorer->close();
    ui->statusBar->showMessage(QString("Hi! Welcome to Abigail"), 10000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionAbout_activated()
{
    About about(this);
    about.exec();
}

void MainWindow::on_actionQuit_activated()
{
    this->close();
}

void MainWindow::on_actionAbigail_Home_Page_activated()
{
    QDesktopServices::openUrl(QUrl("http://elpinchetopo.github.com/Abigail/"));
}

void MainWindow::on_actionGet_Involved_activated()
{
    QDesktopServices::openUrl(QUrl("https://github.com/ElPincheTopo/Abigail"));
}

void MainWindow::on_actionSave_All_triggered()
{
    ui->tabsManager->saveAll();
}

void MainWindow::on_actionOpen_triggered()
{
    ui->tabsManager->open();
}

void MainWindow::on_actionSave_triggered()
{
    // Aqui hay que checar si el documento ya esta guardado
    ui->tabsManager->saveCurrentDoc();
}

void MainWindow::on_tabsManager_tabCloseRequested(int index)
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->widget(index));
    int ret = QMessageBox::Discard;
    // If the Document has changed since las save, ask the user what to do
    if (doc->docHasChanged) {
        QString title = (doc->title == 0 ? QString("Untitled") : *(doc->title));
        QString msgText("The document '");
        msgText.append(title).append("' has been modified.");
        QMessageBox msgBox;
        msgBox.setText(msgText);
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        ret = msgBox.exec();
    }

    // If the user clicked 'cancel' do nothing, else...
    if (ret != QMessageBox::Cancel) {
        // If the user clicked 'save' emit save signal, then...
        if (ret == QMessageBox::Save)
            emit ui->actionSave->trigger();
        // No matter what, delte the doc and remove the tab
        delete doc;
        ui->tabsManager->removeTab(index);
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    ui->tabsManager->saveAs();
}

void MainWindow::on_actionFile_triggered()
{
    ui->tabsManager->newDoc();
}

void MainWindow::on_actionCloseFile_triggered()
{
    int index = ui->tabsManager->currentIndex();
    on_tabsManager_tabCloseRequested(index);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Here it must check if the tabs are already saved
    event->accept();
}

void MainWindow::on_actionUndo_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    doc->textArea->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    doc->textArea->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    doc->textArea->copy();
}

void MainWindow::on_actionCut_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    doc->textArea->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    doc->textArea->paste();
}

void MainWindow::on_actionDelete_triggered()
{
    // Erase current selected text or object in project manager
}
