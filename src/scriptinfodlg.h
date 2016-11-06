/***************************************************************************
                          fileviewdlg.cpp  -  description
                             -------------------
    begin                : Pr Lie 5 02:32:01 2004
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

#ifndef SCRIPTINFODLG_H
#define SCRIPTINFODLG_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class KTextBrowser;
class QProcess;
class KMessageBox;

class ScriptInfoDlg : public QWidget
{
    Q_OBJECT

public:
    ScriptInfoDlg( QWidget* parent = 0, const char* name = 0, WFlags fl = 0, QString scriptFile = "");
    ~ScriptInfoDlg();

    QLabel* dlg_title;
    KTextBrowser* kTextBrowser1;

protected:
    QVBoxLayout* ScriptInfoDlgLayout;
    QProcess *execscr;

protected slots:
    virtual void languageChange();

public slots:
    void receivedStdOutOutput();
    void loadInfo( );

private:
    QString output;
};

#endif // SCRIPTINFODLG_H
