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
#include <QTextCursor>
#include <QTextDocumentFragment>
#include <QPrinter>
#include <QPrintDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "document.h"
#include "document.h"
#include "preferences.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->projectExplorer->close();
    ui->searchBar->close();
    this->replaceMode = false;
    this->cursor = 0;
    this->searchDirection = MainWindow::SearchNext;
    ui->statusBar->showMessage(QString("Hi! Welcome to Abigail"), 10000);

    // SearchBar Float Button
    QAbstractButton* button = ui->searchBar->findChild<QAbstractButton*>("qt_dockwidget_floatbutton");
    connect(button, SIGNAL(clicked()), this, SLOT(searchBarFloated()));

    // Connect signals
    connect(ui->tabsManager, SIGNAL(tabContextMenuEvent(QContextMenuEvent*)), this, SLOT(tabMenuRequested(QContextMenuEvent*)));
    connect(ui->tabsManager, SIGNAL(copyAvailable(bool)), ui->actionCopy, SLOT(setEnabled(bool)));
    connect(ui->tabsManager, SIGNAL(cutAvailable(bool)), ui->actionCut, SLOT(setEnabled(bool)));
    connect(ui->tabsManager, SIGNAL(undoAvailable(bool)), ui->actionUndo, SLOT(setEnabled(bool)));
    connect(ui->tabsManager, SIGNAL(redoAvailable(bool)), ui->actionRedo, SLOT(setEnabled(bool)));

    int argc= QApplication::argc();
    QStringList argv= QApplication::arguments();

    if (argc < 2)
        ui->tabsManager->newDoc();
    else
        for (int i=1; i<argc; ++i)
            ui->tabsManager->openFile(argv[i]);
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
    QDesktopServices::openUrl(QUrl(Preferences::HOMEPAGE));
}

void MainWindow::on_actionGet_Involved_activated()
{
    QDesktopServices::openUrl(QUrl(Preferences::REPO));
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

bool MainWindow::on_tabsManager_tabCloseRequested(int index)
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->widget(index));
    bool closed = true;

    if (doc != 0) { // If the tab is a Document
        int ret = QMessageBox::Discard; // If the document hasn't been changed discard the changes(thar are non-existant)
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
            closed = false;

        }

        // If the user clicked 'cancel' do nothing, else...
        // If the user clicked 'save' call 'save' and retry closing tab
        if (ret == QMessageBox::Save) {
            ui->tabsManager->save(index);
            on_tabsManager_tabCloseRequested(index);
            closed = true;
        }

        // If the user clicked 'discard' or if the document was saved already delete the tab
        if (ret == QMessageBox::Discard) {
            doc->deleteLater();
            closed = true;
        }
    } else { // If the tab is not a document
        // If the tab is a preferences tab
        PreferencesTab* pref = dynamic_cast<PreferencesTab*>(ui->tabsManager->widget(index));
        if (pref != 0) {
            Preferences::writePreferences();
            pref->deleteLater();
        }
    }

    return closed;
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
    bool tabsClosed = true;

    for (int i=0; i<ui->tabsManager->count(); ++i)
        if (!on_tabsManager_tabCloseRequested(i))
            tabsClosed = false;
    (tabsClosed) ? event->accept() : event->ignore();
}

void MainWindow::on_actionUndo_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    if (doc != 0) doc->textArea->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    if (doc != 0) doc->textArea->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    if (doc != 0) doc->textArea->copy();
}

void MainWindow::on_actionCut_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    if (doc != 0) doc->textArea->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    if (doc != 0) doc->textArea->paste();
}

void MainWindow::on_actionDelete_triggered()
{
    // Erase current selected text or object in project manager
}

void MainWindow::on_tabsManager_currentChanged(QWidget *tab)
{
    Document* doc = dynamic_cast<Document*>(tab);
    if (doc != 0) { // If the tab is a document
        doc->textArea->setFocus();
        if (!ui->menuTab->isEnabled()) ui->menuTab->setEnabled(true);
        ui->actionLine_Wrap->setChecked(doc->textArea->lineWrapMode() == QPlainTextEdit::WidgetWidth? true : false);
    } else { // If the tab is not a document
        PreferencesTab* pref = dynamic_cast<PreferencesTab*>(tab);
        if (pref != 0) { // If tab is a preferences tab
            pref->loadPreferences();
            if (ui->menuTab->isEnabled()) ui->menuTab->setEnabled(false);
        }

    }
}

void MainWindow::on_action_Indent_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    QTextCursor cursor = doc->textArea->textCursor();

    cursor.beginEditBlock();
    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();
    cursor.clearSelection();

    cursor.setPosition(end);
    cursor.movePosition(QTextCursor::EndOfLine);
    end = cursor.position();

    cursor.setPosition(start);
    cursor.movePosition(QTextCursor::StartOfLine);
    start = cursor.position();

    do {
        cursor.movePosition(QTextCursor::StartOfLine);
        cursor.insertText("    ");
        cursor.movePosition(QTextCursor::EndOfLine);
        end += 4;
    } while (cursor.position() < end && cursor.movePosition(QTextCursor::Down));

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.endEditBlock();
    doc->textArea->setTextCursor(cursor);
}

