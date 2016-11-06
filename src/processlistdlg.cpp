/***************************************************************************
                          processlistdlg.cpp  -  description
                             -------------------
    begin                : Pn Lie 2 16:38:45 2004
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

#include "processlistdlg.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qtable.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qregexp.h>

#include <stdlib.h>
#include <string.h>


/*
 *  Constructs a ProcessListDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
ProcessListDlg::ProcessListDlg( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "ProcessListDlg" );
    ProcessListDlgLayout = new QGridLayout( this, 1, 1, 11, 6, "ProcessListDlgLayout");

    groupBox1 = new QButtonGroup( this, "groupBox1" );
    groupBox1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, groupBox1->sizePolicy().hasHeightForWidth() ) );
    groupBox1->setColumnLayout(0, Qt::Vertical );
    groupBox1->layout()->setSpacing( 6 );
    groupBox1->layout()->setMargin( 11 );
    groupBox1->setExclusive(true);
    groupBox1Layout = new QGridLayout( groupBox1->layout() );
    groupBox1Layout->setAlignment( Qt::AlignTop );

    radioButton2 = new QRadioButton( groupBox1, "radioButton2" );

    groupBox1Layout->addWidget( radioButton2, 1, 0 );

    radioButton1 = new QRadioButton( groupBox1, "radioButton1" );

    groupBox1Layout->addWidget( radioButton1, 0, 0 );

    radioButton4 = new QRadioButton( groupBox1, "radioButton4" );

    groupBox1Layout->addWidget( radioButton4, 1, 1 );

    radioButton3 = new QRadioButton( groupBox1, "radioButton3" );

    groupBox1Layout->addWidget( radioButton3, 0, 1 );

    ProcessListDlgLayout->addMultiCellWidget( groupBox1, 2, 4, 2, 3 );

    table1 = new QTable( this, "table1" );
    table1->setLeftMargin( 0 );
    table1->verticalHeader()->hide();
    table1->horizontalHeader()->resizeSection(3, int (table1->width() / 3) );

    ProcessListDlgLayout->addMultiCellWidget( table1, 1, 1, 0, 3 );

    checkBox1 = new QCheckBox( this, "checkBox1" );

    ProcessListDlgLayout->addMultiCellWidget( checkBox1, 2, 2, 0, 1 );

    checkBox2 = new QCheckBox( this, "checkBox2" );

    ProcessListDlgLayout->addMultiCellWidget( checkBox2, 3, 3, 0, 1 );

    textLabel1 = new QLabel( this, "textLabel1" );

    ProcessListDlgLayout->addWidget( textLabel1, 0, 0 );

    refreshButton1 = new QPushButton( this, "refreshButton1" );

    ProcessListDlgLayout->addWidget( refreshButton1, 0, 3 );
    QSpacerItem* spacer = new QSpacerItem( 180, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    ProcessListDlgLayout->addMultiCell( spacer, 0, 0, 1, 2 );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed );
    ProcessListDlgLayout->addItem( spacer_2, 4, 0 );
    languageChange();
    resize( QSize(604, 514).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    connect( radioButton1, SIGNAL(clicked()), this, SLOT(showRegisters_Checked() ) );
    connect( radioButton2, SIGNAL(clicked()), this, SLOT(showUserOriented_Checked() ) );
    connect( radioButton3, SIGNAL(clicked()), this, SLOT(showSignals_Checked() ) );
    connect( radioButton4, SIGNAL(clicked()), this, SLOT(showNormal_Checked() ) );
    connect( refreshButton1, SIGNAL(clicked()), this, SLOT(refresh() ) );
    connect(table1->horizontalHeader(), SIGNAL(clicked(int ) ), this, SLOT(doSortColumn(int ) ) );

    showNormal_Checked();
}

/*
 *  Destroys the object and frees any allocated resources
 */
