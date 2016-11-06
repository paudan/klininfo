/***************************************************************************
                          fontdlg.cpp  -  description
                             -------------------
    begin                : Pn Bir 25 18:42:19 2004
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

#include "fontdlg.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <klistbox.h>
#include <klineedit.h>

#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qstringlist.h>
#include <qvaluelist.h>
#include <qfontmetrics.h>
#include <qfontdatabase.h>
#include <kfontdialog.h>

/*
 *  Constructs a FontPreviewDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
FontPreviewDlg::FontPreviewDlg( QWidget* parent, const char* name, WFlags fl, int mode ) : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "FontPreviewDlg" );

    FontPreviewDlgLayout = new QGridLayout( this, 1, 1, 11, 6, "FontPreviewDlgLayout");

    textLabel2_2 = new QLabel( this, "textLabel2_2" );

    FontPreviewDlgLayout->addWidget( textLabel2_2, 1, 2 );

    comboBox1_2 = new QComboBox( FALSE, this, "comboBox1_2" );

    FontPreviewDlgLayout->addMultiCellWidget( comboBox1_2, 2, 2, 2, 3 );

    textLabel2 = new QLabel( this, "textLabel2" );

    FontPreviewDlgLayout->addWidget( textLabel2, 1, 0 );

    comboBox1 = new QComboBox( FALSE, this, "comboBox1" );

    FontPreviewDlgLayout->addMultiCellWidget( comboBox1, 2, 2, 0, 1 );

    listBox1 = new KListBox( this, "listBox1" );

    FontPreviewDlgLayout->addMultiCellWidget( listBox1, 1, 2, 4, 4 );

    dlg_title = new QLabel( this, "textLabel1" );

    FontPreviewDlgLayout->addMultiCellWidget( dlg_title, 0, 0, 0, 6 );

    kLineEdit1 = new KLineEdit( this, "kLineEdit1" );
    kLineEdit1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, kLineEdit1->sizePolicy().hasHeightForWidth() ) );
    kLineEdit1->setAlignment( int( KLineEdit::AlignAuto ) );
    kLineEdit1->setText("This is an example");

    FontPreviewDlgLayout->addMultiCellWidget( kLineEdit1, 3, 3, 0, 4 );
    QSpacerItem* spacer = new QSpacerItem( 20, 61, QSizePolicy::Minimum, QSizePolicy::Fixed );
    FontPreviewDlgLayout->addMultiCell( spacer, 1, 2, 3, 3 );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed );
    FontPreviewDlgLayout->addItem( spacer_2, 1, 2 );
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 61, QSizePolicy::Minimum, QSizePolicy::Fixed );
    FontPreviewDlgLayout->addMultiCell( spacer_3, 1, 2, 1, 1 );
    QSpacerItem* spacer_4 = new QSpacerItem( 20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed );
    FontPreviewDlgLayout->addItem( spacer_4, 1, 0 );
    languageChange();
    resize( QSize(466, 444).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    loadFontInfo(mode);
}

/*
 *  Destroys the object and frees any allocated resources
 */
FontPreviewDlg::~FontPreviewDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FontPreviewDlg::languageChange()
{
    setCaption( tr( "Font Preview" ) );
    textLabel2_2->setText( tr( "Font size:" ) );
    textLabel2->setText( tr( "Font style:" ) );
    listBox1->clear();
    dlg_title->setText( tr( "Fonts, found in your Linux system:" ) );
}

void FontPreviewDlg::loadFontInfo(int mode)
{
   if (mode == 0) {
     listBox1->clear();
     QFontDatabase *fdb= new QFontDatabase();
     QStringList flist = fdb->families();
     for ( QStringList::Iterator it = flist.begin(); it != flist.end(); ++it )
        listBox1->insertItem(QString(*it));
   }
   else if (mode == 1) {
     listBox1->clear();
     QStringList flist;
     KFontChooser *fchooser = new KFontChooser(this, "font", false, QStringList(), false, 6 );
     fchooser->getFontList(flist, false);
     for ( QStringList::Iterator it = flist.begin(); it != flist.end(); ++it )
         listBox1->insertItem(QString(*it));
   }

}

void FontPreviewDlg::fontSelected()
{
  QString curfont = listBox1->currentText(),
          printNr;
  QFontDatabase *fntlist = new QFontDatabase();
  typedef QValueList<int> intList;
  QValueList<int> sizelist = fntlist->pointSizes(curfont);
  comboBox1_2->clear();
  comboBox1->clear();
  for ( QValueList<int>::Iterator it = sizelist.begin(); it != sizelist.end(); ++it )
     comboBox1_2->insertItem( printNr.setNum((int)*it) );
  QStringList stylelist = fntlist->styles(curfont);
  for ( QStringList::Iterator it = stylelist.begin(); it != stylelist.end(); ++it )
      comboBox1->insertItem(QString(*it));
  kLineEdit1->setFont(QFont(curfont, comboBox1_2->currentText().toInt(), QFont::Normal ) );
}

void FontPreviewDlg::fontSizeChanged(int size)
{
  QFont curfont = kLineEdit1->font();
  curfont.setPointSize(  comboBox1_2->currentText().toInt() );
  kLineEdit1->setFont( curfont );
}

void FontPreviewDlg::fontStyleChanged(int style_num)
{
   QString style = comboBox1->currentText().lower();
   if (style == "normal" || style == "normal")
      kLineEdit1->setFont(QFont(listBox1->currentText(), comboBox1_2->currentText().toInt(), QFont::Normal ) );
   else if (style == "bold")
      kLineEdit1->setFont(QFont(listBox1->currentText(), comboBox1_2->currentText().toInt(), QFont::Bold ) );
   else if (style == "italic" || style == "regular italic")
      kLineEdit1->setFont(QFont(listBox1->currentText(), comboBox1_2->currentText().toInt(), QFont::Normal, true) );
   else if (style == "bold italic")
      kLineEdit1->setFont(QFont(listBox1->currentText(), comboBox1_2->currentText().toInt(), QFont::Bold, true ) );
   else if (style == "light")
      kLineEdit1->setFont(QFont(listBox1->currentText(), comboBox1_2->currentText().toInt(), QFont::Light) );
   else if (style == "light italic")
      kLineEdit1->setFont(QFont(listBox1->currentText(), comboBox1_2->currentText().toInt(), QFont::Light, true ) );
   else if (style == "demi bold" || style == "demibold")
      kLineEdit1->setFont(QFont(listBox1->currentText(), comboBox1_2->currentText().toInt(), QFont::DemiBold) );
   else if (style == "demi bold italic" || style == "demibold italic")
      kLineEdit1->setFont(QFont(listBox1->currentText(), comboBox1_2->currentText().toInt(), QFont::DemiBold, true ) );
            // Not supported by Qt 3.2.1
   else if (style == "oblique" || style == "bold oblique" || style == "book" ||
            style == "book oblique" || "demi bold oblique" || style == "demibold oblique") ;
}

void FontPreviewDlg::saveToFile(QString filename, int flags)
{
  QFile f(filename);
   if (!f.open(flags) ) return;
   QTextStream stream(&f);
   stream << "<html>" << "<head>";
   stream << "<title align=\"center\">" << tr("TTF Font list") << "</title>";
   stream << "</head>";
   stream << "<body>";
   stream << "<h1 align=\"center\">" << tr("TTF Font list") << "</h1>";
   for (int i = 0; i < listBox1->count(); i++)
        stream << "<font face=\"" << listBox1->text(i) << "\">" << listBox1->text(i) << "</font><br>\n";
   f.close();
}

#include "fontdlg.moc"