void MainWindow::on_action_Unindent_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    QTextCursor cursor = doc->textArea->textCursor();

    cursor.beginEditBlock();
    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();
    cursor.clearSelection();

    cursor.setPosition(end);
    cursor.movePosition(QTextCursor::EndOfLine);
    end = cursor.position();

    cursor.setPosition(start);
    cursor.movePosition(QTextCursor::StartOfLine);
    start = cursor.position();

    do {
        cursor.movePosition(QTextCursor::StartOfLine);
        cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, 4);
        if (cursor.selectedText() == "    ") cursor.removeSelectedText();
        cursor.movePosition(QTextCursor::EndOfLine);
        end -= 4;
    } while (cursor.position() < end && cursor.movePosition(QTextCursor::Down));

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.endEditBlock();
    doc->textArea->setTextCursor(cursor);
}

void MainWindow::on_actionComment_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    QTextCursor cursor = doc->textArea->textCursor();

    cursor.beginEditBlock();
    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();
    cursor.clearSelection();

    cursor.setPosition(end);
    cursor.movePosition(QTextCursor::EndOfLine);
    end = cursor.position();

    cursor.setPosition(start);
    cursor.movePosition(QTextCursor::StartOfLine);
    start = cursor.position();

    do {
        cursor.movePosition(QTextCursor::StartOfLine);
        cursor.insertText("// ");
        cursor.movePosition(QTextCursor::EndOfLine);
        end += 3;
    } while (cursor.position() < end && cursor.movePosition(QTextCursor::Down));

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.endEditBlock();
    doc->textArea->setTextCursor(cursor);
}

void MainWindow::on_actionUncomment_triggered()
{
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    QTextCursor cursor = doc->textArea->textCursor();

    cursor.beginEditBlock();
    int start = cursor.selectionStart();
    int end = cursor.selectionEnd();
    cursor.clearSelection();

    cursor.setPosition(end);
    cursor.movePosition(QTextCursor::EndOfLine);
    end = cursor.position();

    cursor.setPosition(start);
    cursor.movePosition(QTextCursor::StartOfLine);
    start = cursor.position();

    QString selection;
    int spaces = 2;
    int pos = 0;

    do {
        cursor.movePosition(QTextCursor::StartOfLine);
        do {
            cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
            selection = cursor.selectedText();
            if (selection == "/") {
                pos = cursor.position() - 1;
                cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
                if (cursor.selectedText() == "//") {
                    cursor.removeSelectedText();
                    cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
                    spaces = 2;
                    if (cursor.selectedText() == " ") {
                        cursor.removeSelectedText();
                        spaces = 3;
                    }
                }
            }
            cursor.clearSelection();
        } while (selection == " " || selection == "\t");
        cursor.movePosition(QTextCursor::EndOfLine);
        end -= spaces;
    } while (cursor.position() < end && cursor.movePosition(QTextCursor::Down));

    cursor.setPosition(pos);
    cursor.endEditBlock();
    doc->textArea->setTextCursor(cursor);
}

void MainWindow::on_action_Print_triggered()
{
    QPrinter printer;
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (dlg->exec() != QDialog::Accepted)
        return;
    Document* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    doc->textArea->document()->print(&printer);
}

void MainWindow::on_actionSearch_triggered()
{
    if (!ui->searchBar->isVisible()) {
        replaceMode = false;
        ui->searchBar->setVisible(true);
    }
    ui->searchTextEdit->setFocus();
}

void MainWindow::on_searchTextEdit_textChanged(const QString)
{

    Document *doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget());
    QTextCursor *docCursor = new QTextCursor(doc->textArea->textCursor());
    docCursor->movePosition(QTextCursor::Start);
    this->search(docCursor);
}

void MainWindow::on_searchNext_clicked()
{
    QTextCursor *docCursor;
    int ret = QMessageBox::No;

    if (this->cursor == 0) {
        CodeEditor* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget())->textArea;
        docCursor = new QTextCursor(doc->textCursor());
    } else {
        docCursor = this->cursor;
    }
    int pos = this->search(docCursor);
    if (pos < 0) {
        // Avisar que no se encontro.
        ret = QMessageBox::warning(this, "Abigail",
                                       "Your search reached the end of the document.\nDo you want to search from the top?",
                                        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        pos = 0;
    }
    docCursor->setPosition(pos);
    this->cursor = docCursor;
    if (ret == QMessageBox::Yes) on_searchNext_clicked();
    ui->searchTextEdit->setFocus();

    if (this->searchDirection == MainWindow::SearchPrevious) {
        this->searchDirection = MainWindow::SearchNext;
        this->on_searchNext_clicked();
    }
}