ProcessListDlg::~ProcessListDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ProcessListDlg::languageChange()
{
    setCaption( tr( "Process Display Dialog" ) );
    groupBox1->setTitle( tr( "Output format:" ) );
    radioButton2->setText( tr( "User-oriented" ) );
    QToolTip::add( radioButton2, tr( "Also displays information of memory and CPU usage percentage" ) );
    radioButton1->setText( tr( "As registers" ) );
    QToolTip::add( radioButton1, tr( "Displays registers, used by processes" ) );
    radioButton4->setText( tr( "Normal" ) );
    radioButton3->setText( tr( "Signal" ) );
    QToolTip::add( radioButton3, tr( "Displays output as signals" ) );
    checkBox1->setText( tr( "Show only processes, run by current user" ) );
    checkBox2->setText( tr( "Show only running processes" ) );
    QToolTip::add( checkBox2, QString::null );
    textLabel1->setText( tr( "Process, currently run on this machine:" ) );
    refreshButton1->setText( tr( "Refresh list" ) );
    QToolTip::add( refreshButton1, tr( "Refresh process information" ) );
}

void ProcessListDlg::showNormal_Checked()
{
  if (checkBox1->isChecked() == false && checkBox2->isChecked() == false)
     displayNormal("ps -A -f -l -w >> /tmp/process");
  else if (checkBox1->isChecked() == true && checkBox2->isChecked() == false)
     displayNormal("ps -G `echo $USER`-A -f -l -w >> /tmp/process");
  else if (checkBox1->isChecked() == false && checkBox2->isChecked() == true)
     displayNormal("ps r -f -l -w >> /tmp/process");
  else if (checkBox1->isChecked() == true && checkBox2->isChecked() == true)
     displayNormal("ps r -f -l -w -G `echo $USER`>> /tmp/process");
}

void ProcessListDlg::showUserOriented_Checked()
{
  if (checkBox1->isChecked() == false && checkBox2->isChecked() == false)
     displayUserOriented("ps -A u -w >> /tmp/process");
  else if (checkBox1->isChecked() == true && checkBox2->isChecked() == false)
     displayUserOriented("ps -G `echo $USER`-A u -w >> /tmp/process");
  else if (checkBox1->isChecked() == false && checkBox2->isChecked() == true)
     displayUserOriented("ps r u -w >> /tmp/process");
  else if (checkBox1->isChecked() == true && checkBox2->isChecked() == true)
     displayUserOriented("ps r u -w -G `echo $USER`>> /tmp/process");
}

void ProcessListDlg::showSignals_Checked()
{
  if (checkBox1->isChecked() == false && checkBox2->isChecked() == false)
     displaySignals("ps -eo user,uid,pid,pending,blocked,ignored,caught,stime,tty,time,command -w >> /tmp/process");
  else if (checkBox1->isChecked() == true && checkBox2->isChecked() == false)
     displaySignals("ps -G `echo $USER`-eo user,uid,pid,pending,blocked,ignored,caught,stime,tty,time,command -w >> /tmp/process");
  else if (checkBox1->isChecked() == false && checkBox2->isChecked() == true)
     displaySignals("ps r -o user,uid,pid,pending,blocked,ignored,caught,stime,tty,time,command -w >> /tmp/process");
  else if (checkBox1->isChecked() == true && checkBox2->isChecked() == true)
     displaySignals("ps r -o user,uid,pid,pending,blocked,ignored,caught,stime,tty,time,command -w -G `echo $USER`>> /tmp/process");
}

void ProcessListDlg::showRegisters_Checked()
{
  if (checkBox1->isChecked() == false && checkBox2->isChecked() == false)
     displayRegisters("ps -eo user,pid,stackp,esp,eip,tmout,alarm,stat,tty,time,command -w >> /tmp/process");
  else if (checkBox1->isChecked() == true && checkBox2->isChecked() == false)
     displayRegisters("ps -eo user,pid,stackp,esp,eip,tmout,alarm,stat,tty,time,command -w -G `echo $USER` >> /tmp/process");
  else if (checkBox1->isChecked() == false && checkBox2->isChecked() == true)
     displayRegisters("ps r -o user,pid,stackp,esp,eip,tmout,alarm,stat,tty,time,command -w >> /tmp/process");
  else if (checkBox1->isChecked() == true && checkBox2->isChecked() == true)
     displayRegisters("ps r -o user,pid,stackp,esp,eip,tmout,alarm,stat,tty,time,command -w -G `echo $USER` >> /tmp/process");
}

