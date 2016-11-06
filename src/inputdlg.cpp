/***************************************************************************
                          inputdlg.cpp  -  description
                             -------------------
    begin                : Pr Lie 5 21:42:13 2004
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

#include "inputdlg.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

/*
 *  Constructs a InputDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
InputDlg::InputDlg( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "InputDlg" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth() ) );
    setIcon( QPixmap("icons/info.png") );
    setSizeGripEnabled( TRUE );
    InputDlgLayout = new QVBoxLayout( this, 11, 6, "InputDlgLayout");

    cmd_title = new QLabel( this, "cmd_title" );
    InputDlgLayout->addWidget( cmd_title );

    lineEdit1 = new QLineEdit( this, "lineEdit1" );
    InputDlgLayout->addWidget( lineEdit1 );

    textLabel2 = new QLabel( this, "textLabel2" );
    InputDlgLayout->addWidget( textLabel2 );

    textEdit1 = new QTextEdit( this, "textEdit1" );
    textEdit1->setTextFormat(Qt::PlainText);
    InputDlgLayout->addWidget( textEdit1 );

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
    InputDlgLayout->addLayout( Layout1 );
    languageChange();
    resize( QSize(511, 286).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
InputDlg::~InputDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void InputDlg::languageChange()
{
    setCaption( tr( "Information Input" ) );
    cmd_title->setText( tr( "Command name:" ) );
    textLabel2->setText( tr( "Description:" ) );
    buttonHelp->setText( tr( "&Help" ) );
    buttonHelp->setAccel( QKeySequence( tr( "F1" ) ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
}

#include "inputdlg.moc"
