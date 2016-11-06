
/****************************************************************************
** Form implementation generated from reading ui file '/home/Paulius/klininfo_v0.2/klininfo/src/config_misc.ui'
**
** Created: Št Lie 17 13:34:16 2004
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.2.1   edited May 19 14:22 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "config_misc.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <klineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a MiscConfig as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
MiscConfig::MiscConfig( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "MiscConfig" );
    MiscConfigLayout = new QGridLayout( this, 1, 1, 11, 6, "MiscConfigLayout"); 

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setMaximumSize( QSize( 32767, 20 ) );
    QFont textLabel1_font(  textLabel1->font() );
    textLabel1_font.setPointSize( 13 );
    textLabel1_font.setBold( TRUE );
    textLabel1->setFont( textLabel1_font ); 
    textLabel1->setAlignment( int( QLabel::AlignCenter ) );

    MiscConfigLayout->addMultiCellWidget( textLabel1, 0, 0, 0, 1 );

    checkBox1 = new QCheckBox( this, "checkBox1" );

    MiscConfigLayout->addWidget( checkBox1, 1, 0 );

    textLabel2 = new QLabel( this, "textLabel2" );

    MiscConfigLayout->addWidget( textLabel2, 2, 0 );

    kLineEdit1 = new KLineEdit( this, "kLineEdit1" );

    MiscConfigLayout->addWidget( kLineEdit1, 2, 1 );

    textLabel3 = new QLabel( this, "textLabel3" );
    textLabel3->setMaximumSize( QSize( 32767, 20 ) );

    MiscConfigLayout->addMultiCellWidget( textLabel3, 3, 3, 0, 1 );

    kLineEdit2 = new KLineEdit( this, "kLineEdit2" );

    MiscConfigLayout->addMultiCellWidget( kLineEdit2, 4, 4, 0, 1 );
    QSpacerItem* spacer = new QSpacerItem( 20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding );
    MiscConfigLayout->addItem( spacer, 5, 0 );
    languageChange();
    resize( QSize(357, 276).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
MiscConfig::~MiscConfig()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void MiscConfig::languageChange()
{
    setCaption( tr( "Miscellaneous preferences" ) );
    textLabel1->setText( tr( "Miscellaneous options" ) );
    checkBox1->setText( tr( "Show table grid" ) );
    QWhatsThis::add( checkBox1, tr( "If this is checked then the grid in all the tables is on, else it is off. The grid is turned on by default" ) );
    textLabel2->setText( tr( "Editor for custom file editing:" ) );
    QWhatsThis::add( kLineEdit1, tr( "Here you can define the editor for description files (<i>kwrite</i>, <i>kate</i>, <i>emacs</i>, etc.)" ) );
    textLabel3->setText( tr( "Text caption, used in font dialog display:" ) );
    QWhatsThis::add( kLineEdit2, tr( "This text is displayed in font dialog as an example" ) );
}

#include "config_misc.moc"
