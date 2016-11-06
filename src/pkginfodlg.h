/***************************************************************************
                          pkginfodlg.h  -  description
                             -------------------
    begin                : Pn Lie 2 23:40:38 2004
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

#ifndef PKGINFODLG_H
#define PKGINFODLG_H

#define PACKAGE_INFO_DIR "/var/log/packages"

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QTable;
class QTabWidget;
class QTextBrowser;

class pkgInfoDlg : public QWidget
{
    Q_OBJECT

public:
    pkgInfoDlg( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~pkgInfoDlg();

    QLabel* textLabel1;
    QTable* table1;
    QTabWidget* tabWidget2;
    QWidget* tab;
    QTextBrowser* textBrowser1;
    QWidget* tab_2;
    QTextBrowser* textBrowser2;

    QString errorMsg;

protected:
    QVBoxLayout* pkgInfoDlgLayout;
    QVBoxLayout* tabLayout;
    QVBoxLayout* tabLayout_2;

    void loadPackageList();

protected slots:
    virtual void languageChange();
    void showPackageInfo(int , int , int, const QPoint& );
    virtual void doSortColumn(int );

private:
    int packageCount();
    bool genPKGInfoFile();

};

#endif // PKGINFODLG_H
