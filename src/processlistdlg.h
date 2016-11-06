/***************************************************************************
                          processlistdlg.h  -  description
                             -------------------
    begin                : Pn Lie 2 16:38:42 2004
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

#ifndef PROCESSLISTDLG_H
#define PROCESSLISTDLG_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QButtonGroup;
class QGridLayout;
class QRadioButton;
class QTable;
class QCheckBox;
class QLabel;
class QPushButton;

class ProcessListDlg : public QWidget
{
    Q_OBJECT

public:
    ProcessListDlg( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ProcessListDlg();
    

    QButtonGroup* groupBox1;
    QRadioButton* radioButton2;
    QRadioButton* radioButton1;
    QRadioButton* radioButton4;
    QRadioButton* radioButton3;
    QTable* table1;
    QCheckBox* checkBox1;
    QCheckBox* checkBox2;
    QLabel* textLabel1;
    QPushButton* refreshButton1;

protected:
    QGridLayout* ProcessListDlgLayout;
    QGridLayout* groupBox1Layout;

protected slots:
    virtual void languageChange();

public slots:
    virtual void showNormal_Checked();
    virtual void showUserOriented_Checked();
    virtual void showSignals_Checked();
    virtual void showRegisters_Checked();
    virtual void refresh();
    virtual void doSortColumn(int );

private:
    int lineCount(QString );
    virtual void readInfo();
    virtual void displayNormal(char *);
    virtual void displayUserOriented(char *);
    virtual void displaySignals(char *);
    virtual void displayRegisters(char *);

};

#endif // PROCESSLISTDLG_H
