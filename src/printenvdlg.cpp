/***************************************************************************
                          printenvdlg.cpp  -  description
                             -------------------
    begin                : Pr Lie 5 15:54:19 2004
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

#include "printenvdlg.h"


#include <qvariant.h>
#include <qlabel.h>
#include <qtextbrowser.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <stdlib.h>

/*
 *  Constructs a PrintEnvDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
PrintEnvDlg::PrintEnvDlg( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "PrintEnvDlg" );
    PrintEnvDlgLayout = new QVBoxLayout( this, 11, 6, "PrintEnvDlgLayout"); 

    textBrowser1 = new QTextBrowser( this, "textBrowser1" );
    PrintEnvDlgLayout->addWidget( textBrowser1 );
    languageChange();
    resize( QSize(600, 482).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    loadPEString();
}

/*
 *  Destroys the object and frees any allocated resources
 */
PrintEnvDlg::~PrintEnvDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void PrintEnvDlg::languageChange()
{
    setCaption( tr( "printenv Dialog" ) );
}

void PrintEnvDlg::loadPEString()
{
 textBrowser1->setText(tr( "<p><b>The output of <i>printenv</i> command</b></p>" ));
 extern char **environ;
 register char **ep;
 for (ep = environ; *ep; ep++)
    textBrowser1->setText(textBrowser1->text() + QString(*ep) + "<br>");
}

void PrintEnvDlg::saveToFile(QString filename, int flags)
{
   QFile f(filename);
   if (!f.open(flags) ) return;
   QTextStream stream(&f);
   stream << "<html>" << "<head>";
   stream << "<title align=\"center\">" << tr("printenv information") << "</title>";
   stream << "</head>";
   stream << "<body>";
   stream << "<h1 align=\"center\">" << tr("printenv information") << "</h1>";
   stream << textBrowser1->text();
   f.close();
}

#include "printenvdlg.moc"