void ProcessListDlg::refresh()
{
  if (groupBox1->selectedId() == groupBox1->id(radioButton1) ) showRegisters_Checked();
  else if (groupBox1->selectedId() == groupBox1->id(radioButton2)) showUserOriented_Checked();
  else if (groupBox1->selectedId() == groupBox1->id(radioButton3)) showSignals_Checked();
  else if (groupBox1->selectedId() == groupBox1->id(radioButton4)) showNormal_Checked();
}

void ProcessListDlg::displayNormal(char *paramline)
{
    table1->setNumCols( 12 );
    table1->horizontalHeader()->resizeSection(0, 20 );
    table1->horizontalHeader()->resizeSection(1, 20 );
    table1->horizontalHeader()->resizeSection(2, 40 );
    table1->horizontalHeader()->resizeSection(3, 40 );
    table1->horizontalHeader()->resizeSection(4, 40 );
    table1->horizontalHeader()->resizeSection(5, 40 );
    table1->horizontalHeader()->resizeSection(6, 70 );
    table1->horizontalHeader()->resizeSection(7, 70 );
    table1->horizontalHeader()->resizeSection(8, 40 );
    table1->horizontalHeader()->resizeSection(9, 100 );
    table1->horizontalHeader()->resizeSection(10, 100 );
    table1->horizontalHeader()->resizeSection(11, 300 );
    table1->horizontalHeader()->setLabel( 0, tr("Flag") );
    table1->horizontalHeader()->setLabel( 1, tr("State") );
    table1->horizontalHeader()->setLabel( 2, tr("User ID") );
    table1->horizontalHeader()->setLabel( 3, tr("Process ID") );
    table1->horizontalHeader()->setLabel( 4, tr("PPID") );
    table1->horizontalHeader()->setLabel( 5, tr("Priority") );
    table1->horizontalHeader()->setLabel( 6, tr("Used memory") );
    table1->horizontalHeader()->setLabel( 7, tr("WCHAN") );
    table1->horizontalHeader()->setLabel( 8, tr("Start time") );
    table1->horizontalHeader()->setLabel( 9, tr("TTY") );
    table1->horizontalHeader()->setLabel( 10, tr("Time run") );
    table1->horizontalHeader()->setLabel( 11, tr("Command (process)") );

    system(paramline);
    table1->setNumRows( lineCount( QString("/tmp/process") ) );

    QFile tmp("/tmp/process");
    if (tmp.open(IO_ReadOnly) ) {
        QTextStream rd(&tmp);
        QString readl;
        int rowCount = -1;
	readl = rd.readLine();
	while (!tmp.atEnd() ) {
	   readl = rd.readLine();
           ++rowCount;
	   QTableItem* tblitem1 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 0, 0, QString::SectionSkipEmpty));
           table1->setItem(rowCount, 0, tblitem1);
	   QTableItem* tblitem2 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 1, 1, QString::SectionSkipEmpty));
	   table1->setItem(rowCount, 1, tblitem2);
	   QTableItem* tblitem3 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 2, 2, QString::SectionSkipEmpty));
	   table1->setItem(rowCount, 2, tblitem3);
	   QTableItem* tblitem4 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 3, 3, QString::SectionSkipEmpty));
	   table1->setItem(rowCount, 3, tblitem4);
	   QTableItem* tblitem5 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 4, 4, QString::SectionSkipEmpty));
           table1->setItem(rowCount, 4, tblitem5);
	   QTableItem* tblitem6 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 6, 6, QString::SectionSkipEmpty));
	   table1->setItem(rowCount, 5, tblitem6);
	   QTableItem* tblitem7 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 9, 9, QString::SectionSkipEmpty));
	   table1->setItem(rowCount, 6, tblitem7);
	   QTableItem* tblitem8 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 10, 10, QString::SectionSkipEmpty));
	   table1->setItem(rowCount, 7, tblitem8);
	   QTableItem* tblitem9 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 11, 11, QString::SectionSkipEmpty));
	   table1->setItem(rowCount, 8, tblitem9);
	   QTableItem* tblitem10 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 12, 12, QString::SectionSkipEmpty));
	   table1->setItem(rowCount, 9, tblitem10);
	   QTableItem* tblitem11 = new QTableItem(table1, QTableItem::Never, readl.section(" ", 13, 13, QString::SectionSkipEmpty));
	   table1->setItem(rowCount, 10, tblitem11);
	   QTableItem* tblitem12 = new QTableItem(table1, QTableItem::Never, readl.section(":", -1, 0xffffffff).section(" ", 1));
	   table1->setItem(rowCount, 11, tblitem12);
       }
       tmp.close();
       tmp.remove();
    }
}

