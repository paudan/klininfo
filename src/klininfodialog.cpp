/***************************************************************************
                          klininfodialog.cpp  -  description
                             -------------------
    begin                : Pn Bir 25 16:19:42 2004
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

#include "klininfodialog.h"

//----------------- QT includes----------------
#include <qvariant.h>
#include <qheader.h>
#include <qframe.h>
#include <qwidgetstack.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qpopupmenu.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qtimer.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qdir.h>
#include <qtable.h>
#include <qfiledialog.h>
#include <qcheckbox.h>
#include <qdatetime.h>
#include <qtextbrowser.h>

//------------------KDE includes----------------
#include <kapp.h>
#include <klistview.h>
#include <klocale.h>
#include <kstatusbar.h>
#include <kmenubar.h>
#include <kaboutkde.h>
#include <kaboutdialog.h>
#include <kdialogbase.h>
#include <kmessagebox.h>
#include <kglobal.h>
#include <kiconloader.h>
#include <ktextbrowser.h>
#include <ktextedit.h>
#include <kstandarddirs.h>

//----------------Other includes------------------
#include "fontdlg.h"
#include "printenvdlg.h"
#include "fileviewdlg.h"
#include "simpltabledlg.h"
#include "rpmsearchdlg.h"
#include "pkginfodlg.h"
#include "processlistdlg.h"
#include "scriptinfodlg.h"
#include "comdescrdlg.h"
#include "dudlg.h"
#include "modldispdlg.h"
#include "partitiondlg.h"
#include "memorydlg.h"
#include "configdlg.h"
#include "config_files.h"
#include "selsavedlg.h"

/*
 *  Constructs a KLinInfoDialog as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
KLinInfoDialog::KLinInfoDialog( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "KLinInfoDialog" );
    
    confdlg = new ConfigDlg(this, "confdlg", 0);
    connect(confdlg, SIGNAL(apply() ), this, SLOT(applySettings() ) );
    confdlg->loadSettings();
    pref = confdlg->opt;
    selsvdlg = new SelSaveDlg(this, "selsvdlg", 0);
}

/*
 *  Destroys the object and frees any allocated resources
 */
KLinInfoDialog::~KLinInfoDialog()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void KLinInfoDialog::languageChange()
{
    setCaption( tr( "KLinInfo v0.2" ) );
    kListView2->header()->setLabel( 0, QString::null );
    kListView2->clear();
    QListViewItem * item = new QListViewItem( kListView2, 0 );
    item->setText( 0, tr( "Command descriptions" ) );
    item->setPixmap( 0, QPixmap(locate("data","klininfo/icons/info_command.png") ));

    QListViewItem * item_2 = new QListViewItem( kListView2, item );
    item_2->setOpen( TRUE );
    item = new QListViewItem( item_2, item );
    item->setText( 0, tr( "Font families" ) );
    item_2->setOpen( TRUE );
    item = new QListViewItem( item_2, item );
    item->setText( 0, tr( "KDE fonts" ) );
    item_2->setText( 0, tr( "Fonts" ) );
    item_2->setPixmap( 0, QPixmap(locate("data","klininfo/icons/font_truetype.png")) );

    QListViewItem * item_3 = new QListViewItem( kListView2, item_2 );
    item_3->setOpen( TRUE );
    item = new QListViewItem( item_3, item_2 );
    item->setText( 0, tr( "log files" ) );
    item_3->setOpen( TRUE );
    item = new QListViewItem( item_3, item );
    item->setText( 0, tr( "System files" ) );
    item_3->setText( 0, tr( "Important files" ) );
    item_3->setPixmap( 0, QPixmap(locate("data", "klininfo/icons/log.png")) );

    QListViewItem * item_4 = new QListViewItem( kListView2, item_3 );
    item_4->setOpen( TRUE );
    item = new QListViewItem( item_4, item_3 );
    item->setText( 0, tr( "Disk information" ) );
    item_4->setOpen( TRUE );
    item = new QListViewItem( item_4, item );
    item->setText( 0, tr( "Memory information" ) );
    item_4->setOpen( TRUE );
    item = new QListViewItem( item_4, item );
    item->setText( 0, tr( "Other information" ) );
    item_4->setOpen( TRUE );
    item = new QListViewItem( item_4, item );
    item->setText( 0, tr( "printenv information" ) );
    item_4->setText( 0, tr( "Information" ) );
    item_4->setPixmap( 0, QPixmap(locate("data","klininfo/icons/detailed.png") ) );
    item_4->setOpen( TRUE );
    item = new QListViewItem( item_4, item );
    item->setText( 0, tr( "Process information" ) );
    item_4->setOpen( TRUE );
    item = new QListViewItem( item_4, item );
    item->setText( 0, tr( "Partition information" ) );
    item_4->setOpen( TRUE );
    item = new QListViewItem( item_4, item );
    item->setText( 0, tr( "Module information" ) );

    QListViewItem * item_6 = new QListViewItem( kListView2, item_4 );
    item_6->setOpen( TRUE );
    item = new QListViewItem( item_6, item_4 );
    item->setText( 0, tr( "RPM" ) );
    item_6->setOpen( TRUE );
    item = new QListViewItem( item_6, item );
    item->setText( 0, tr( "Package list" ) );
    item_6->setOpen( TRUE );
    item = new QListViewItem( item_6, item );
    item->setText( 0, tr( "Custom programs" ) );
    item_6->setText( 0, tr( "Packages" ) );
    item_6->setPixmap( 0, QPixmap(locate("data","klininfo/icons/rpm.png")) );

}


