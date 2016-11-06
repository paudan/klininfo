/***************************************************************************
                          fontdlg.h  -  description
                             -------------------
    begin                : Pn Bir 25 18:42:18 2004
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

#ifndef FONTPREVIEWDLG_H
#define FONTPREVIEWDLG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QComboBox;
class KListBox;
class QListBoxItem;
class KLineEdit;

class FontPreviewDlg : public QWidget
{
    Q_OBJECT

public:
    FontPreviewDlg( QWidget* parent = 0, const char* name = 0, WFlags fl = 0, int mode = 1 );
    ~FontPreviewDlg();

    QLabel* textLabel2_2;
    QComboBox* comboBox1_2;
    QLabel* textLabel2;
    QComboBox* comboBox1;
    KListBox* listBox1;
    QLabel* dlg_title;
    KLineEdit* kLineEdit1;

    void saveToFile(QString filename, int flags = IO_WriteOnly);

protected:
    QGridLayout* FontPreviewDlgLayout;

public slots:
    virtual void languageChange();
    void fontSelected();
    void fontSizeChanged(int );
    void fontStyleChanged(int );
    void loadFontInfo(int );
};

#endif // FONTPREVIEWDLG_H