void MainWindow::on_searchPrev_clicked()
{
    QTextCursor *docCursor;
    int ret = QMessageBox::No;

    if (this->cursor == 0) {
        CodeEditor* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget())->textArea;
        docCursor = new QTextCursor(doc->textCursor());
    } else {
        docCursor = this->cursor;
    }
    int pos = this->search(docCursor, QTextDocument::FindBackward);
    int len = ui->searchTextEdit->text().size();
    docCursor->movePosition(QTextCursor::End);
    int max = docCursor->position();

    pos = pos - len;
    if (pos < 0) {
        // Avisar que no se encontro.
        ret = QMessageBox::warning(this, "Abigail",
                                       "Your search reached the beginning of the document.\nDo you want to search from the bottom?",
                                        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        pos = max;
    }
    docCursor->setPosition(pos);
    this->cursor = docCursor;
    if (ret == QMessageBox::Yes) on_searchPrev_clicked();
    ui->searchTextEdit->setFocus();

    if (this->searchDirection == MainWindow::SearchNext) {
        this->searchDirection = MainWindow::SearchPrevious;
        this->on_searchPrev_clicked();
    }
}

int MainWindow::search(QTextCursor *docCursor, QTextDocument::FindFlags flags)
{
    CodeEditor* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget())->textArea;
    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection selection;
    QRegExp regExp(ui->searchTextEdit->text());
    QColor selectionColor = QColor(QRgb(Preferences::selectionColor));

    #ifdef QT5
        regExp.setPatternSyntax(QRegExp::RegExp); // In Qt4, in Qt5 it should be RegExp
    #else
        regExp.setPatternSyntax(QRegExp::RegExp2); // In Qt4, in Qt5 it should be RegExp
    #endif

    QTextCursor findResult = doc->document()->find(regExp, *docCursor, flags);
    selection.cursor = findResult;
    int posFound = findResult.position();

    if (findResult.isNull()) {
        selection.cursor.clearSelection();
        //flags == QTextDocument::FindBackward ? docCursor->movePosition(QTextCursor::Start) : docCursor->movePosition(QTextCursor::End);
        //docCursor->setPosition(pos);
    } else {
        selection.format.setBackground(selectionColor);
        extraSelections.append(selection);
        if (this->cursor != 0)
            this->cursor->setPosition(posFound);
        else
            this->cursor = new QTextCursor(findResult);
    }
    doc->setExtraSelections(extraSelections);
    //docCursor->setPosition(pos);
    //doc->setTextCursor(*docCursor);

    return posFound;
}

void MainWindow::on_replace_clicked()
{
    CodeEditor* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget())->textArea;

    QList<QTextEdit::ExtraSelection> list = doc->extraSelections();

    foreach(QTextEdit::ExtraSelection selection, list) {
        selection.cursor.removeSelectedText();
        selection.cursor.insertText(ui->replaceTextEdit->text());
    }

    on_searchNext_clicked();
}

void MainWindow::on_actionReplace_triggered()
{
    replaceMode = true;
    on_searchBar_visibilityChanged(true);
    if (!ui->searchBar->isVisible()) ui->searchBar->setVisible(true);
    ui->searchTextEdit->setFocus();
}

void MainWindow::on_searchBar_visibilityChanged(bool visible)
{
    if (visible) {
        if (replaceMode) {
            ui->replaceLabel->show();
            ui->replaceTextEdit->show();
            ui->replace->show();
            this->searchDirection = MainWindow::SearchNext;
        } else {
            ui->replaceLabel->hide();
            ui->replaceTextEdit->hide();
            ui->replace->hide();
        }
    }

    if (ui->searchBar->isFloating()) {
        int x = ui->searchBar->x();
        int y = ui->searchBar->y();
        ui->searchBar->setGeometry(QRect(x,y,400,60));
    }
}

void MainWindow::searchBarFloated()
{
    if (ui->searchBar->isFloating()) {
        int x = (this->x() + this->width()) - 410;
        int y = (this->y() + this->height()) - 70;
        ui->searchBar->setGeometry(QRect(x,y,400,60));
    }
}

void MainWindow::on_actionLine_Wrap_triggered()
{
    CodeEditor* doc = dynamic_cast<Document*>(ui->tabsManager->currentWidget())->textArea;
    if (ui->actionLine_Wrap->isChecked())
        doc->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    else
        doc->setLineWrapMode(QPlainTextEdit::NoWrap);
}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionPreferences_triggered()
{
    ui->tabsManager->openPreferences();
}

void MainWindow::on_actionAdvanced_Search_triggered()
{

}

void MainWindow::tabMenuRequested(QContextMenuEvent *event)
{
    ui->menuTab->exec(event->globalPos());
}
