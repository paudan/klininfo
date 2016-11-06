/***************************************************************************
                          klininfodialog.h  -  description
                             -------------------
    begin                : Kt Lie 15 17:11:05 2004
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

#include "config_font.h"


#include <qvariant.h>
#include <kfontdialog.h>
#include <qlabel.h>
#include <kcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a FontConfig as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
FontConfig::FontConfig( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "FontConfig" );
    FontConfigLayout = new QGridLayout( this, 1, 1, 11, 6, "FontConfigLayout"); 

    textLabel1 = new QLabel( this, "textLabel1" );

    FontConfigLayout->addWidget( textLabel1, 0, 0 );

    kFontDialog = new KFontChooser( this, "kFontDialog", false, QStringList(), true);

    FontConfigLayout->addMultiCellWidget( kFontDialog, 1, 1, 0, 2 );
    QSpacerItem* spacer = new QSpacerItem( 300, 15, QSizePolicy::Fixed, QSizePolicy::Minimum );
    FontConfigLayout->addItem( spacer, 0, 2 );

    kComboBox1 = new KComboBox( FALSE, this, "kComboBox1" );

    FontConfigLayout->addWidget( kComboBox1, 0, 1 );
    languageChange();
    resize( QSize(600, 482).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect(kComboBox1, SIGNAL( activated(int ) ), this, SLOT( saveFontInfo() ) );
    connect(kFontDialog, SIGNAL( fontSelected(const QFont &) ), this, SLOT(FontChange() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
FontConfig::~FontConfig()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FontConfig::languageChange()
{
    setCaption( tr( "Form1" ) );
    textLabel1->setText( tr( "Change font in:" ) );
    kComboBox1->clear();
    kComboBox1->insertItem( tr( "Text dialogs" ) );
    kComboBox1->insertItem( tr( "Description dialogs" ) );
    kComboBox1->insertItem( tr( "Tables" ) );
    kComboBox1->insertItem( tr( "Listboxes" ) );
}

void FontConfig::saveFontInfo()
{
  fsettings[curTypeWidget] = curWidgetFont;
  const QFont curFont = fsettings[kComboBox1->currentItem()];
  kFontDialog->setFont(curFont);
}

void FontConfig::FontChange()
{
  curTypeWidget = kComboBox1->currentItem();
  curWidgetFont = kFontDialog->font();
}

#include "config_font.moc"
