/****************************************************************************
** Form implementation generated from reading ui file '/home/Paulius/klininfo_v0.2/klininfo/src/selsavedlg.ui'
**
** Created: An Lie 20 21:13:47 2004
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.2.1   edited May 19 14:22 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "selsavedlg.h"

#include <kglobal.h>
#include <kiconloader.h>
#include <qvariant.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a SelSaveDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
SelSaveDlg::SelSaveDlg( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "SelSaveDlg" );
    setIcon(KGlobal::iconLoader()->loadIcon("filesave.png", KIcon::Small));
    SelSaveDlgLayout = new QGridLayout( this, 1, 1, 11, 6, "SelSaveDlgLayout");

    textLabel1 = new QLabel( this, "textLabel1" );

    SelSaveDlgLayout->addWidget( textLabel1, 0, 0 );

    checkBox1 = new QCheckBox( this, "checkBox1" );

    SelSaveDlgLayout->addWidget( checkBox1, 1, 0 );

    checkBox2 = new QCheckBox( this, "checkBox2" );

    SelSaveDlgLayout->addWidget( checkBox2, 2, 0 );

    checkBox4 = new QCheckBox( this, "checkBox4" );

    SelSaveDlgLayout->addWidget( checkBox4, 4, 0 );

    checkBox5 = new QCheckBox( this, "checkBox5" );

    SelSaveDlgLayout->addWidget( checkBox5, 5, 0 );

    checkBox6 = new QCheckBox( this, "checkBox6" );

    SelSaveDlgLayout->addWidget( checkBox6, 6, 0 );

    checkBox7 = new QCheckBox( this, "checkBox7" );

    SelSaveDlgLayout->addWidget( checkBox7, 7, 0 );

    checkBox8 = new QCheckBox( this, "checkBox8" );

    SelSaveDlgLayout->addMultiCellWidget( checkBox8, 1, 1, 1, 2 );

    checkBox15 = new QCheckBox( this, "checkBox15" );

    SelSaveDlgLayout->addWidget( checkBox15, 8, 0 );

    pushButton2 = new QPushButton( this, "pushButton2" );
    pushButton2->setMaximumSize( QSize( 87, 32767 ) );

    SelSaveDlgLayout->addWidget( pushButton2, 9, 2 );
    QSpacerItem* spacer = new QSpacerItem( 90, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    SelSaveDlgLayout->addItem( spacer, 9, 1 );

    checkBox9 = new QCheckBox( this, "checkBox9" );

    SelSaveDlgLayout->addMultiCellWidget( checkBox9, 2, 2, 1, 2 );

    checkBox3 = new QCheckBox( this, "checkBox3" );

    SelSaveDlgLayout->addWidget( checkBox3, 3, 0 );

    checkBox12 = new QCheckBox( this, "checkBox12" );

    SelSaveDlgLayout->addMultiCellWidget( checkBox12, 5, 5, 1, 2 );

    checkBox10 = new QCheckBox( this, "checkBox10" );

    SelSaveDlgLayout->addMultiCellWidget( checkBox10, 4, 4, 1, 2 );

    checkBox13 = new QCheckBox( this, "checkBox13" );

    SelSaveDlgLayout->addMultiCellWidget( checkBox13, 6, 6, 1, 2 );

    checkBox14 = new QCheckBox( this, "checkBox14" );

    SelSaveDlgLayout->addMultiCellWidget( checkBox14, 7, 7, 1, 2 );

    checkBox16 = new QCheckBox( this, "checkBox16" );

    SelSaveDlgLayout->addMultiCellWidget( checkBox16, 3, 3, 1, 2 );
    languageChange();
    connect(pushButton2, SIGNAL( clicked() ), this, SLOT (applySelection() ) );
    resize( QSize(464, 296).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
SelSaveDlg::~SelSaveDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void SelSaveDlg::languageChange()
{
    setCaption( tr( "Select what to save" ) );
    textLabel1->setText( tr( "Select what to save:" ) );
    checkBox1->setText( tr( "Command list and their descriptions" ) );
    checkBox2->setText( tr( "System file list and their descriptions" ) );
    checkBox4->setText( tr( "Disk usage information" ) );
    checkBox5->setText( tr( "Memory information" ) );
    checkBox6->setText( tr( "Custom information" ) );
    checkBox7->setText( tr( "printenv information" ) );
    checkBox8->setText( tr( "Process information" ) );
    checkBox15->setText( tr( "Font information" ) );
    pushButton2->setText( tr( "Select" ) );
    checkBox9->setText( tr( "Partition information" ) );
    checkBox3->setText( tr( "Log file list and their descriptions" ) );
    checkBox12->setText( tr( "Package information" ) );
    checkBox10->setText( tr( "Module information" ) );
    checkBox13->setText( tr( "RPM package information" ) );
    checkBox14->setText( tr( "Program version information" ) );
    checkBox16->setText( tr( "Hard disk information" ) );
}

void SelSaveDlg::applySelection()
{
  emit apply();
  hide();
}

#include "selsavedlg.moc"