void ProcessListDlg::displayUserOriented(char *paramline)
{
    table1->setNumCols( 11 );
    table1->horizontalHeader()->resizeSection(0, 70 );
    table1->horizontalHeader()->resizeSection(1, 70 );
    table1->horizontalHeader()->resizeSection(2, 70 );
    table1->horizontalHeader()->resizeSection(3, 70 );
    table1->horizontalHeader()->resizeSection(4, 70 );
    table1->horizontalHeader()->resizeSection(5, 70 );
    table1->horizontalHeader()->resizeSection(6, 70 );
    table1->horizontalHeader()->resizeSection(7, 20 );
    table1->horizontalHeader()->resizeSection(8, 40 );
    table1->horizontalHeader()->resizeSection(9, 70 );
    table1->horizontalHeader()->resizeSection(10, 300 );
    table1->horizontalHeader()->setLabel( 0, tr("User ID") );
    table1->horizontalHeader()->setLabel( 1, tr("Process ID") );
    table1->horizontalHeader()->setLabel( 2, tr("CPU usage, %") );
    table1->horizontalHeader()->setLabel( 3, tr("Memory usage, %") );
    table1->horizontalHeader()->setLabel( 4, tr("VSZ") );
    table1->horizontalHeader()->setLabel( 5, tr("RSS") );
    table1->horizontalHeader()->setLabel( 6, tr("TTY") );
    table1->horizontalHeader()->setLabel( 7, tr("STAT") );
    table1->horizontalHeader()->setLabel( 8, tr("Start time") );
    table1->horizontalHeader()->setLabel( 9, tr("Time run") );
    table1->horizontalHeader()->setLabel( 10, tr("Command (process)") );

    system(paramline);
    table1->setNumRows( lineCount( QString("/tmp/process") ) );

    readInfo();
}

void ProcessListDlg::displaySignals(char *paramline)
{
    table1->setNumCols( 11 );
    table1->horizontalHeader()->resizeSection(0, 70 );
    table1->horizontalHeader()->resizeSection(1, 40 );
    table1->horizontalHeader()->resizeSection(2, 60 );
    table1->horizontalHeader()->resizeSection(3, 150 );
    table1->horizontalHeader()->resizeSection(4, 150 );
    table1->horizontalHeader()->resizeSection(5, 150 );
    table1->horizontalHeader()->resizeSection(6, 150 );
    table1->horizontalHeader()->resizeSection(7, 50 );
    table1->horizontalHeader()->resizeSection(8, 40 );
    table1->horizontalHeader()->resizeSection(9, 70 );
    table1->horizontalHeader()->resizeSection(10, 300 );
    table1->horizontalHeader()->setLabel( 0, tr("User") );
    table1->horizontalHeader()->setLabel( 1, tr("User ID") );
    table1->horizontalHeader()->setLabel( 2, tr("Process ID") );
    table1->horizontalHeader()->setLabel( 3, tr("Pending") );
    table1->horizontalHeader()->setLabel( 4, tr("Blocked") );
    table1->horizontalHeader()->setLabel( 5, tr("Ignored") );
    table1->horizontalHeader()->setLabel( 6, tr("Caught") );
    table1->horizontalHeader()->setLabel( 7, tr("Start time") );
    table1->horizontalHeader()->setLabel( 8, tr("TTY") );
    table1->horizontalHeader()->setLabel( 9, tr("Time run") );
    table1->horizontalHeader()->setLabel( 10, tr("Command (process)") );

    system(paramline);
    table1->setNumRows( lineCount( QString("/tmp/process") ) );

    readInfo();
}

