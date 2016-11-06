/***************************************************************************
                          finputdlg.h  -  description
                             -------------------
    begin                : Tr Lie 7 14:21:06 2004
    copyright            : (C) 2004 by Paulius Danenas
    email                : metalmaniac@xxx.lt
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/****************************************************************************
** Form interface generated from reading ui file '/home/Paulius/klininfo_v0.2/klininfo/src/finputdlg.ui'
**
** Created: Tr Lie 7 14:21:06 2004
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.2.1   edited May 19 14:22 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FILEINPUTDLG_H
#define FILEINPUTDLG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QToolButton;
class QLineEdit;
class QTextEdit;
class QPushButton;

class FileInputDlg : public QDialog
{
    Q_OBJECT

public:
    FileInputDlg( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~FileInputDlg();

    QLabel* textLabel1;
    QToolButton* toolButton1;
    QLineEdit* lineEdit1;
    QLabel* textLabel2;
    QTextEdit* textEdit1;
    QPushButton* buttonHelp;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

signals:
    void apply();

public slots:
    virtual void setFilename();
    virtual void accept();

protected:
    QGridLayout* FileInputDlgLayout;
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();
};

#endif // FILEINPUTDLG_H