void KLinInfoDialog::initGUI()
{
    KLinInfoDialogLayout = new QGridLayout( this, 2, 1, 11, 6, "KLinInfoDialogLayout");
    KLinInfoDialogLayout->setRowSpacing(0, 20 );

    kListView2 = new KListView( this, "kListView2" );
    kListView2->addColumn( QString::null );
    kListView2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)7, 0, 0, kListView2->sizePolicy().hasHeightForWidth() ) );
    kListView2->setSorting(-1);
    kListView2->header()->hide();
    kListView2->setColumnWidth(0, kListView2->width());

    KLinInfoDialogLayout->addWidget( kListView2, 1, 0 );

    wstack = new QWidgetStack( this, "wstack" );

    KLinInfoDialogLayout->addWidget( wstack, 1, 1 );

    wstackLayout = new QVBoxLayout(wstack, 0, 0, "wstackLayout");

    languageChange();
    resize( QSize(687, 482).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    connect(kListView2, SIGNAL(executed(QListViewItem *)), this, SLOT(doAction()));

    initMenu();
    initStatusBar();
}    

void KLinInfoDialog::initMenu()
{
    QPixmap saveicon = KGlobal::iconLoader()->loadIcon("filesave.png", KIcon::Small);
    QPixmap refreshicon = KGlobal::iconLoader()->loadIcon("reload.png", KIcon::Small);
    QPixmap printicon = KGlobal::iconLoader()->loadIcon("fileprint.png", KIcon::Small);
    QPixmap helpicon = KGlobal::iconLoader()->loadIcon("toggle_log.png", KIcon::Small);
    QPixmap whthisicon = KGlobal::iconLoader()->loadIcon("help.png", KIcon::Small);

    QPopupMenu *saveopt = new QPopupMenu(this);
    CHECK_PTR( saveopt );
    saveopt->insertItem( tr("To separate files"), this, SLOT(selSaveDir()));
    saveopt->insertItem( tr("To a single file"), this, SLOT(selSave()) );

    QPopupMenu *file = new QPopupMenu( this );
    CHECK_PTR( file );
    file->insertItem(saveicon, tr("&Save"), saveopt, CTRL+Key_S );
    file->insertSeparator();
    file->insertItem( tr("E&xit"),  kapp, SLOT(quit()), ALT+Key_X );

    QPopupMenu *edit = new QPopupMenu( this );
    CHECK_PTR( edit );
    edit->insertItem( tr("Command descriptions file"), this, SLOT(editCommandDescr()));
    edit->insertItem( tr("System files descriptions file"), this, SLOT(editSystFilesDescr()) );
    edit->insertItem( tr("Log file descriptions file"), this, SLOT(editLogFilesDescr()) );
    edit->insertItem( tr("Version file"), this, SLOT(editFileVersions()));
    edit->insertItem( tr("Information script"), this, SLOT(editScript()));

    QPopupMenu *options = new QPopupMenu( this );
    CHECK_PTR( options );
    options->insertItem( tr("Edit files"), edit );
    options->insertItem( tr("Program &preferences"), this, SLOT(showConfigDlg()));

    QPopupMenu *help = new QPopupMenu( this );
    CHECK_PTR( help );
    help->insertItem( helpicon, tr("Help"), this, SLOT(showHelp()), Key_F1 );
    help->insertItem( whthisicon, tr("What's this?"), this, SLOT(whatsthisMode()), CTRL+Key_F1 );
    help->insertItem( tr("&About"), this, SLOT(showAbout()) );
    help->insertItem( tr("About KDE"), this, SLOT(showAboutKDE()));

    menu = new KMenuBar(this);
    CHECK_PTR(menu);
    menu->insertItem( tr("&File"), file );
    menu->insertItem( tr("Settings"), options );
    menu->setSeparator( KMenuBar::InWindowsStyle );
    menu->insertSeparator();
    menu->insertItem( tr("&Help"), help );
    
}

