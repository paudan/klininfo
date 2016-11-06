/***************************************************************************
                          pkginfodlg.cpp  -  description
                             -------------------
    begin                : Pn Lie 2 23:40:38 2004
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

#include "pkginfodlg.h"


#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qtable.h>
#include <qtabwidget.h>
#include <qtextbrowser.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qregexp.h>

#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

/*
 *  Constructs a pkgInfoDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
pkgInfoDlg::pkgInfoDlg( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "pkgInfoDlg" );
    pkgInfoDlgLayout = new QVBoxLayout( this, 11, 6, "pkgInfoDlgLayout"); 

    textLabel1 = new QLabel( this, "textLabel1" );
    pkgInfoDlgLayout->addWidget( textLabel1 );

    table1 = new QTable( this, "table1" );
    table1->setNumRows( packageCount() );
    table1->setNumCols( 4 );
    table1->setLeftMargin( 0 );
    table1->verticalHeader()->hide();
    table1->horizontalHeader()->resizeSection(0, int (table1->width() / 3) );
    table1->horizontalHeader()->resizeSection(1, int (table1->width() / 5 + 10) );
    table1->horizontalHeader()->resizeSection(2, int (table1->width() / 5 + 10) );
    table1->horizontalHeader()->resizeSection(3, int (table1->width() / 3) );
    table1->horizontalHeader()->setLabel( 0, tr( "Package name" ) );
    table1->horizontalHeader()->setLabel( 1, tr( "Compressed package size" ) );
    table1->horizontalHeader()->setLabel( 2, tr( "Uncompressed package size" ) );
    table1->horizontalHeader()->setLabel( 3, tr( "Full package name" ) );
    pkgInfoDlgLayout->addWidget( table1 );

    tabWidget2 = new QTabWidget( this, "tabWidget2" );

    tab = new QWidget( tabWidget2, "tab" );
    tabLayout = new QVBoxLayout( tab, 11, 6, "tabLayout"); 

    textBrowser1 = new QTextBrowser( tab, "textBrowser1" );
    tabLayout->addWidget( textBrowser1 );
    tabWidget2->insertTab( tab, QString("") );

    tab_2 = new QWidget( tabWidget2, "tab_2" );
    tabLayout_2 = new QVBoxLayout( tab_2, 11, 6, "tabLayout_2"); 

    textBrowser2 = new QTextBrowser( tab_2, "textBrowser2" );
    tabLayout_2->addWidget( textBrowser2 );
    tabWidget2->insertTab( tab_2, QString("") );
    pkgInfoDlgLayout->addWidget( tabWidget2 );
    languageChange();
    resize( QSize(600, 482).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    connect( table1, SIGNAL( clicked(int,int,int,const QPoint&) ),
                 this, SLOT( showPackageInfo(int, int, int, const QPoint& ) ) );
    connect( table1, SIGNAL( doubleClicked(int,int,int,const QPoint&) ),
                 this, SLOT( showPackageInfo(int, int, int , const QPoint& ) ) );
    connect(table1->horizontalHeader(), SIGNAL(clicked(int ) ), this, SLOT(doSortColumn(int ) ) );
    
    errorMsg = tr("Package information successfully loaded.");
    loadPackageList();
}

/*
 *  Destroys the object and frees any allocated resources
 */
pkgInfoDlg::~pkgInfoDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void pkgInfoDlg::languageChange()
{
    setCaption( tr( "Package Information Dialog" ) );
    textLabel1->setText( tr( "Packages, installed in this Linux system:" ) );
    tabWidget2->changeTab( tab, tr( "Package information" ) );
    tabWidget2->changeTab( tab_2, tr( "Package files" ) );
}

