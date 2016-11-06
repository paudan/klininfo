/***************************************************************************
                          splashscreen.h  -  description
                             -------------------
    begin                : Sat Feb 28 2004
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

#ifndef __SPLASHSCREEN_H__
#define __SPLASHSCREEN_H__

#include <qobject.h>
#include <qwidget.h>
class QWidget;
class QLabel;

class SplashScreen : public QWidget
{
 Q_OBJECT

 public:

  SplashScreen();
  ~SplashScreen();

  public slots:

  void showMessage(const QString &message);

  private:

  QWidget *m_splash;
  QLabel  *m_message;

  void setTextPalette();

};

#endif