void KLinInfoDialog::initStatusBar()
{
/** Status bar setup */
    statusBar = new KStatusBar(this, "statusBar");
    statusBar->insertItem("", ID_GENERAL, 10 );
    statusBar->insertFixedItem( KGlobal::locale()->formatTime(QTime::currentTime(),true), ID_TIME_COLUMN );
    statusBar->setItemAlignment( ID_GENERAL, AlignLeft|AlignVCenter );
    statusBar->setItemAlignment( ID_TIME_COLUMN, AlignLeft|AlignVCenter );
    KLinInfoDialogLayout->addMultiCellWidget( statusBar, 2, 2, 0, 1);
    statusBar->changeItem (tr("Detailed information about your Linux system"), ID_GENERAL);

    QTimer * counter = new QTimer( this );
    connect( counter, SIGNAL(timeout()), SLOT(updateTimeCaption()) );
    counter->start( 1000 );               // emit signal every second
}

void KLinInfoDialog::initSettings()
{
  /** Init config files */
    QString home(QDir::home().path());
    home.append("/.klininfo");
    QDir homedir(home);
    if (! homedir.exists() ) { homedir.mkdir(home); confdlg->writeDefault(); }
    QFile f(home + "/klininforc");
    if (! f.exists() || f.size() == 0) confdlg->writeDefault();
    QFile fsrc(home + "/commandrc.kl");
    if (! fsrc.exists())  cpConfFile(locate("data","klininfo/templates/commandrc.kl"));
    QFile fver(home + "/systemrc.kl");
    if (! fver.exists())  cpConfFile(locate("data","klininfo/templates/systemrc.kl") );
    QFile flog(home + "/logrc.kl");
    if (! flog.exists())  cpConfFile(locate("data", "klininfo/templates/logrc.kl") );
    QFile fl(home + "/filever");
    if (! fl.exists())  cpConfFile(locate("data", "klininfo/templates/filever"));
}

void KLinInfoDialog::cpConfFile(QString filename)
{
  QFile f(filename);
  QFile o(QDir::home().path() + "/.klininfo/" + filename.section("/", -1));
  if (!f.open(IO_ReadOnly)  ) return;
  else {
    o.open(IO_WriteOnly);
    QTextStream out(&o);
    out << QString(f.readAll());
    f.close();
    o.close();
  }
}

void KLinInfoDialog::updateTimeCaption()
{
  statusBar->changeItem( KGlobal::locale()->formatTime(QTime::currentTime(),true), ID_TIME_COLUMN );
}

void KLinInfoDialog::doAction()
{
  int currItem = kListView2->itemIndex(kListView2->currentItem());
  if (currItem == 0)		showCommandDescrDlg();
  else if (currItem == 2)	showFontDlgFamilies();
  else if (currItem == 3)	showFontDlgKDE();
  else if (currItem == 5)	showLogView();
  else if (currItem == 6)	showSystView();
  else if (currItem == 8)	showDUDlg();
  else if (currItem == 9)	showMemoryDlg();
  else if (currItem == 10)	showMainInfo();
  else if (currItem == 11)	showPrintEnv();
  else if (currItem == 12)	showProcessDlg();
  else if (currItem == 13)	showPartitionDlg();
  else if (currItem == 14)	showModulesDlg();
  else if (currItem == 16)	showRPMDialog();
  else if (currItem == 17)	showPackageDialog();
  else if (currItem == 18)	showCustomVersions();
}

void KLinInfoDialog::showAboutKDE()
{
  aboutKDE = new KAboutKDE(this, "aboutKDE", true);
  aboutKDE->show();
}

