/***************************************************************************
                          modldispdlg.cpp  -  description
                             -------------------
    begin                : Pn Lie 9 21:02:22 2004
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

#include "modldispdlg.h"


#include <qvariant.h>
#include <qlabel.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <kprocess.h>
#include <qtextstream.h>
#include <kmessagebox.h>

/*
 *  Constructs a ModuleDisplaydlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
ModuleDisplaydlg::ModuleDisplaydlg( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "ModuleDisplaydlg" );
    ModuleDisplaydlgLayout = new QVBoxLayout( this, 11, 6, "ModuleDisplaydlgLayout"); 

    dlg_title = new QLabel( this, "dlg_title" );
    ModuleDisplaydlgLayout->addWidget( dlg_title );

    table1 = new QTable( this, "table1" );
    table1->setNumRows( 0 );
    table1->setNumCols( 4 );
    table1->setShowGrid( FALSE );
    table1->setLeftMargin( 0 );
    table1->verticalHeader()->hide();
    table1->horizontalHeader()->setLabel( 0, tr("Module") );
    table1->horizontalHeader()->setLabel( 1, tr("Size") );
    table1->horizontalHeader()->setLabel( 2, tr("Used by") );
    table1->horizontalHeader()->setLabel( 3, tr("Not tainted") );
    ModuleDisplaydlgLayout->addWidget( table1 );
    connect(table1->horizontalHeader(), SIGNAL(clicked(int ) ), this, SLOT(doSortColumn(int ) ) );
    languageChange();
    resize( QSize(600, 482).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
    runLsmod();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ModuleDisplaydlg::~ModuleDisplaydlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ModuleDisplaydlg::languageChange()
{
    setCaption( tr( "Module Display Dialog" ) );
    dlg_title->setText( tr( "Modules, loaded currently in Linux kernel:" ) );
}

void ModuleDisplaydlg::runLsmod()
{
  KProcess *process = new KProcess();
  process->clearArguments();
  (*process) << "lsmod";
  connect(process, SIGNAL(receivedStdout(KProcess*, char*, int) ), this, SLOT(receivedOutput(KProcess *, char *, int)) );
  if ( !process->start(KProcess::NotifyOnExit, KProcess::AllOutput) )
        KMessageBox::error( this, tr("Fatal error running lsmod. Module information could not be retrieved"), QString("KLinInfo v0.2"), KMessageBox::Notify);
}

void ModuleDisplaydlg::receivedOutput(KProcess *, char buffer[], int length)
{
  bufout.append(QCString(buffer, length + 1));
  displayData();
}

void ModuleDisplaydlg::displayData()
{
  QString copybuf = bufout;
  QTextStream rd(&bufout, IO_ReadOnly);
  QString readl;
  int rowCount = -1, number = -1;
  readl = rd.readLine();
  while (!rd.atEnd() ) {
     readl = rd.readLine();
     ++number;
  }
  table1->setNumRows(number);
  QTextStream rdf(&copybuf, IO_ReadOnly);
  readl = rdf.readLine();	//Skip the first row (the header of du command)
  while (!rdf.atEnd() ) {
     	   readl = rdf.readLine();
     	   ++rowCount;
     	   QTableItem* tblitem1 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 0, 0, QString::SectionSkipEmpty));
     	   table1->setItem(rowCount, 0, tblitem1);
      	   QTableItem* tblitem2 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 1, 1, QString::SectionSkipEmpty));
	   table1->setItem(rowCount, 1, tblitem2);
	   QTableItem* tblitem3 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 2, 2, QString::SectionSkipEmpty));
	   table1->setItem(rowCount, 2, tblitem3);
	   QTableItem* tblitem4 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 3, 0xffffffff, QString::SectionSkipEmpty));
	   table1->setItem(rowCount, 3, tblitem4);
  }
}

void ModuleDisplaydlg::doSortColumn(int which)
{
  table1->sortColumn(which, TRUE, TRUE);
}


#include "modldispdlg.moc"
