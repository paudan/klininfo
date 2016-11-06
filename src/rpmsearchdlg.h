/***************************************************************************
                          rpmsearchdlg.h  -  description
                             -------------------
    begin                : Kt Lie 1 16:07:55 2004
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

#ifndef RPMSEARCHDLG_H
#define RPMSEARCHDLG_H

#include <qvariant.h>
#include <qwidget.h>

#define RPM_CMD  "rpm"
#define GREP_CMD "grep"
#define SORT_CMD "sort"
#define RPM_ARGS "-qa"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QPushButton;
class QTextBrowser;
class QLabel;
class QLineEdit;
class KProcess;

class RPMSearchDlg : public QWidget
{
    Q_OBJECT

public:
    RPMSearchDlg( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~RPMSearchDlg();

    QPushButton* buttonFind;
    QPushButton* buttonFindAll;
    QTextBrowser* kTextBrowser1;
    QLabel* textLabel1;
    QLineEdit* lineEdit1;

public slots:
    void showRPMS();
    void showAllRPMS();

protected:
    QGridLayout* RPMSearchDlgLayout;
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();
    virtual void runRPMFind();
    virtual void runRPMFindAll();
    virtual void receivedOutput(KProcess *, char * , int);
};

#endif // RPMSEARCHDLG_H