void KLinInfoDialog::showHelp()
{
  kapp->invokeHelp("KLinInfo_about");
}

void KLinInfoDialog::whatsthisMode()
{
  QWhatsThis::enterWhatsThisMode();
}

void KLinInfoDialog::showAbout()
{
  KAboutDialog *aboutdlg = new KAboutDialog( 
                          KAboutDialog::AbtAppStandard, 
                          "KLinInfo v0.2", 
			  KDialogBase::Ok|KDialogBase::Close, 
			  KDialogBase::Ok, 
			  this, 
			  "aboutdlg", 
			  true, 
			  true, 
			  tr("Ok"), 
			  tr("Close") );
  aboutdlg->setImage(locate("data", "klininfo/pixmaps/splash_logo.jpg"));
  aboutdlg->setImageFrame(false);
  aboutdlg->setProduct("KLinInfo", "0.2", "Paulius Danenas", "2004");
  KAboutContainer *container = aboutdlg->addContainerPage(tr("Author"));
  container->addPerson("Paulius Danenas", "paulius.dan@takas.lt", NULL, NULL);
  aboutdlg->addTextPage(tr("About"), tr("The Linux information utility"), true, 10);
  aboutdlg->show();
    
}

void KLinInfoDialog::newFontDlg(FontPreviewDlg *dlg)
{
    wstackLayout->addWidget(dlg);
    connect((QObject *)dlg->comboBox1, SIGNAL(activated(int ) ), (QObject *)dlg, SLOT(fontStyleChanged(int ) ) );
    connect((QObject *)dlg->comboBox1_2, SIGNAL(activated(int ) ), (QObject *)dlg, SLOT(fontSizeChanged(int ) ) );
    connect(dlg->listBox1, SIGNAL( executed(QListBoxItem *)), (QObject *)dlg, SLOT(fontSelected() ) );
}

void KLinInfoDialog::showFontDlgFamilies()
{
  wstack->raiseWidget(ffdlg);
}

void KLinInfoDialog::showFontDlgKDE()
{
  wstack->raiseWidget(fdlg);
}

void KLinInfoDialog::showMainInfo()
{
  wstack->raiseWidget(scdlg);
}

void KLinInfoDialog::showPrintEnv()
{
  wstack->raiseWidget(prdlg);
}

void KLinInfoDialog::showSystView()
{
  statusBar->changeItem (systView->errorMsg, ID_GENERAL);
  wstack->raiseWidget(systView);
}

void KLinInfoDialog::showLogView()
{
  logView->dlg_title->setText(tr("Important system log files"));
  statusBar->changeItem (logView->errorMsg, ID_GENERAL);
  wstack->raiseWidget(logView);
}

void KLinInfoDialog::showCustomVersions()
{
  wstack->raiseWidget(vinfodlg);
}

void KLinInfoDialog::showRPMDialog()
{
  wstack->raiseWidget(rpmdlg);
}

void KLinInfoDialog::showPackageDialog()
{
  wstack->raiseWidget(pkgdlg);
}

void KLinInfoDialog::showProcessDlg()
{
  wstack->raiseWidget(procdlg);
}

void KLinInfoDialog::showCommandDescrDlg()
{
  wstack->raiseWidget(comdlg);
}

void KLinInfoDialog::showDUDlg()
{
  wstack->raiseWidget(dudlg);
}

void KLinInfoDialog::showModulesDlg()
{
  wstack->raiseWidget(mdldlg);
}

void KLinInfoDialog::showPartitionDlg()
{
  wstack->raiseWidget(ptdlg);
}

void KLinInfoDialog::showMemoryDlg()
{
 wstack->raiseWidget(memdlg);
}

void KLinInfoDialog::showConfigDlg()
{
  confdlg->show();
}

