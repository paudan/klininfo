/***************************************************************************
                          partitiondlg.cpp  -  description
                             -------------------
    begin                : Lie 10 20:15:38 2004
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

#ifndef PARTITIONDISPDLG_H
#define PARTITIONDISPDLG_H

#include <qvariant.h>
#include <qwidget.h>

#define FDISK_CMD "fdisk"
#define FDISK_ARG1 "-l"
#define FDISK_ARG2 "-u"
#define CFDISK_CMD "cfdisk"
#define CFDISK_ARGPRINT "-P"
#define CFDISK_ARGRAW "r"
#define CFDISK_ARGSECT "s"
#define CFDISK_ARGTRAW "t"
#define HDPARM_CMD "hdparm"
#define HDPARM_ARGINFO1 "-I"
#define HDPARM_ARGINFO2 "/dev/hd?"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class KComboBox;
class QTextBrowser;
class KProcess;

class PartitionDispDlg : public QWidget
{
    Q_OBJECT

public:
    PartitionDispDlg( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~PartitionDispDlg();

    QLabel* dlg_title;
    QLabel* textLabel2;
    KComboBox* kComboBox1;
    QTextBrowser* textBrowser1;
    QTextBrowser* textBrowser2;

public slots:
    virtual void typeSelected(int);

protected:
    QGridLayout* PartitionDispDlgLayout;
    QString buffer, buffer_hdparm;
    virtual void runCommand(const char* , const char*, const char*);
    virtual void run_hdparm();

protected slots:
    virtual void languageChange();
    virtual void receivedOutput(KProcess *, char * , int);
    virtual void receivedOutputHDP(KProcess *, char * , int);
    virtual void processFinished(KProcess *, char *, int);
};

#endif // PARTITIONDISPDLG_H
