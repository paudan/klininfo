/***************************************************************************
                          comdescrdlg.cpp  -  description
                             -------------------
    begin                : Pr Lie 5 15:38:44 2004
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

#ifndef COMDESCRDLG_H
#define COMDESCRDLG_H

#include <qvariant.h>
#include <qwidget.h>

//This separates the command name and description in the list
#define INFO_DELIMITER "\t*****"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class KTextBrowser;
class QPushButton;
class QListBox;
class QListBoxItem;
class QStringList;
class InputDlg;

class CommandDescrDlg : public QWidget
{
    Q_OBJECT

public:
    CommandDescrDlg( QWidget* parent = 0, const char* name = 0, WFlags fl = 0, QString filename = 0);
    ~CommandDescrDlg();

    QLabel* TextLabel1;
    QLabel* textLabel3;
    KTextBrowser* kTextBrowser1;
    QPushButton* addButton;
    QPushButton* modifyButton;
    QPushButton* removeButton;
    QListBox* listBox1;
    InputDlg *inputdlg;

    QString errorMsg;
    virtual void saveToFile(QString filename, int flags = IO_WriteOnly);

public slots:
    virtual void listBox1_selected(QListBoxItem*);
    virtual void listBox1_doubleClicked(QListBoxItem*);
    virtual void listBox1_clicked(QListBoxItem*);
    virtual void addButton_clicked();
    virtual void modifyButton_clicked();
    virtual void removeButton_clicked();
    virtual void addNewCommand();

protected:
    QGridLayout* CommandDescrDlgLayout;
    QStringList commandlist;
    QString descrFile;

protected slots:
    virtual void languageChange();
    bool loadInfo(QString );

private:
    void loadDescription();
    int editState;		//0 if add new command, 1 if modify an existing one

};

#endif // COMDESCRDLG_H