void KLinInfoDialog::loadWidgets()
{
  fdlg = new FontPreviewDlg(wstack, "fdlg", false, 0);
  newFontDlg(fdlg);

  ffdlg = new FontPreviewDlg(wstack, "ffdlg", false, 1);
  newFontDlg(ffdlg);

  scdlg = new ScriptInfoDlg(wstack, "scdlg", false, locate("exe","all_info"));
  wstack->addWidget(scdlg);

  prdlg = new PrintEnvDlg(wstack, "prdlg", false);
  wstack->addWidget(prdlg);

  systView = new FilePreviewDlg(wstack, "systview", 0);
  systView->descrFile = pref.systfile;
  (void) systView->loadFileList();
  wstack->addWidget(systView);

  logView = new FilePreviewDlg(wstack, "logview", 0);
  logView->descrFile = pref.logfile;
  (void) logView->loadFileList();
  logView->kTextBrowser2->setTextFormat( QTextEdit::LogText );
  logView->dlg_title->setText(tr("Important system log files"));
  wstack->addWidget(logView);

  vinfodlg = new VersionInfoDlg(wstack, "versioninfodlg", false, pref.verfile);
  wstack->addWidget(vinfodlg);

  rpmdlg = new RPMSearchDlg(wstack, "rpmdlg", false);
  wstack->addWidget(rpmdlg);

  pkgdlg = new pkgInfoDlg(wstack, "pkgdlg", false);
  wstack->addWidget(pkgdlg);

  procdlg = new ProcessListDlg(wstack, "procdlg", false);
  wstack->addWidget(procdlg);

  comdlg = new CommandDescrDlg(wstack, "comdlg", false, pref.cmdfile);
  wstack->addWidget(comdlg);

  dudlg = new DiskUsageDlg(wstack, "dudlg", false);
  wstack->addWidget(dudlg);

  mdldlg = new ModuleDisplaydlg(wstack, "mdldlg", false);
  wstack->addWidget(mdldlg);

  ptdlg = new PartitionDispDlg(wstack, "ptdlg", false);
  wstack->addWidget(ptdlg);

  memdlg = new MemoryDispDlg(wstack, "memdlg", false);
  wstack->addWidget(memdlg);
}

void KLinInfoDialog::applySettings()
{
  pref = confdlg->opt;
  scdlg->kTextBrowser1->setFont(pref.font_dlg);
  prdlg->textBrowser1->setFont(pref.font_dlg);
  systView->kTextBrowser2->setFont(pref.font_dlg);
  systView->kListBox1->setFont(pref.font_lbox);
  systView->kTextEdit1->setFont(pref.font_descr);
  logView->kTextBrowser2->setFont(pref.font_dlg);
  logView->kListBox1->setFont(pref.font_lbox);
  logView->kTextEdit1->setFont(pref.font_descr);
  vinfodlg->table1->setFont(pref.font_tbl);
  rpmdlg->kTextBrowser1->setFont(pref.font_dlg);
  pkgdlg->table1->setFont(pref.font_tbl);
  pkgdlg->textBrowser1->setFont(pref.font_descr);
  pkgdlg->textBrowser2->setFont(pref.font_descr);
  procdlg->table1->setFont(pref.font_tbl);
  comdlg->kTextBrowser1->setFont(pref.font_dlg);
  comdlg->listBox1->setFont(pref.font_lbox);
  dudlg->table1->setFont(pref.font_tbl);
  mdldlg->table1->setFont(pref.font_tbl);
  ptdlg->textBrowser1->setFont(pref.font_dlg);
  ptdlg->textBrowser2->setFont(pref.font_dlg);
  memdlg->table1->setFont(pref.font_tbl);
  vinfodlg->table1->setShowGrid(pref.showGrid);
  pkgdlg->table1->setShowGrid(pref.showGrid);
  procdlg->table1->setShowGrid(pref.showGrid);
  mdldlg->table1->setShowGrid(pref.showGrid);
  memdlg->table1->setShowGrid(pref.showGrid);
}

void KLinInfoDialog::editCommandDescr()
{
  confdlg->filecfg->editFile(pref.editorname, pref.cmdfile );
}

void KLinInfoDialog::editFileVersions()
{
  confdlg->filecfg->editFile(pref.editorname, pref.verfile );
}

void KLinInfoDialog::editLogFilesDescr()
{
  confdlg->filecfg->editFile(pref.editorname, pref.logfile );
}

void KLinInfoDialog::editSystFilesDescr()
{
  confdlg->filecfg->editFile(pref.editorname, pref.systfile );
}

void KLinInfoDialog::editScript()
{
  confdlg->filecfg->editFile(pref.editorname, locate("exe","all_info") );
}

void KLinInfoDialog::selSave()
{
   selsvdlg->disconnect(SIGNAL( apply() ) );
   connect( selsvdlg, SIGNAL( apply() ), this, SLOT ( doSaving() ) );
   selsvdlg->show();
}

