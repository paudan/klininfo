/***************************************************************************
                          configdlg.h  -  description
                             -------------------
    begin                : Kt Lie 15 17:10:40 2004
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

#ifndef CONFIGDLG_H
#define CONFIGDLG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QPushButton;
class QIconView;
class QIconViewItem;
class QWidgetStack;
class QWidget;
class KSimpleConfig;
class FontConfig;
class FilesConfig;
class MiscConfig;

struct Settings {
   QFont font_dlg, font_descr, font_tbl, font_lbox;
   QString cmdfile, systfile, logfile, verfile, editorname, examplestr;
   bool showGrid;
};

class ConfigDlg : public QDialog
{
    Q_OBJECT

public:
    ConfigDlg( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~ConfigDlg();

    QPushButton* buttonHelp;
    QPushButton* buttonDefault;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QIconView* iconView2;
    QWidgetStack* widgetStack1;
    QWidget* WStackPage;
    KSimpleConfig* konfig;
    FontConfig* fontcfg;
    FilesConfig* filecfg;
    MiscConfig* misccfg;

    Settings opt;

    virtual void loadSettings();

public slots:
    virtual void selectDialog();
    virtual void writeDefault();
    virtual void writeSettings();
    virtual void accept();
    virtual void defaultPressed();
    virtual void helpPressed();

signals:
    void apply();

protected:
    QGridLayout* ConfigDlgLayout;
    QHBoxLayout* Layout1;
    QVBoxLayout* widgetStack1Layout;

protected slots:
    virtual void languageChange();
    virtual void editButton1_clicked();
    virtual void editButton2_clicked();
    virtual void editButton3_clicked();
    virtual void editButton4_clicked();

private:
    virtual void setDialog();
};

#endif // CONFIGDLG_H
