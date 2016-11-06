/***************************************************************************
                          splashscreen.cpp  -  description
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

//-------------------QT includes------------
#include <qlayout.h>
#include <qpixmap.h>
#include <qlabel.h>
#include <qimage.h>
#include <qapplication.h>

//------------------KDE includes------------
#include <kapp.h>
#include <kdebug.h>
#include <kstddirs.h>
#include <kapplication.h>
#include <kglobalsettings.h>
#include <kmainwindow.h>
#include "splashscreen.h"


void SplashScreen::setTextPalette()
{
    QPixmap image;
    image.load(locate("appdata", "pixmaps/bottomline.jpg") );
    QPalette pal;
    QColorGroup cg;
    cg.setColor( QColorGroup::Foreground, white );
    cg.setColor( QColorGroup::Button, QColor( 220, 220, 220) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, QColor( 237, 237, 237) );
    cg.setColor( QColorGroup::Dark, QColor( 110, 110, 110) );
    cg.setColor( QColorGroup::Mid, QColor( 146, 146, 146) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setBrush( QColorGroup::Background, QBrush( QColor( 220, 220, 220), image) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 84, 112, 152) );
    cg.setColor( QColorGroup::HighlightedText, white );
    pal.setActive( cg );
    cg.setColor( QColorGroup::Foreground, white );
    cg.setColor( QColorGroup::Button, QColor( 220, 220, 220) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, QColor( 253, 253, 253) );
    cg.setColor( QColorGroup::Dark, QColor( 110, 110, 110) );
    cg.setColor( QColorGroup::Mid, QColor( 146, 146, 146) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setBrush( QColorGroup::Background, QBrush( QColor( 220, 220, 220), image) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 84, 112, 152) );
    cg.setColor( QColorGroup::HighlightedText, white );
    pal.setInactive( cg );
    cg.setColor( QColorGroup::Foreground, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Button, QColor( 220, 220, 220) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, QColor( 253, 253, 253) );
    cg.setColor( QColorGroup::Dark, QColor( 110, 110, 110) );
    cg.setColor( QColorGroup::Mid, QColor( 146, 146, 146) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Base, white );
    cg.setBrush( QColorGroup::Background, QBrush( QColor( 220, 220, 220), image) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 84, 112, 152) );
    cg.setColor( QColorGroup::HighlightedText, white );
    pal.setDisabled( cg );
    m_message->setPalette( pal );
}

SplashScreen::SplashScreen() : QWidget()
{
  m_splash = new QWidget( 0, "splash", WStyle_NoBorder | WStyle_Customize |
WStyle_StaysOnTop /*| WX11BypassWM */);
  QVBoxLayout *vbox = new QVBoxLayout(m_splash);
  QLabel *pixmap = new QLabel(m_splash);
  QPixmap pm;
  pm.load(locate("appdata", "pixmaps/splash_top.jpg") );
  pixmap->setPixmap(pm);
  vbox->addWidget(pixmap);

  m_message = new QLabel(m_splash);
  vbox->addWidget(m_message);
  setTextPalette();

  QRect rect = QApplication::desktop()->screenGeometry(QApplication::desktop()->screenNumber(QPoint(0,0)));
   m_splash->move(rect.x() + (rect.width() - m_splash->sizeHint().width()) / 2,
           rect.y() + (rect.height() - m_splash->sizeHint().height()) / 2);
   m_splash->setFixedSize(m_splash->sizeHint());

   m_splash->show();
   m_splash->repaint( false );
   QApplication::flushX();
}

SplashScreen::~SplashScreen()
{
  delete m_splash;
}

void SplashScreen::showMessage(const QString &message)
{
  m_message->setText(" " + message);
  kapp->processEvents();
}

#include "splashscreen.moc"