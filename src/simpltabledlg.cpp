/***************************************************************************
                          simpltabledlg.cpp  -  description
                             -------------------
    begin                : Kt Lie 1 14:49:06 2004
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

#include "simpltabledlg.h"


#include <qvariant.h>
#include <qlabel.h>
#include <qtable.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <stdio.h>

/*
 *  Constructs a VersionInfoDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
VersionInfoDlg::VersionInfoDlg( QWidget* parent, const char* name, WFlags fl, QString versionFile)
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "VersionInfoDlg" );
    VersionInfoDlgLayout = new QVBoxLayout( this, 11, 6, "VersionInfoDlgLayout");

    dlg_title = new QLabel( this, "dlg_title" );
    VersionInfoDlgLayout->addWidget( dlg_title );

    table1 = new QTable( this, "table1" );
    table1->setResizePolicy( QTable::AutoOneFit );
    table1->setNumCols( 2 );
    table1->setNumRows( 20 );
    table1->setLeftMargin( 0 );
    table1->verticalHeader()->hide();
    table1->horizontalHeader()->setLabel( 0, tr( "Program (command) name" ) );
    table1->horizontalHeader()->setLabel( 1, tr( "Version" ) );
    table1->horizontalHeader()->resizeSection(0, int (table1->width() / 2 - 10) );
    table1->horizontalHeader()->resizeSection(1, int (table1->width() / 2 - 10) );
    table1->horizontalHeader()->setResizeEnabled(true);
    table1->setReadOnly( TRUE );
    VersionInfoDlgLayout->addWidget( table1 );
    connect(table1->horizontalHeader(), SIGNAL(clicked(int ) ), this, SLOT(doSortColumn(int ) ) );
    languageChange();
    resize( QSize(600, 482).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
    table1->setNumRows( getLineCount(versionFile) );
    readVersionFile(versionFile);  
}

/*
 *  Destroys the object and frees any allocated resources
 */
VersionInfoDlg::~VersionInfoDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void VersionInfoDlg::languageChange()
{
    setCaption( tr( "Simple Table Dialog" ) );
    dlg_title->setText( tr( "Programs, installed in this Linux system, and their versions:" ) );
}


void VersionInfoDlg::readVersionFile(QString versFile)
{
  QFile f(versFile);
  QString line;
  QString version;
  int i = 0;
  
  if (!f.exists()) errorMsg = tr("File with filenames does not exist or could not be loaded");
  else {
    if (f.open(IO_ReadOnly) )   {
       QTextStream stream(&f);
       while (!f.atEnd() ) 
       {
         line = stream.readLine();
         if (line.isEmpty() || line.left (1) == "#") ;
         else {
	    version = getVersion(line);
	    table1->setText(i, 0, line.left(line.find(" ")));
            table1->setText(i++, 1, (version) ? version : "N/A");
	 }
	}
	f.close();
  }
  else errorMsg = tr("Error loading version file");
  }	   
}

QString VersionInfoDlg::getVersion(QString cmname)
{
  #define BUFSIZE 1024
  
  FILE *cmd_stream;
  
  char  cp_cmname[255],
        buf[BUFSIZE], copybuf[BUFSIZE], *p,
       command[255];    
  int p1, p2, p3;	
  bool found = false;
  QString vers;
  
  strcpy(cp_cmname, (const char*)cmname);
  
  sprintf(command, "%s 2>&1", (const char*)cmname);	/*sending everything to stderr*/
  
  cmd_stream = popen(command, "r");
  if (!cmd_stream) fprintf(stderr, "Error running %s\n", cp_cmname);
  while (!feof(cmd_stream) ) {
     fgets(buf, BUFSIZE, cmd_stream);
     strcpy(copybuf, buf);
     p = strtok(copybuf, ", ");
        while (p && !found) {
          if (sscanf(p, "%d.%d", &p1, &p2) || sscanf(p, "%d.%d.%d", &p1, &p2, &p3) ||
              sscanf(p, "v%d.%d", &p1, &p2) || sscanf(p, "v%d.%d.%d", &p1, &p2, &p3))	  
              { if (p[0] == 'v') 
	      {      
                 for (int k = 0; k < strlen(p); k++)  p[k] = p[k+1];
                 p[strlen(p)] = '\0';
                 vers = QString(p); 
	      }
              else vers = QString(p);
              found = true; break; }
          p = strtok(NULL, ", ");
        }
  }
  if (pclose(cmd_stream) != 0) fprintf(stderr, "Error running %s\n", cp_cmname);
  return vers;
}    
  

int VersionInfoDlg::getLineCount(QString filename)
{
  QFile f(filename);
  QTextStream tmp(&f);
  int i = 0;
  QString line;
  if (f.open(IO_ReadOnly) ) {
  while (!tmp.atEnd() ) {
    line = tmp.readLine();
    if (line.left (1) == "#" || line.isEmpty() ) ;		//Skip comments
    else ++i;
  }
  f.close();
  return i;
  }
  else return 0;
}

void VersionInfoDlg::doSortColumn(int which)
{
  table1->sortColumn(which, TRUE, TRUE);
}

#include "simpltabledlg.moc"
