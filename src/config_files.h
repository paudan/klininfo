/***************************************************************************
                          config_files.h  -  description
                             -------------------
    begin                : Kt Lie 15 17:11:30 2004
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

#ifndef FILESCONFIG_H
#define FILESCONFIG_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class KLineEdit;
class QToolButton;
class QPushButton;

class FilesConfig : public QWidget
{
    Q_OBJECT

public:
    FilesConfig( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~FilesConfig();

    QLabel* textLabel2;
    QLabel* textLabel1;
    KLineEdit* kLineEdit1;
    QToolButton* toolButton1;
    QPushButton* pushButton1;
    QLabel* textLabel3;
    KLineEdit* kLineEdit2;
    QLabel* textLabel4;
    KLineEdit* kLineEdit3;
    QToolButton* toolButton3;
    QPushButton* pushButton3;
    QLabel* textLabel1_2;
    KLineEdit* kLineEdit4;
    QToolButton* toolButton4;
    QPushButton* pushButton4;
    QPushButton* pushButton2;
    QToolButton* toolButton2;

public slots:
    virtual void commandButton_clicked();
    virtual void systemButton_clicked();
    virtual void logButton_clicked();
    virtual void varsionButton_clicked();

public:
    void editFile(QString , QString );

protected:
    QGridLayout* FilesConfigLayout;

protected slots:
    virtual void languageChange();

};

#endif // FILESCONFIG_H
