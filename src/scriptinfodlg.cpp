/***************************************************************************
                          scriptinfodlg.cpp  -  description
                             -------------------
    begin                : Pr Lie 5 02:32:02 2004
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

#include "scriptinfodlg.h"

#include <qvariant.h>
#include <qlabel.h>
#include <ktextbrowser.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <kmessagebox.h>
#include <qprocess.h>


/*
 *  Constructs a ScriptInfoDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'. A script file for
 *  parsing is also passed as an argument of the constructor
 */
ScriptInfoDlg::ScriptInfoDlg( QWidget* parent, const char* name, WFlags fl, QString scriptFile)
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "ScriptInfoDlg" );
    ScriptInfoDlgLayout = new QVBoxLayout( this, 11, 6, "ScriptInfoDlgLayout"); 

    dlg_title = new QLabel( this, "dlg_title" );
    ScriptInfoDlgLayout->addWidget( dlg_title );

    kTextBrowser1 = new KTextBrowser( this, "kTextBrowser1" );
    ScriptInfoDlgLayout->addWidget( kTextBrowser1 );
    languageChange();
    resize( QSize(600, 482).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    output = "";

   execscr = new QProcess();
   connect( execscr, SIGNAL(readyReadStdout()), this, SLOT(receivedStdOutOutput() ) );
   connect( execscr, SIGNAL(processExited()), this, SLOT(loadInfo()) );

   execscr->setArguments(scriptFile);
   if ( !execscr->start() )
        KMessageBox::error( this, tr("Fatal error. Script %1 could not be executed").arg(scriptFile), QString("KLinInfo v0.2"), KMessageBox::Notify);
}

/*
 *  Destroys the object and frees any allocated resources
 */
ScriptInfoDlg::~ScriptInfoDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ScriptInfoDlg::languageChange()
{
    setCaption( tr( "Script Information" ) );
    dlg_title->setText( tr( "Custom Linux information:" ) );
}

void ScriptInfoDlg::loadInfo()
{
  kTextBrowser1->setText(output);
}

void ScriptInfoDlg::receivedStdOutOutput()
{
  output.append(execscr->readStdout());
}

#include "scriptinfodlg.moc"