void pkgInfoDlg::loadPackageList()
{
  int rowCount = -1;

  if (!genPKGInfoFile() ) errorMsg = tr("Could not retrieve package information");
  else {
       QFile pkgFile("/tmp/pkginfo.txt");
       if (pkgFile.open(IO_ReadOnly) ) {
         QTextStream rd(&pkgFile);
	 while (!pkgFile.atEnd() ) {
           ++rowCount;
	   QTableItem* tblitem1 = new QTableItem(table1, QTableItem::Never, rd.readLine());
           table1->setItem(rowCount, 0, tblitem1);
	   QTableItem* tblitem2 = new QTableItem(table1, QTableItem::Never, rd.readLine());
	   table1->setItem(rowCount, 1, tblitem2);
	   QTableItem* tblitem3 = new QTableItem(table1, QTableItem::Never, rd.readLine());
	   table1->setItem(rowCount, 2, tblitem3);
	   QTableItem* tblitem4 = new QTableItem(table1, QTableItem::Never, rd.readLine().section("/", -1));
	   table1->setItem(rowCount, 3, tblitem4);

        }
        pkgFile.close();
	pkgFile.remove();
     }
  }
}

int pkgInfoDlg::packageCount()
{
  DIR *dp;
  struct dirent *ep;

  int count = 0;

  dp = opendir (PACKAGE_INFO_DIR);
  if (dp != NULL) {
      ep = readdir(dp);  	//Skip .
      ep = readdir(dp);		//Skip ..
      while (ep = readdir (dp)) count++;
    }
  else errorMsg = tr("Could not retrieve package information");
  return count;
}

bool pkgInfoDlg::genPKGInfoFile()
{
  /*A simple bash script that collects all the necessary info from package dir,
    is defined here:

  #!/bin/bash

  PACKAGE_INFO_DIR=/var/log/packages/*

  for x in $PACKAGE_INFO_DIR
  do
    head $x -n 4 | awk 'BEGIN { FS =": " } { print $2 }' >> /tmp/pkginfo.txt
  done

  This script puts all the necessary package info to a temporary file /tmp/pkginfo.txt,
  which contents can be easily read
  */

  QString scripttxt =
  QString("#!/bin/bash\n\n") +
  QString("PACKAGE_INFO_DIR=") + PACKAGE_INFO_DIR + QString("/*\n\n") +
  QString("for x in $PACKAGE_INFO_DIR\n") +
  QString("do\n") +
  QString("head $x -n 4 | awk 'BEGIN { FS =\": \" } { print $2 }' >> /tmp/pkginfo.txt\n") +
  QString("done\n");

   QFile script("/tmp/collectinfo");
   if (script.open(IO_WriteOnly)) {
     QTextStream wr(&script);
     wr << scripttxt;
     script.close();
   }
   chmod("/tmp/collectinfo", S_IRWXU | S_IRWXO);
   system("/tmp/collectinfo");
   unlink("/tmp/collectinfo");
   QFile genfile("/tmp/pkginfo.txt");
   if (genfile.exists() && genfile.size() > 0) return true;
   else return false;
}

void pkgInfoDlg::showPackageInfo(int , int , int, const QPoint& )
{
  QString tmp;
  textBrowser1->setText("");
  textBrowser2->setText("");
  QFile f( QString(PACKAGE_INFO_DIR) + QString("/") + table1->text(table1->currentRow(), 0).stripWhiteSpace() );
  if (f.open(IO_ReadOnly) ) {
     QTextStream rd(&f);
     while (!f.atEnd() ) {
       tmp = rd.readLine();
       if (tmp.contains("PACKAGE DESCRIPTION:") >= 1)
       while (!tmp.contains("FILE LIST:") ) {
         tmp = rd.readLine();
	 textBrowser1->setText(textBrowser1->text() + tmp.section(":", 1) + "\n");
       }
       if (tmp.contains("FILE LIST:") == 1) {
          tmp = rd.readLine();
          while (!f.atEnd() )
	     textBrowser2->setText(textBrowser2->text() + rd.readLine() + "\n");
       }
       }
       f.close();
   }
 }
 
void pkgInfoDlg::doSortColumn(int which)
{
  table1->sortColumn(which, TRUE, TRUE);
} 

#include "pkginfodlg.moc"
