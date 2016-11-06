/***************************************************************************
                          finputdlg.cpp  -  description
                             -------------------
    begin                : Tr Lie 7 14:21:10 2004
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

#include "finputdlg.h"


#include <qvariant.h>
#include <qlabel.h>
#include <qtoolbutton.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qfiledialog.h>
#include <qfile.h>
#include <kmessagebox.h>

/*
 *  Constructs a FileInputDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
FileInputDlg::FileInputDlg( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "FileInputDlg" );
    setIcon( QPixmap("icons/edit.png") );
    setSizeGripEnabled( TRUE );
    FileInputDlgLayout = new QGridLayout( this, 1, 1, 11, 6, "FileInputDlgLayout"); 

    textLabel1 = new QLabel( this, "textLabel1" );

    FileInputDlgLayout->addWidget( textLabel1, 0, 0 );

    toolButton1 = new QToolButton( this, "toolButton1" );
    toolButton1->setIconSet( QIconSet( QPixmap("icons/folder_yellow_open.png") ) );

    FileInputDlgLayout->addWidget( toolButton1, 1, 1 );

    lineEdit1 = new QLineEdit( this, "lineEdit1" );

    FileInputDlgLayout->addWidget( lineEdit1, 1, 0 );

    textLabel2 = new QLabel( this, "textLabel2" );

    FileInputDlgLayout->addWidget( textLabel2, 2, 0 );

    textEdit1 = new QTextEdit( this, "textEdit1" );
    textEdit1->setTextFormat( QTextEdit::PlainText );

    FileInputDlgLayout->addMultiCellWidget( textEdit1, 3, 3, 0, 1 );

    Layout1 = new QHBoxLayout( 0, 0, 6, "Layout1"); 

    buttonHelp = new QPushButton( this, "buttonHelp" );
    buttonHelp->setAutoDefault( TRUE );
    Layout1->addWidget( buttonHelp );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( spacer );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );

    FileInputDlgLayout->addMultiCellLayout( Layout1, 4, 4, 0, 1 );
    languageChange();
    resize( QSize(511, 284).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( toolButton1, SIGNAL( clicked() ), this, SLOT( setFilename() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
FileInputDlg::~FileInputDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FileInputDlg::languageChange()
{
    setCaption( tr( "Change file information" ) );
    textLabel1->setText( tr( "File name:" ) );
    toolButton1->setText( QString::null );
    textLabel2->setText( tr( "File description:" ) );
    buttonHelp->setText( tr( "&Help" ) );
    buttonHelp->setAccel( QKeySequence( tr( "F1" ) ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
}

void FileInputDlg::setFilename()
{
  QString s( QFileDialog::getOpenFileName( QString::null, tr("All files (*)"), this) );
  if (s.isEmpty() )
     KMessageBox::error(this, tr("File name field is empty"), tr("Error setting filename") );
  else lineEdit1->setText(s);
}

void FileInputDlg::accept()
{
  QFile f(lineEdit1->text());
  if (!f.exists()) KMessageBox::error(this, tr("Error setting filename: file %1 does not exist").arg(lineEdit1->text()), tr("Error setting filename") );
  else {
    emit apply();
    hide();
  }
}

#include "finputdlg.moc"