void KLinInfoDialog::selSaveDir()
{
   selsvdlg->disconnect(SIGNAL( apply() ) );
   connect( selsvdlg, SIGNAL( apply() ), this, SLOT ( doSavingDir() ) );
   selsvdlg->show();
}

void KLinInfoDialog::doSaving()
{
  QString s( QFileDialog::getSaveFileName( QString::null, tr("HTML files (*.html, *.htm);;All files (*)"), this ) );
  if ( s.isEmpty() ) return;
  else {
     s = s + ".html";
     saveAllToFile(s);
  }
}

void KLinInfoDialog::saveAllToFile(QString s)
{
     if (selsvdlg->checkBox1->isChecked() )  comdlg->saveToFile(s, IO_WriteOnly);
     if (selsvdlg->checkBox2->isChecked() )  systView->saveToFile(s, IO_WriteOnly|IO_Append);
     if (selsvdlg->checkBox3->isChecked() )  logView->saveToFile(s, IO_WriteOnly|IO_Append);
     if (selsvdlg->checkBox4->isChecked() )  dudlg->saveToFile(s, IO_WriteOnly|IO_Append);
     if (selsvdlg->checkBox5->isChecked() )  saveTableData(s, tr("Memory information"), memdlg->table1, IO_WriteOnly|IO_Append);
     if (selsvdlg->checkBox6->isChecked() )  saveData(s, tr("Information about Linux"), scdlg->kTextBrowser1, IO_WriteOnly|IO_Append);
     if (selsvdlg->checkBox7->isChecked() )  prdlg->saveToFile(s, IO_WriteOnly|IO_Append);
     if (selsvdlg->checkBox8->isChecked() )  saveTableData(s, tr("Process information"), procdlg->table1, IO_WriteOnly|IO_Append);
     if (selsvdlg->checkBox9->isChecked() )  saveData(s, tr("Partition information"), (KTextBrowser*)ptdlg->textBrowser2, IO_WriteOnly|IO_Append);
     if (selsvdlg->checkBox16->isChecked() )  saveData(s, tr("Hard disk information"), (KTextBrowser*)ptdlg->textBrowser1, IO_WriteOnly|IO_Append);
     if (selsvdlg->checkBox10->isChecked() )  saveTableData(s, tr("Module information"), mdldlg->table1, IO_WriteOnly|IO_Append);
     if (selsvdlg->checkBox12->isChecked() )  saveTableData(s, tr("Package information"), pkgdlg->table1, IO_WriteOnly|IO_Append);
     if (selsvdlg->checkBox13->isChecked() )  saveData(s, tr("RPM package information"), (KTextBrowser*)rpmdlg->kTextBrowser1, IO_WriteOnly|IO_Append);
     if (selsvdlg->checkBox14->isChecked() )  saveTableData(s, tr("Version information"), vinfodlg->table1, IO_WriteOnly|IO_Append);
     if (selsvdlg->checkBox15->isChecked() )  fdlg->saveToFile(s,IO_WriteOnly|IO_Append);

     appendFooter(s);
}

