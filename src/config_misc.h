/***************************************************************************
                          config_misc.h  -  description
                             -------------------
    begin                : Št Lie 17 13:34:14 2004
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

#ifndef MISCCONFIG_H
#define MISCCONFIG_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QLabel;
class QCheckBox;
class KLineEdit;

class MiscConfig : public QWidget
{
    Q_OBJECT

public:
    MiscConfig( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~MiscConfig();

    QLabel* textLabel1;
    QCheckBox* checkBox1;
    QLabel* textLabel2;
    KLineEdit* kLineEdit1;
    QLabel* textLabel3;
    KLineEdit* kLineEdit2;

protected:
    QGridLayout* MiscConfigLayout;

protected slots:
    virtual void languageChange();

};

#endif // MISCCONFIG_H
