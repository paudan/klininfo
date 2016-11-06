/***************************************************************************
                          config_files.cpp  -  description
                             -------------------
    begin                : Kt Lie 15 17:11:31 2004
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

#include "config_files.h"

#include <qvariant.h>
#include <qlabel.h>
#include <klineedit.h>
#include <qtoolbutton.h>
#include <qpushbutton.h>
#include <qfiledialog.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

#include <kprocess.h>
#include <kmessagebox.h>

/*
 *  Constructs a FilesConfig as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
FilesConfig::FilesConfig( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "FilesConfig" );
    FilesConfigLayout = new QGridLayout( this, 1, 1, 11, 6, "FilesConfigLayout"); 

    textLabel2 = new QLabel( this, "textLabel2" );
    QFont textLabel2_font(  textLabel2->font() );
    textLabel2_font.setPointSize( 13 );
    textLabel2_font.setBold( TRUE );
    textLabel2->setFont( textLabel2_font ); 
    textLabel2->setAlignment( int( QLabel::AlignCenter ) );

    FilesConfigLayout->addMultiCellWidget( textLabel2, 0, 0, 0, 2 );

    textLabel1 = new QLabel( this, "textLabel1" );

    FilesConfigLayout->addWidget( textLabel1, 1, 0 );

    kLineEdit1 = new KLineEdit( this, "kLineEdit1" );

    FilesConfigLayout->addWidget( kLineEdit1, 2, 0 );

    toolButton1 = new QToolButton( this, "toolButton1" );
    toolButton1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)1, 0, 0, toolButton1->sizePolicy().hasHeightForWidth() ) );
    toolButton1->setMinimumSize( QSize( 20, 20 ) );

    FilesConfigLayout->addWidget( toolButton1, 2, 1 );

    pushButton1 = new QPushButton( this, "pushButton1" );

    FilesConfigLayout->addWidget( pushButton1, 2, 2 );

    textLabel3 = new QLabel( this, "textLabel3" );
    textLabel3->setAlignment( int( QLabel::AlignVCenter ) );

    FilesConfigLayout->addMultiCellWidget( textLabel3, 3, 3, 0, 1 );

    kLineEdit2 = new KLineEdit( this, "kLineEdit2" );

    FilesConfigLayout->addWidget( kLineEdit2, 4, 0 );

    textLabel4 = new QLabel( this, "textLabel4" );
    textLabel4->setAlignment( int( QLabel::AlignVCenter ) );

    FilesConfigLayout->addWidget( textLabel4, 5, 0 );

    kLineEdit3 = new KLineEdit( this, "kLineEdit3" );

    FilesConfigLayout->addWidget( kLineEdit3, 6, 0 );

    toolButton3 = new QToolButton( this, "toolButton3" );
    toolButton3->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)1, 0, 0, toolButton3->sizePolicy().hasHeightForWidth() ) );
    toolButton3->setMinimumSize( QSize( 20, 20 ) );

    FilesConfigLayout->addWidget( toolButton3, 6, 1 );

    pushButton3 = new QPushButton( this, "pushButton3" );

    FilesConfigLayout->addWidget( pushButton3, 6, 2 );

    textLabel1_2 = new QLabel( this, "textLabel1_2" );

    FilesConfigLayout->addWidget( textLabel1_2, 7, 0 );

    kLineEdit4 = new KLineEdit( this, "kLineEdit4" );

    FilesConfigLayout->addWidget( kLineEdit4, 8, 0 );

    toolButton4 = new QToolButton( this, "toolButton4" );

    FilesConfigLayout->addWidget( toolButton4, 8, 1 );

    pushButton4 = new QPushButton( this, "pushButton4" );

    FilesConfigLayout->addWidget( pushButton4, 8, 2 );

    pushButton2 = new QPushButton( this, "pushButton2" );

    FilesConfigLayout->addWidget( pushButton2, 4, 2 );

    toolButton2 = new QToolButton( this, "toolButton2" );
    toolButton2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)1, 0, 0, toolButton2->sizePolicy().hasHeightForWidth() ) );
    toolButton2->setMinimumSize( QSize( 20, 20 ) );

    FilesConfigLayout->addWidget( toolButton2, 4, 1 );
    languageChange();
    resize( QSize(418, 288).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( toolButton1, SIGNAL( clicked() ), this, SLOT( commandButton_clicked() ) );
    connect( toolButton2, SIGNAL( clicked() ), this, SLOT( systemButton_clicked() ) );
    connect( toolButton3, SIGNAL( clicked() ), this, SLOT( logButton_clicked() ) );
    connect( toolButton4, SIGNAL( clicked() ), this, SLOT( varsionButton_clicked() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
FilesConfig::~FilesConfig()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FilesConfig::languageChange()
{
    setCaption( tr( "Form1" ) );
    QToolTip::add( this, tr( "You can select to use your own KLinInfo description files here" ) );
    QWhatsThis::add( this, tr( "This dialog gives ability to select files with descriptions, used by System files, Log files and Custom commands dialogs. You can also edit them here " ) );
    textLabel2->setText( tr( "Source files " ) );
    textLabel1->setText( tr( "Command description file:" ) );
    QWhatsThis::add( kLineEdit1, tr( "The name and full path of command description file" ) );
    toolButton1->setText( tr( "..." ) );
    QToolTip::add( toolButton1, tr( "Select command description file here" ) );
    QWhatsThis::add( toolButton1, tr( "Select command description file here" ) );
    pushButton1->setText( tr( "Edit file.." ) );
    QToolTip::add( pushButton1, tr( "Edit your selected file here (although it's not recommended to edit it by hand)" ) );
    QWhatsThis::add( pushButton1, tr( "Allows you to edit command description file" ) );
    textLabel3->setText( tr( "<i>System files</i> description file:" ) );
    QWhatsThis::add( kLineEdit2, tr( "The name and full path  of <i>System files</i> description file" ) );
    textLabel4->setText( tr( "<i>Log files</i> description file:" ) );
    QWhatsThis::add( kLineEdit3, tr( "The name and full path of <i>Log files</i> description file" ) );
    toolButton3->setText( tr( "..." ) );
    pushButton3->setText( tr( "Edit file..." ) );
    textLabel1_2->setText( tr( "Program version file:" ) );
    QWhatsThis::add( kLineEdit4, tr( "The name and full path of program version file" ) );
    toolButton4->setText( tr( "..." ) );
    QWhatsThis::add( toolButton4, tr( "Select your own  version file" ) );
    pushButton4->setText( tr( "Edit file..." ) );
    QToolTip::add( pushButton4, tr( "Allows you to edit your program version s file directly. This easy, you just need to write in the command that gives you the line containing the version of the program" ) );
    QWhatsThis::add( pushButton4, tr( "Edit your version file directly" ) );
    pushButton2->setText( tr( "Edit file..." ) );
    toolButton2->setText( tr( "..." ) );
    QToolTip::add( toolButton2, tr( "Select System file description file here" ) );
    QWhatsThis::add( toolButton2, tr( "Select System file description file here" ) );
}

void FilesConfig::commandButton_clicked()
{
    QString s( QFileDialog::getOpenFileName(QString::null, tr("KLinInfo files(*.kl);;All files(*.*)") ) );
    if (s.isEmpty() ) return;
    kLineEdit1->setText(s);
}

void FilesConfig::systemButton_clicked()
{
    QString s( QFileDialog::getOpenFileName(QString::null, tr("KLinInfo files(*.kl);;All files(*.*)") ) );
    if (s.isEmpty() ) return;
    kLineEdit2->setText(s);
}

void FilesConfig::logButton_clicked()
{
    QString s( QFileDialog::getOpenFileName(QString::null, tr("KLinInfo files(*.kl);;All files(*.*)") ) );
    if (s.isEmpty() ) return;
    kLineEdit3->setText(s);
}

void FilesConfig::varsionButton_clicked()
{
    QString s( QFileDialog::getOpenFileName(QString::null, tr("KLinInfo files(*.kl);;All files(*.*)") ) );
    if (s.isEmpty() ) return;
    kLineEdit4->setText(s);
}

void FilesConfig::editFile(QString editor, QString filename)
{
    KProcess *edproc = new KProcess();
    edproc->clearArguments();
    *edproc << editor << filename;
    if (!edproc->start())
       KMessageBox::error(this, tr("Error executing %1: file %2 could not be openened").arg(editor, filename ), QString("Error opening file"), KMessageBox::Notify);
}

#include "config_files.moc"
