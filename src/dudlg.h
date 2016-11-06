/***************************************************************************
                          fileviewdlg.cpp  -  description
                             -------------------
    begin                : Tr Lie 7 23:50:59 2004
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

#ifndef DISKUSAGEDLG_H
#define DISKUSAGEDLG_H

#include <qvariant.h>
#include <qwidget.h>

#define DF_CMD "df"
#define DF_ARGS "-aTB"
#define DF_HUMAN_READ "-aTh"
#define LIMIT_FULL 95

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QTable;
class QLabel;
class KComboBox;
class KProcess;
class QPalette;

class DiskUsageDlg : public QWidget
{
    Q_OBJECT

public:
    DiskUsageDlg( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~DiskUsageDlg();

    QTable* table1;
    QLabel* textLabel1;
    KComboBox* kComboBox1;
    KProcess *process;

    void saveToFile(QString filename, int flags = IO_WriteOnly);

public slots:
    virtual void dispSelected(int );
    virtual void receivedOutput(KProcess *, char * , int);

protected:
    QGridLayout* DiskUsageDlgLayout;
    QString bufout;

protected slots:
    virtual void languageChange();
    virtual void displayData();

private:
    virtual void runDU(const char *);
    virtual void runDU();
    QPalette progressRed();
    QPalette progressGrey();
};

#endif // DISKUSAGEDLG_H
