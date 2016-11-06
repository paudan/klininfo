/***************************************************************************
                          partitiondlg.cpp  -  description
                             -------------------
    begin                : Lie 10 20:15:39 2004
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

#include "partitiondlg.h"


#include <qvariant.h>
#include <qlabel.h>
#include <kcombobox.h>
#include <qtextbrowser.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <kprocess.h>
#include <kmessagebox.h>

/*
 *  Constructs a PartitionDispDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
PartitionDispDlg::PartitionDispDlg( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "PartitionDispDlg" );
    PartitionDispDlgLayout = new QGridLayout( this, 1, 1, 11, 6, "PartitionDispDlgLayout"); 

    dlg_title = new QLabel( this, "dlg_title" );

    PartitionDispDlgLayout->addWidget( dlg_title, 0, 0 );

    textLabel2 = new QLabel( this, "textLabel2" );

    PartitionDispDlgLayout->addMultiCellWidget( textLabel2, 3, 3, 0, 1 );

    kComboBox1 = new KComboBox( FALSE, this, "kComboBox1" );

    PartitionDispDlgLayout->addWidget( kComboBox1, 0, 1 );

    textBrowser1 = new QTextBrowser( this, "textBrowser1" );

    PartitionDispDlgLayout->addMultiCellWidget( textBrowser1, 4, 4, 0, 1 );

    textBrowser2 = new QTextBrowser( this, "textBrowser2" );

    PartitionDispDlgLayout->addMultiCellWidget( textBrowser2, 1, 1, 0, 1 );
    QSpacerItem* spacer = new QSpacerItem( 20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed );
    PartitionDispDlgLayout->addItem( spacer, 2, 0 );
    languageChange();
    resize( QSize(600, 482).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( kComboBox1, SIGNAL( activated(int) ), this, SLOT( typeSelected(int) ) );

    buffer = buffer_hdparm = "";
    textBrowser2->clear();
    textBrowser1->clear();
    run_hdparm();

    typeSelected(0);
}

/*
 *  Destroys the object and frees any allocated resources
 */
PartitionDispDlg::~PartitionDispDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void PartitionDispDlg::languageChange()
{
    setCaption( tr( "Partition Display Dialog" ) );
    dlg_title->setText( tr( "Select partition table display style:" ) );
    textLabel2->setText( tr( "Hard drive information:" ) );
    QToolTip::add( textLabel2, tr( "Displays HD information " ) );
    kComboBox1->clear();
    kComboBox1->insertItem( tr( "With sizes in cylinders (fdisk)" ) );
    kComboBox1->insertItem( tr( "With sizes in sectors (fdisk)" ) );
    kComboBox1->insertItem( tr( "In sector order format (cfdisk)" ) );
    kComboBox1->insertItem( tr( "In raw format (cfdisk)" ) );
    kComboBox1->insertItem( tr( "Raw format (what's exactly on the disk)" ) );
    QToolTip::add( kComboBox1, tr( "Select the way you want to see the partitions displayed." ) );
    QWhatsThis::add( kComboBox1, tr( "This allows you to select the way for your partition display" ) );
    QToolTip::add( textBrowser1, QString::null );
    QWhatsThis::add( textBrowser1, tr( "This is where hard disk information is being displayed" ) );
    QToolTip::add( textBrowser2, QString::null );
    QWhatsThis::add( textBrowser2, tr( "Displays your system's partition information in the way you want" ) );
}

void PartitionDispDlg::typeSelected(int type_id)
{
   textBrowser2->clear();
   if (type_id == 0 ) 		runCommand(FDISK_CMD, FDISK_ARG1, NULL);
    else if (type_id == 1)	runCommand(FDISK_CMD, FDISK_ARG1, FDISK_ARG2);
    else if (type_id == 2)	runCommand(CFDISK_CMD, CFDISK_ARGPRINT, CFDISK_ARGSECT);
    else if (type_id == 3)	runCommand(CFDISK_CMD, CFDISK_ARGPRINT, CFDISK_ARGTRAW);
    else if (type_id == 4)	runCommand(CFDISK_CMD, CFDISK_ARGPRINT, CFDISK_ARGRAW);
}

void PartitionDispDlg::runCommand(const char *cname, const char *carg1, const char *carg2)
{
  KProcess *process = new KProcess();
  process->clearArguments();
  (*process) << cname << carg1 << carg2;
  connect(process, SIGNAL(receivedStdout(KProcess*, char*, int) ), this, SLOT(receivedOutput(KProcess *, char *, int)) );
  connect(process, SIGNAL(receivedStderr(KProcess*, char*, int) ), this, SLOT(receivedOutput(KProcess *, char *, int)) );
  connect(process, SIGNAL(processExited(KProcess*, char*, int) ), this, SLOT(processFinished(KProcess *, char *, int)) );
  if ( !process->start(KProcess::NotifyOnExit, KProcess::AllOutput) )
        KMessageBox::error( this, tr("Fatal error. Could not retrieve information"), QString("KLinInfo v0.2"), KMessageBox::Notify);
}

void PartitionDispDlg::run_hdparm()
{
  KProcess *process = new KProcess();
  process->clearArguments();
  (*process) << HDPARM_CMD << HDPARM_ARGINFO1 << HDPARM_ARGINFO2;
  process->setUseShell(true, "/bin/bash");
  connect(process, SIGNAL(receivedStdout(KProcess*, char*, int) ), this, SLOT(receivedOutputHDP(KProcess *, char *, int)) );
  connect(process, SIGNAL(receivedStderr(KProcess*, char*, int) ), this, SLOT(receivedOutputHDP(KProcess *, char *, int)) );
  connect(process, SIGNAL(processExited(KProcess*, char*, int) ), this, SLOT(processFinished(KProcess *, char *, int)) );
  if ( !process->start(KProcess::NotifyOnExit, KProcess::AllOutput) )
        KMessageBox::error( this, tr("Fatal error. Could not retrieve information"), QString("KLinInfo v0.2"), KMessageBox::Notify);
}

void PartitionDispDlg::receivedOutput(KProcess *, char output[], int length)
{
  buffer.append(QCString(output, length + 1));
  textBrowser2->setText(textBrowser2->text() + QString(output) + "\n");
}

void PartitionDispDlg::receivedOutputHDP(KProcess *, char output[], int length)
{
  buffer_hdparm.append(QCString(output, length + 1));
  textBrowser1->setText(textBrowser1->text() + QString(output) + "\n");
}

void PartitionDispDlg::processFinished(KProcess *, char *, int )
{
  buffer = "";
  buffer_hdparm = "";
}

#include "partitiondlg.moc"
