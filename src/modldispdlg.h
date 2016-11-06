/***************************************************************************
                          modldispdlg.h  -  description
                             -------------------
    begin                : Pn Lie 9 21:02:20 2004
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

#ifndef MODULEDISPLAYDLG_H
#define MODULEDISPLAYDLG_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QTable;
class KProcess;

class ModuleDisplaydlg : public QWidget
{
    Q_OBJECT

public:
    ModuleDisplaydlg( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ModuleDisplaydlg();

    QLabel* dlg_title;
    QTable* table1;

    QString errMsg;

protected:
    QVBoxLayout* ModuleDisplaydlgLayout;
    QString bufout;
    virtual void displayData();

protected slots:
    virtual void languageChange();
    virtual void receivedOutput(KProcess *, char * , int);
    virtual void doSortColumn(int );

private:
    virtual void runLsmod();

};

#endif // MODULEDISPLAYDLG_H
