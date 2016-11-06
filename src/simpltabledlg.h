/***************************************************************************
                          simpltabledlg.h  -  description
                             -------------------
    begin                : Kt Lie 1 14:49:04 2004
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
 
#ifndef VERSIONINFODLG_H
#define VERSIONINFODLG_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QTable;

class VersionInfoDlg : public QWidget
{
    Q_OBJECT

public:
    VersionInfoDlg( QWidget* parent = 0, const char* name = 0, WFlags fl = 0, QString versionFile = "");
    ~VersionInfoDlg();

    QLabel* dlg_title;
    QTable* table1;

    QString errorMsg;

protected:
    QVBoxLayout* VersionInfoDlgLayout;

protected slots:
    virtual void languageChange();
    virtual void doSortColumn(int );

private:
    void readVersionFile(QString );
    QString getVersion(QString );
    int getLineCount(QString );

};

#endif // VERSIONINFODLG_H