void ProcessListDlg::displayRegisters(char *paramline)
{
    table1->setNumCols( 11 );
    table1->horizontalHeader()->resizeSection(0, 70 );
    table1->horizontalHeader()->resizeSection(1, 40 );
    table1->horizontalHeader()->resizeSection(2, 60 );
    table1->horizontalHeader()->resizeSection(3, 100 );
    table1->horizontalHeader()->resizeSection(4, 100 );
    table1->horizontalHeader()->resizeSection(5, 100 );
    table1->horizontalHeader()->resizeSection(6, 100 );
    table1->horizontalHeader()->resizeSection(7, 50 );
    table1->horizontalHeader()->resizeSection(8, 40 );
    table1->horizontalHeader()->resizeSection(9, 70 );
    table1->horizontalHeader()->resizeSection(10, 300 );
    table1->horizontalHeader()->setLabel( 0, tr("User ID") );
    table1->horizontalHeader()->setLabel( 1, tr("Process ID") );
    table1->horizontalHeader()->setLabel( 2, tr("STACKP") );
    table1->horizontalHeader()->setLabel( 3, tr("ESP") );
    table1->horizontalHeader()->setLabel( 4, tr("EIP") );
    table1->horizontalHeader()->setLabel( 5, tr("Timeout") );
    table1->horizontalHeader()->setLabel( 6, tr("Alarm") );
    table1->horizontalHeader()->setLabel( 7, tr("STAT") );
    table1->horizontalHeader()->setLabel( 8, tr("TTY") );
    table1->horizontalHeader()->setLabel( 9, tr("Time run") );
    table1->horizontalHeader()->setLabel( 10, tr("Command (process)") );

    system(paramline);
    table1->setNumRows( lineCount( QString("/tmp/process") ) );

    readInfo();
}

int ProcessListDlg::lineCount(QString filename)
{
  int count = 0;
  QFile f(filename);
  if (!f.open(IO_ReadOnly) ) return 0;
  else {
     QTextStream rd(&f);
     QString tmp = rd.readLine();
     while (!f.atEnd() )
     {
       tmp = rd.readLine();
       count++;
     }
  }
  return count;
}

void ProcessListDlg::readInfo()
{
    QFile tmp("/tmp/process");
    if (tmp.open(IO_ReadOnly) ) {
        QTextStream rd(&tmp);
        QString readl;
        int rowCount = -1;
	readl = rd.readLine();
	while (!tmp.atEnd() ) {
	   readl = rd.readLine();
           ++rowCount;
           table1->setText(rowCount, 0, readl.section(" ", 0, 0, QString::SectionSkipEmpty));
	   table1->setText(rowCount, 1, readl.section(" ", 1, 1, QString::SectionSkipEmpty));
	   table1->setText(rowCount, 2, readl.section(" ", 2, 2, QString::SectionSkipEmpty));
	   table1->setText(rowCount, 3, readl.section(" ", 3, 3, QString::SectionSkipEmpty));
           table1->setText(rowCount, 4, readl.section(" ", 4, 4, QString::SectionSkipEmpty));
	   table1->setText(rowCount, 5, readl.section(" ", 5, 5, QString::SectionSkipEmpty));
	   table1->setText(rowCount, 6, readl.section(" ", 6, 6, QString::SectionSkipEmpty));
	   table1->setText(rowCount, 7, readl.section(" ", 7, 7, QString::SectionSkipEmpty));
	   table1->setText(rowCount, 8, readl.section(" ", 8, 8, QString::SectionSkipEmpty));
	   table1->setText(rowCount, 9, readl.section(" ", 9, 9, QString::SectionSkipEmpty));
	   table1->setText(rowCount, 10, readl.section(" ", 10, 10, QString::SectionSkipEmpty));
	   table1->setText(rowCount, 11, readl.section(":", -1, 0xffffffff).section(" ", 1));
       }
       tmp.close();
       tmp.remove();
    }
}

void ProcessListDlg::doSortColumn(int which)
{
  table1->sortColumn(which, TRUE, TRUE);
}

#include "processlistdlg.moc"


