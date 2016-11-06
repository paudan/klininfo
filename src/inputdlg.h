/***************************************************************************
                          fileviewdlg.cpp  -  description
                             -------------------
    begin                : Pr Lie 5 21:16:06 2004
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

#ifndef INPUTDLG_H
#define INPUTDLG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QTextEdit;
class QPushButton;

class InputDlg : public QDialog
{
    Q_OBJECT

public:
    InputDlg( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~InputDlg();

    QLabel* cmd_title;
    QLineEdit* lineEdit1;
    QLabel* textLabel2;
    QTextEdit* textEdit1;
    QPushButton* buttonHelp;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

public slots:
    virtual void accept() { emit apply(); hide(); };

signals:
    void apply();

protected:
    QVBoxLayout* InputDlgLayout;
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

};

#endif // INPUTDLG_H
