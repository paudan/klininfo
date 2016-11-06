/***************************************************************************
                          klininfodialog.h  -  description
                             -------------------
    begin                : Pn Bir 25 16:19:41 2004
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

#ifndef KLININFODIALOG_H
#define KLININFODIALOG_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <qvariant.h>
#include <qwidget.h>
#include "configdlg.h"

#define ID_TIME_COLUMN 1
#define ID_GENERAL 2

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class KListView;
class QListViewItem;
class QWidgetStack;
class QStringList;
class QTable;
class QTextBrowser;
class KMenuBar;
class KStatusBar;
class KTextBrowser;
class KAboutKDE;
class FontPreviewDlg;
class ScriptInfoDlg;
class PrintEnvDlg;
class FilePreviewDlg;
class VersionInfoDlg;
class RPMSearchDlg;
class pkgInfoDlg;
class ProcessListDlg;
class CommandDescrDlg;
class DiskUsageDlg;
class ModuleDisplaydlg;
class PartitionDispDlg;
class MemoryDispDlg;
class ConfigDlg;
class SelSaveDlg;

class KLinInfoDialog : public QWidget
{
    Q_OBJECT

public:
    KLinInfoDialog( QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~KLinInfoDialog();

    KListView* kListView2;
    QWidgetStack* wstack;
    KMenuBar *menu;
    KStatusBar *statusBar;

    KAboutKDE* aboutKDE;
    FontPreviewDlg* fdlg;
    FontPreviewDlg* ffdlg;
    ScriptInfoDlg* scdlg;
    PrintEnvDlg* prdlg;
    FilePreviewDlg* systView;
    FilePreviewDlg* logView;
    VersionInfoDlg* vinfodlg;
    RPMSearchDlg *rpmdlg;
    pkgInfoDlg *pkgdlg;
    ProcessListDlg *procdlg;
    CommandDescrDlg *comdlg;
    DiskUsageDlg *dudlg;
    ModuleDisplaydlg *mdldlg;
    PartitionDispDlg *ptdlg;
    MemoryDispDlg *memdlg;
    ConfigDlg* confdlg;
    SelSaveDlg* selsvdlg;

    Settings pref;

    /* initializes the GUI */
    virtual void initGUI();
    
    /* this creates the menu. Change the menu look and add new menu items in this function */
    virtual void initMenu();

    /*this creates the status bar with two blocks inside of it - for messages and watch*/
    virtual void initStatusBar();

    /*loads all the widgets*/
    virtual void loadWidgets();

    /*initializes settings; if needed, new configuration files are created*/
    virtual void initSettings();

public slots:
    virtual void showFontDlgFamilies();
    virtual void showFontDlgKDE();
    virtual void showMainInfo();
    virtual void showPrintEnv();
    virtual void showSystView();
    virtual void showLogView();
    virtual void showCustomVersions();
    virtual void showRPMDialog();
    virtual void showPackageDialog();
    virtual void showProcessDlg();
    virtual void showCommandDescrDlg();
    virtual void showDUDlg();
    virtual void showModulesDlg();
    virtual void showPartitionDlg();
    virtual void showMemoryDlg();
    virtual void showConfigDlg();
    virtual void applySettings();
    virtual void editCommandDescr();
    virtual void editSystFilesDescr();
    virtual void editLogFilesDescr();
    virtual void editFileVersions();
    virtual void editScript();
    virtual void selSave();
    virtual void selSaveDir();

protected:
    QGridLayout* KLinInfoDialogLayout;
    QVBoxLayout* wstackLayout;

protected slots:
    virtual void languageChange();
    virtual void doSaving();
    virtual void doSavingDir();
    
private:
    bool printHeader;
    QString headerCenter;
    void newFontDlg(FontPreviewDlg *);
    void cpConfFile(QString );
    void saveTableData(QString, QString, QTable *, int flags = IO_WriteOnly);
    void saveData(QString, QString, KTextBrowser *, int flags = IO_WriteOnly);
    void appendFooter(QString );
    void saveAllToFile(QString );

private slots:
    virtual void showAboutKDE();
    virtual void showHelp();
    virtual void showAbout();
    virtual void whatsthisMode();
    virtual void updateTimeCaption();
    virtual void doAction();
};

#endif // KLININFODIALOG_H
