/***************************************************************************
                          configdlg.cpp  -  description
                             -------------------
    begin                : Kt Lie 15 17:10:41 2004
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

#include "configdlg.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qiconview.h>
#include <qwidgetstack.h>
#include <qwidget.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qdir.h>
#include <qcheckbox.h>
#include <kapp.h>
#include <ksimpleconfig.h>
#include <kcombobox.h>
#include <kfontdialog.h>
#include <klineedit.h>
#include <kstandarddirs.h>

#include "config_font.h"
#include "config_files.h"
#include "config_misc.h"

/*
 *  Constructs a ConfigDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
ConfigDlg::ConfigDlg( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "ConfigDlg" );
    setIcon( QPixmap(locate("data","klininfo/icons/configure.png") ) );
    setSizeGripEnabled( TRUE );
    ConfigDlgLayout = new QGridLayout( this, 1, 1, 11, 6, "ConfigDlgLayout");

    Layout1 = new QHBoxLayout( 0, 0, 8, "Layout1");

    buttonHelp = new QPushButton( this, "buttonHelp" );
    buttonHelp->setAutoDefault( TRUE );
    Layout1->addWidget( buttonHelp );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( spacer );

    buttonDefault = new QPushButton( this, "buttonDefault" );
    buttonDefault->setAutoDefault( TRUE );
    Layout1->addWidget( buttonDefault );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    Layout1->addWidget( buttonOk );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    Layout1->addWidget( buttonCancel );

    ConfigDlgLayout->addMultiCellLayout( Layout1, 1, 1, 0, 1 );

    iconView2 = new QIconView( this, "iconView2" );
    iconView2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)7, 0, 0, iconView2->sizePolicy().hasHeightForWidth() ) );
    QFont iconView2_font(  iconView2->font() );
    iconView2_font.setPointSize( 13 );
    iconView2_font.setBold( TRUE );
    iconView2->setFont( iconView2_font ); 

    ConfigDlgLayout->addWidget( iconView2, 0, 0 );

    widgetStack1 = new QWidgetStack( this, "widgetStack1" );

    widgetStack1Layout = new QVBoxLayout(widgetStack1, 0, 0, "widgetStack1Layout");

    ConfigDlgLayout->addWidget( widgetStack1, 0, 1 );
    languageChange();
    resize( QSize(597, 366).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( buttonDefault, SIGNAL( clicked() ), this, SLOT(defaultPressed() ) );
    connect( buttonHelp, SIGNAL( clicked() ), this, SLOT(helpPressed() ) );
    connect( iconView2, SIGNAL( selectionChanged()), this, SLOT( selectDialog() ) );

    fontcfg = new FontConfig(widgetStack1, "fontcfg", false);
    widgetStack1->addWidget(fontcfg);
    filecfg = new FilesConfig(widgetStack1, "filecfg", false);
    widgetStack1->addWidget(filecfg);
    misccfg = new MiscConfig(widgetStack1, "misccfg", false);
    widgetStack1->addWidget(misccfg);

    connect( filecfg->pushButton1, SIGNAL( clicked() ), this, SLOT( editButton1_clicked() ) );
    connect( filecfg->pushButton2, SIGNAL( clicked() ), this, SLOT( editButton2_clicked() ) );
    connect( filecfg->pushButton3, SIGNAL( clicked() ), this, SLOT( editButton3_clicked() ) );
    connect( filecfg->pushButton4, SIGNAL( clicked() ), this, SLOT( editButton4_clicked() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
ConfigDlg::~ConfigDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ConfigDlg::languageChange()
{
    setCaption( tr( "Configuration Dialog" ) );
    buttonHelp->setText( tr( "&Help" ) );
    buttonHelp->setAccel( QKeySequence( tr( "F1" ) ) );
    buttonDefault->setText( tr( "Default" ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
    iconView2->clear();
    (void) new QIconViewItem( iconView2, tr( "Fonts" ), QPixmap(locate("data", "klininfo/icons/font_truetype_large.png")) );
    (void) new QIconViewItem( iconView2, tr( "Files" ), QPixmap(locate("data", "klininfo/icons/source.png")) );
    (void) new QIconViewItem( iconView2, tr( "Other" ), QPixmap(locate("data", "klininfo/icons/misc.png")) );
}

void ConfigDlg::selectDialog()
{
  int DlgID = iconView2->index( iconView2->currentItem() );
  if (DlgID == 0) 	widgetStack1->raiseWidget(fontcfg);
  else if (DlgID == 1)	widgetStack1->raiseWidget(filecfg);
  else if (DlgID == 2)	widgetStack1->raiseWidget(misccfg);
}

void ConfigDlg::loadSettings()
{
 const QFont DIALOGS = QFont("helvetica", 12),
              DESCR = QFont("helvetica", 12),
	      TABLES = QFont("helvetica", 12),
	      LISTBOXES = QFont("helvetica", 12);

  konfig = new KSimpleConfig(QDir::home().path() + "/.klininfo/klininforc");

  konfig->setGroup("Fonts");
  opt.font_dlg = konfig->readFontEntry("DialogFont", &DIALOGS);
  opt.font_descr = konfig->readFontEntry("DescriptionFont", &DESCR);
  opt.font_tbl = konfig->readFontEntry("TableFont", &TABLES);
  opt.font_lbox = konfig->readFontEntry("ListboxFont", &LISTBOXES);
  konfig->setGroup("Source files");
  opt.cmdfile = konfig->readPathEntry("CommandDescriptionFile", QDir::home().path() + "/.klininfo/commandrc.kl");
  opt.systfile = konfig->readPathEntry("SystemDescriptionFile", QDir::home().path() + "/.klininfo/systemrc.kl");
  opt.logfile = konfig->readPathEntry("LogDescriptionFile", QDir::home().path() + "/.klininfo/logrc.kl");
  opt.verfile = konfig->readPathEntry("VersionFile", QDir::home().path() + "/.klininfo/filever");
  konfig->setGroup("Misc");
  opt.editorname = konfig->readEntry("Editor", "kwrite");
  opt.examplestr = konfig->readEntry("FontExample", "This is an example");
  opt.showGrid = konfig->readBoolEntry("ShowTableGrid", true);

  setDialog();
  delete konfig;
}

void ConfigDlg::writeDefault()
{
  konfig = new KSimpleConfig(QDir::home().path() + "/.klininfo/klininforc");
  opt.font_dlg = opt.font_descr = opt.font_tbl = opt.font_lbox = QFont("helvetica", 12);
  opt.cmdfile = QDir::home().path() + "/.klininfo/commandrc.kl";
  opt.systfile = QDir::home().path() + "/.klininfo/systemrc.kl";
  opt.logfile = QDir::home().path() + "/.klininfo/logrc.kl";
  opt.verfile = QDir::home().path() + "/.klininfo/filever";
  opt.editorname = "kwrite";
  opt.examplestr = "This is an example";
  opt.showGrid = true;

  konfig->setGroup("Fonts");
  konfig->writeEntry("DialogFont", opt.font_dlg);
  konfig->writeEntry("DescriptionFont", opt.font_descr);
  konfig->writeEntry("TableFont", opt.font_tbl);
  konfig->writeEntry("ListBoxFont", opt.font_lbox);
  konfig->setGroup("Source files");
  konfig->writeEntry("CommandDescriptionFile", opt.cmdfile);
  konfig->writeEntry("SystemDescriptionFile", opt.systfile);
  konfig->writeEntry("LogDescriptionFile", opt.logfile);
  konfig->writeEntry("VersionFile", opt.verfile);
  konfig->setGroup("Misc");
  konfig->writeEntry("Editor", opt.editorname);
  konfig->writeEntry("FontExample", opt.examplestr);
  konfig->writeEntry("ShowTableGrid", opt.showGrid);
  delete konfig;

  setDialog();
}

void ConfigDlg::setDialog()
{
  if (fontcfg->kComboBox1->currentItem() == 0)
    fontcfg->kFontDialog->setFont(opt.font_dlg);
  else if (fontcfg->kComboBox1->currentItem() == 1)
    fontcfg->kFontDialog->setFont(opt.font_descr);
  else if (fontcfg->kComboBox1->currentItem() == 2)
    fontcfg->kFontDialog->setFont(opt.font_tbl);
  else if (fontcfg->kComboBox1->currentItem() == 3)
    fontcfg->kFontDialog->setFont(opt.font_lbox);
  filecfg->kLineEdit1->setText(opt.cmdfile);
  filecfg->kLineEdit2->setText(opt.systfile);
  filecfg->kLineEdit3->setText(opt.logfile);
  filecfg->kLineEdit4->setText(opt.verfile);
  misccfg->checkBox1->setChecked(opt.showGrid);
  misccfg->kLineEdit2->setText(opt.examplestr);
  misccfg->kLineEdit1->setText(opt.editorname);
}

void ConfigDlg::writeSettings()
{
  konfig = new KSimpleConfig(QDir::home().path() + "/.klininfo/klininforc");

  opt.font_dlg = fontcfg->fsettings[0];
  opt.font_descr = fontcfg->fsettings[1];
  opt.font_tbl = fontcfg->fsettings[2];
  opt.font_lbox = fontcfg->fsettings[3];
  opt.cmdfile = filecfg->kLineEdit1->text().stripWhiteSpace();
  opt.systfile = filecfg->kLineEdit2->text().stripWhiteSpace();
  opt.logfile = filecfg->kLineEdit3->text().stripWhiteSpace();
  opt.verfile = filecfg->kLineEdit4->text().stripWhiteSpace();
  opt.editorname = misccfg->kLineEdit1->text().simplifyWhiteSpace();
  opt.examplestr = misccfg->kLineEdit2->text();
  opt.showGrid = misccfg->checkBox1->isChecked();

  konfig->setGroup("Fonts");
  konfig->writeEntry("DialogFont", opt.font_dlg);
  konfig->writeEntry("DescriptionFont", opt.font_descr);
  konfig->writeEntry("TableFont", opt.font_tbl);
  konfig->writeEntry("ListBoxFont", opt.font_lbox);
  konfig->setGroup("Source files");
  konfig->writeEntry("CommandDescriptionFile", opt.cmdfile);
  konfig->writeEntry("SystemDescriptionFile", opt.systfile);
  konfig->writeEntry("LogDescriptionFile", opt.logfile);
  konfig->writeEntry("VersionFile", opt.verfile);
  konfig->setGroup("Misc");
  konfig->writeEntry("Editor", opt.editorname);
  konfig->writeEntry("FontExample", opt.examplestr);
  konfig->writeEntry("ShowTableGrid", opt.showGrid);

  emit apply();
  delete konfig;
}

void ConfigDlg::editButton1_clicked()
{
  filecfg->editFile(misccfg->kLineEdit1->text(), filecfg->kLineEdit1->text() );
}

void ConfigDlg::editButton2_clicked()
{
  filecfg->editFile(misccfg->kLineEdit1->text(), filecfg->kLineEdit2->text() );
}

void ConfigDlg::editButton3_clicked()
{
  filecfg->editFile(misccfg->kLineEdit1->text(), filecfg->kLineEdit3->text() );
}

void ConfigDlg::editButton4_clicked()
{
  filecfg->editFile(misccfg->kLineEdit1->text(), filecfg->kLineEdit4->text() );
}

void ConfigDlg::accept()
{
  fontcfg->fsettings[fontcfg->curTypeWidget] = fontcfg->curWidgetFont;
  writeSettings();
  hide();
}

void ConfigDlg::defaultPressed()
{
  writeDefault();
  emit apply();
}

void ConfigDlg::helpPressed()
{
  kapp->invokeHelp("KLinInfo_about");
}

#include "configdlg.moc"
