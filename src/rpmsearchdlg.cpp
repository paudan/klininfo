/***************************************************************************
                          rpmsearchdlg.cpp  -  description
                             -------------------
    begin                : Kt Lie 1 16:07:57 2004
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

#include "rpmsearchdlg.h"


#include <qvariant.h>
#include <qpushbutton.h>
#include <qtextbrowser.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qtextbrowser.h>
#include <kprocess.h>
#include <kmessagebox.h>

/*
 *  Constructs a RPMSearchDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
RPMSearchDlg::RPMSearchDlg( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "RPMSearchDlg" );
    RPMSearchDlgLayout = new QGridLayout( this, 1, 1, 11, 6, "RPMSearchDlgLayout");

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( spacer );

    buttonFind = new QPushButton( this, "buttonFind" );
    buttonFind->setAutoDefault( TRUE );
    buttonFind->setDefault( TRUE );
    Layout1->addWidget( buttonFind );

    buttonFindAll = new QPushButton( this, "buttonFindAll" );
    buttonFindAll->setAutoDefault( TRUE );
    Layout1->addWidget( buttonFindAll );

    RPMSearchDlgLayout->addMultiCellLayout( Layout1, 0, 0, 0, 1 );

    kTextBrowser1 = new QTextBrowser( this, "kTextBrowser1" );

    RPMSearchDlgLayout->addMultiCellWidget( kTextBrowser1, 2, 2, 0, 1 );

    textLabel1 = new QLabel( this, "textLabel1" );

    RPMSearchDlgLayout->addWidget( textLabel1, 1, 0 );

    lineEdit1 = new QLineEdit( this, "lineEdit1" );

    RPMSearchDlgLayout->addWidget( lineEdit1, 1, 1 );
    languageChange();
    resize( QSize(517, 361).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonFind, SIGNAL( clicked() ), this, SLOT( showRPMS() ) );
    connect( buttonFindAll, SIGNAL( clicked() ), this, SLOT( showAllRPMS() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
RPMSearchDlg::~RPMSearchDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void RPMSearchDlg::languageChange()
{
    setCaption( tr( "RPM Search Dialog" ) );
    buttonFind->setText( tr( "Find RPM" ) );
    buttonFind->setAccel( QKeySequence( QString::null ) );
    buttonFindAll->setText( tr( "List All RPM packages" ) );
    buttonFindAll->setAccel( QKeySequence( QString::null ) );
    textLabel1->setText( tr( "Line to search:" ) );
}

void RPMSearchDlg::runRPMFind()
{
  KProcess* process = new KProcess();
  process->clearArguments();
  (*process) << RPM_CMD << RPM_ARGS << "|" << GREP_CMD << (const char*)lineEdit1->text().latin1() << "|" << SORT_CMD;
  process->setUseShell(true, "/bin/bash");
  connect(process, SIGNAL(receivedStdout(KProcess*, char*, int) ), this, SLOT(receivedOutput(KProcess *, char *, int)) );
  if ( !process->start(KProcess::NotifyOnExit, KProcess::AllOutput) )
        KMessageBox::error( this, tr("Error: could not retrieve RPM package information"), QString("KLinInfo v0.2"), KMessageBox::Notify);
}

void RPMSearchDlg::runRPMFindAll()
{
  KProcess* process = new KProcess();
  process->clearArguments();
  process->setUseShell(true, "/bin/bash");
  (*process) << RPM_CMD << RPM_ARGS << "|" << SORT_CMD;
  connect(process, SIGNAL(receivedStdout(KProcess*, char*, int) ), this, SLOT(receivedOutput(KProcess *, char *, int)) );
  if ( !process->start(KProcess::NotifyOnExit, KProcess::AllOutput) )
        KMessageBox::error( this, tr("Error: could not retrieve RPM package information"), QString("KLinInfo v0.2"), KMessageBox::Notify);
}

void RPMSearchDlg::receivedOutput(KProcess *, char output[], int )
{
  kTextBrowser1->setText(kTextBrowser1->text() + QString(output) + "\n");
}

void RPMSearchDlg::showRPMS()
{
   kTextBrowser1->setText("");
   runRPMFind();
}

void RPMSearchDlg::showAllRPMS()
{
   kTextBrowser1->setText("");
   runRPMFindAll();
}

#include "rpmsearchdlg.moc"