void KLinInfoDialog::doSavingDir()
{
  QString s( QFileDialog::getExistingDirectory( QString::null, this, "fd", QString::null, TRUE ) );
  if ( s.isEmpty() ) return;
  else {
     QDir k(s);
     if (!k.exists() ) k.mkdir(s);
     if (selsvdlg->checkBox1->isChecked() )
        { comdlg->saveToFile(s + "/commandinfo.html");
	  appendFooter(s + "/commandinfo.html");
	}
     if (selsvdlg->checkBox2->isChecked() )
        { systView->saveToFile(s + "/systfileinfo.html");
	  appendFooter(s + "/systfileinfo.html");
	}
     if (selsvdlg->checkBox3->isChecked() )
        { logView->saveToFile(s + "/logfileinfo.html");
	  appendFooter(s + "/logfileinfo.html");
	}
     if (selsvdlg->checkBox4->isChecked() )
        { dudlg->saveToFile(s + "/duinfo.html");
	  appendFooter(s + "/duinfo.html");
	}
     if (selsvdlg->checkBox5->isChecked() )
        { saveTableData(s + "/memoryinfo.html", tr("Memory information"), memdlg->table1);
	  appendFooter(s + "/memoryinfo.html");
	}
     if (selsvdlg->checkBox6->isChecked() )
        { saveData(s + "/scriptinfo.html", tr("Information about Linux"), scdlg->kTextBrowser1);
	  appendFooter(s + "/scriptinfo.html");
	}
     if (selsvdlg->checkBox7->isChecked() )
        { prdlg->saveToFile(s + "/printenvinfo.html");
	  appendFooter(s + "/printenvinfo.html");
	}
     if (selsvdlg->checkBox8->isChecked() )
        { saveTableData(s + "/processinfo.html", tr("Process information"), procdlg->table1);
	  appendFooter(s + "/processinfo.html");
	}
     if (selsvdlg->checkBox9->isChecked() )
        { saveData(s + "/partitioninfo.html", tr("Partition information"), (KTextBrowser*)ptdlg->textBrowser2);
	  appendFooter(s + "/partitioninfo.html");
	}
     if (selsvdlg->checkBox10->isChecked() )
        { saveTableData(s + "/moduleinfo.html", tr("Module information"), mdldlg->table1);
	  appendFooter(s + "/moduleinfo.html");
	}
     if (selsvdlg->checkBox12->isChecked() )
        { saveTableData(s + "/packageinfo.html", tr("Package information"), pkgdlg->table1);
	  appendFooter(s + "/packageinfo.html");
	}
     if (selsvdlg->checkBox13->isChecked() )
        { saveData(s + "/rpminfo.html", tr("RPM package information"), (KTextBrowser*)rpmdlg->kTextBrowser1);
	  appendFooter(s + "/rpminfo.html");
	}
     if (selsvdlg->checkBox14->isChecked() )
        { saveTableData(s + "/versioninfo.html", tr("Version information"), vinfodlg->table1);
	  appendFooter(s + "/versioninfo.html");
	}
     if (selsvdlg->checkBox15->isChecked() )
        { fdlg->saveToFile(s + "/fontinfo.html");
	  appendFooter(s + "/fontinfo.html");
	}
     if (selsvdlg->checkBox16->isChecked() )
        { saveData(s + "/hdinfo.html", tr("Hard disk information"), (KTextBrowser*)ptdlg->textBrowser1);
	  appendFooter(s + "/hdinfo.html");
	}
  }
}

void KLinInfoDialog::saveTableData(QString filename, QString header, QTable* table, int flags)
{
   QFile f(filename);
   if (!f.open(flags) ) return;
   QTextStream stream(&f);
   stream << "<html>" << "<head>";
   stream << "<title align=\"center\">" << header << "</title>";
   stream << "</head>";
   stream << "<body>";
   stream << "<h1 align=\"center\">" << header << "</h1>";
   stream << "<table border=\"2\">"<< "<thead>" << "<tr>";
   for (int i = 0; i < table->horizontalHeader()->count(); i++)
      stream << "<th scope=col>" << table->horizontalHeader()->label(i) << "</th>";
   stream << "</tr>" << "</thead>";
   stream << "<tbody>";
   for (int i = 0; i < table->numRows(); i++) {
      stream << "<tr>";
      for (int j = 0; j < table->numCols(); j++)
         stream << "<td>" << table->text(i, j) << "</td>";
      stream << "</tr>";
   }
   stream << "</tbody>" << "</table>";
   f.close();
}

void KLinInfoDialog::saveData(QString filename, QString header, KTextBrowser* textBrowser, int flags)
{
  QFile f(filename);
   if (!f.open(flags) ) return;
   QTextStream stream(&f);
   stream << "<html>" << "<head>";
   stream << "<title align=\"center\">" << header << "</title>";
   stream << "</head>";
   stream << "<body>";
   stream << "<h1 align=\"center\">" << header << "</h1>";
   QString txt = textBrowser->text();
   QTextStream istream(&txt, IO_ReadOnly);
   while (!istream.atEnd() )  stream << istream.readLine() << "<br>";
   f.close();
}

void KLinInfoDialog::appendFooter(QString filename)
{
  QFile f(filename);
   if (!f.open(IO_WriteOnly|IO_Append) ) return;
   QTextStream stream(&f);
   stream << "<hr>";
   stream << "Generated by <b><i>KLinInfo v0.2</i></b> on " << QDate::currentDate().toString(Qt::LocalDate) << " " <<  QTime::currentTime().toString(Qt::LocalDate);
   stream << "</body>" << "</html>";
   f.close();
}


#include "klininfodialog.moc"
