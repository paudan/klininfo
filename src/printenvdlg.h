/***************************************************************************
                          fileviewdlg.cpp  -  description
                             -------------------
    begin                : Pr Lie 5 15:54:16 2004
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

#ifndef PRINTENVDLG_H
#define PRINTENVDLG_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QTextBrowser;

class PrintEnvDlg : public QWidget
{
    Q_OBJECT

public:
    PrintEnvDlg( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~PrintEnvDlg();

    QTextBrowser* textBrowser1;

    virtual void saveToFile(QString filename, int flags = IO_WriteOnly);

protected:
    virtual void loadPEString();

    QVBoxLayout* PrintEnvDlgLayout;

protected slots:
    virtual void languageChange();

};

#endif // PRINTENVDLG_H
