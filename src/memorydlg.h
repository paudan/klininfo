/***************************************************************************
                          memorydlg.h  -  description
                             -------------------
    begin                : Pr Lie 12 18:36:51 2004
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
 
#ifndef MEMORYDISPDLG_H
#define MEMORYDISPDLG_H

#include <qvariant.h>
#include <qwidget.h>

#define FREE_CMD "free"
#define FREE_ARGS "-tb"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QLabel;
class QTable;
class KProcess;
class QResizeEvent;
class QTimer;

class MemoryDispDlg : public QWidget
{
    Q_OBJECT

public:
    MemoryDispDlg( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~MemoryDispDlg();

    QFrame* line1;
    QLabel* textLabel3;
    QLabel* textLabel2;
    QLabel* textLabel1;
    QTable* table1;
    QFrame* frame5;
    QFrame* frame4;
    QFrame* frame3;
    QTimer* timer1;

protected:
    QGridLayout* MemoryDispDlgLayout;
    QString bufout;
    virtual void drawGraphs();
    virtual void resizeEvent(QResizeEvent *);

protected slots:
    virtual void languageChange();
    virtual void receivedOutput(KProcess *, char * , int);
    virtual void runFree();

private:
    virtual void displayData();
    void dispKBMBSizes(QString , int );
};

#endif // MEMORYDISPDLG_H
