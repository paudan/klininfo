/***************************************************************************
                          config_font.h  -  description
                             -------------------
    begin                : Kt Lie 15 17:11:04 2004
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

#ifndef FONTCONFIG_H
#define FONTCONFIG_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class KFontChooser;
class QLabel;
class KComboBox;

class FontConfig : public QWidget
{
    Q_OBJECT

public:
    FontConfig( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~FontConfig();

    QLabel* textLabel1;
    KFontChooser* kFontDialog;
    KComboBox* kComboBox1;

    int curTypeWidget;
    QFont curWidgetFont;
    QFont fsettings[4];

protected:
    QGridLayout* FontConfigLayout;

protected slots:
    virtual void languageChange();
    virtual void saveFontInfo();
    virtual void FontChange();

private:

};

#endif // FONTCONFIG_H
