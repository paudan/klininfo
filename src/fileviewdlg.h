/***************************************************************************
                          fileviewdlg.h  -  description
                             -------------------
    begin                : Tr Lie 7 12:47:51 2004
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

#ifndef FILEPREVIEWDLG_H
#define FILEPREVIEWDLG_H

#include <qvariant.h>
#include <qwidget.h>

#define INFO_DELIMITER "\t*****"
#define FILE_TMP1 "/tmp/tmp0045.tmp"
#define FILE_TMP2 "/tmp/tmp0012.tmp"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class KTextBrowser;
class KTextEdit;
class QFrame;
class QPushButton;
class KListBox;
class QListBoxItem;
class QStringList;
class FileInputDlg;

class FilePreviewDlg : public QWidget
{
    Q_OBJECT

public:
    FilePreviewDlg( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~FilePreviewDlg();

    QLabel* dlg_title;
    QFrame *frameLabel;
    KTextBrowser* kTextBrowser2;
    QLabel* textLabel3;
    KTextEdit* kTextEdit1;
    QLabel* textLabel2;
    QFrame* frame;
    QLabel* textLabel1;
    QPushButton* addButton;
    QPushButton* modifyButton;
    QPushButton* removeButton;
    KListBox* kListBox1;
    FileInputDlg* inputdlg;

    QString errorMsg;
    QString descrFile;
    bool loadFileList( );
    virtual void saveToFile(QString filename, int flags = IO_WriteOnly);

public slots:
    virtual void kListBox1_executed(QListBoxItem*);
    virtual void addButton_clicked();
    virtual void modifyButton_clicked();
    virtual void removeButton_clicked();
    virtual void editFileDesc();

protected:
    QGridLayout* FilePreviewDlgLayout;
    QGridLayout* frameLayout;
    QVBoxLayout* frameLabelLayout;

protected slots:
    virtual void languageChange();

private:
    QStringList fileList;
    int editState;
    void loadDescription();
};

#endif // FILEPREVIEWDLG_H
