/***************************************************************************
                          dudlg.cpp  -  description
                             -------------------
    begin                : Tr Lie 7 23:51:00 2004
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

#include "dudlg.h"


#include <qvariant.h>
#include <qtable.h>
#include <qlabel.h>
#include <kcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qtextstream.h>
#include <qfile.h>
#include <kprogress.h>
#include <kprocess.h>
#include <kmessagebox.h>

/*
 *  Constructs a DiskUsageDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
DiskUsageDlg::DiskUsageDlg( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "DiskUsageDlg" );
    DiskUsageDlgLayout = new QGridLayout( this, 1, 1, 11, 6, "DiskUsageDlgLayout"); 

    table1 = new QTable( this, "table1" );
    table1->setNumRows( 0 );
    table1->setNumCols( 7 );
    table1->setShowGrid( FALSE );
    table1->setLeftMargin( 0 );
    table1->verticalHeader()->hide();
    table1->horizontalHeader()->setLabel( 0, tr("Drive") );
    table1->horizontalHeader()->setLabel( 1, tr("FS type") );
    table1->horizontalHeader()->setLabel( 2, tr("Mounting point") );
    table1->horizontalHeader()->setLabel( 3, tr("Blocks") );
    table1->horizontalHeader()->setLabel( 4, tr("Used") );
    table1->horizontalHeader()->setLabel( 5, tr("Free") );
    table1->horizontalHeader()->setLabel( 6, tr("%") );
    table1->horizontalHeader()->resizeSection(1, 100 );
    table1->horizontalHeader()->resizeSection(6, 200 );

    DiskUsageDlgLayout->addMultiCellWidget( table1, 1, 1, 0, 2 );

    textLabel1 = new QLabel( this, "textLabel1" );

    DiskUsageDlgLayout->addWidget( textLabel1, 0, 0 );

    kComboBox1 = new KComboBox( FALSE, this, "kComboBox1" );

    DiskUsageDlgLayout->addWidget( kComboBox1, 0, 1 );
    QSpacerItem* spacer = new QSpacerItem( 100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    DiskUsageDlgLayout->addItem( spacer, 0, 2 );
    languageChange();
    resize( QSize(600, 482).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( kComboBox1, SIGNAL( activated(int) ), this, SLOT( dispSelected(int) ) );

    bufout = "";
    process = new KProcess();
    dispSelected(3);
}

/*
 *  Destroys the object and frees any allocated resources
 */
DiskUsageDlg::~DiskUsageDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void DiskUsageDlg::languageChange()
{
    setCaption( tr( "Disk Usage Dialog" ) );
    textLabel1->setText( tr( "Display in:" ) );
    kComboBox1->clear();
    kComboBox1->insertItem( tr( "Kilobytes (kB), blocksize = 1 000" ) );
    kComboBox1->insertItem( tr( "Kilobytes (K), blocksize = 1 024" ) );
    kComboBox1->insertItem( tr( "Megabytes (mB), blocksize = 1 000 000" ) );
    kComboBox1->insertItem( tr( "Megabytes (M), blocksize = 1 048 576" ) );
    kComboBox1->insertItem( tr( "Gigabytes (gB), blocksize = 1 000 000 000" ) );
    kComboBox1->insertItem( tr( "Gigabytes (G), blocksize = 1 073 741 824" ) );
    kComboBox1->insertItem( tr( "Terabytes (tB), blocksize = 1 000 000 000 000" ) );
    kComboBox1->insertItem( tr( "Terabytes (T), blocksize = 1 099 511 627 776" ) );
    kComboBox1->insertItem( tr( "Easy readable" ) );
}

void DiskUsageDlg::dispSelected(int type_id)
{
    if (type_id == 0 ) 		runDU("kB");
    else if (type_id == 1)	runDU("K");
    else if (type_id == 2)	runDU("mB");
    else if (type_id == 3)	runDU("M");
    else if (type_id == 4)	runDU("gB");
    else if (type_id == 5)	runDU("G");
    else if (type_id == 6)	runDU("tB");
    else if (type_id == 7) 	runDU("T");
    else if (type_id == 8)	runDU();
}

void DiskUsageDlg::runDU(const char *sizeparam)
{
  process->clearArguments();
  (*process) << DF_CMD << DF_ARGS << sizeparam;
  connect(process, SIGNAL(receivedStdout(KProcess*, char*, int) ), this, SLOT(receivedOutput(KProcess *, char *, int)) );
  connect(process, SIGNAL(processExited(KProcess*, char*, int) ), this, SLOT(receivedOutput(KProcess *, char *, int)) );
  if ( !process->start(KProcess::NotifyOnExit, KProcess::AllOutput) )
        KMessageBox::error( this, tr("Fatal error. Disk usage information could not be retrieved"), QString("KLinInfo v0.2"), KMessageBox::Notify);

}

void DiskUsageDlg::runDU()
{
  process->clearArguments();
  (*process) << DF_CMD << DF_HUMAN_READ;
  connect(process, SIGNAL(receivedStdout(KProcess*, char*, int) ), this, SLOT(receivedOutput(KProcess *, char *, int)) );
   connect(process, SIGNAL(processExited(KProcess*, char*, int) ), this, SLOT(receivedOutput(KProcess *, char *, int)) );
  if ( !process->start(KProcess::NotifyOnExit, KProcess::AllOutput) )
        KMessageBox::error( this, tr("Fatal error. Disk usage information could not be retrieved") , QString("KLinInfo v0.2"), KMessageBox::Notify);
}

void DiskUsageDlg::receivedOutput(KProcess *, char buffer[], int length)
{
  bufout.append(QCString(buffer, length + 1));
  displayData();
}

void DiskUsageDlg::displayData()
{
  QString copybuf = bufout;
  QTextStream rd(&bufout, IO_ReadOnly);
  QString readl;
  int rowCount = -1, number = -1;
  readl = rd.readLine();
  while (!rd.atEnd() ) {
     readl = rd.readLine();
     ++number;
  }
  table1->setNumRows(number+1);
  QTextStream rdf(&copybuf, IO_ReadOnly);
  readl = rdf.readLine();	//Skip the first row (the header of du command)
  while (!rdf.atEnd() ) {
     	   readl = rdf.readLine();
     	   ++rowCount;
	   table1->setText(rowCount, 0, readl.section(" ", 0, 0, QString::SectionSkipEmpty) );
     	   table1->setText(rowCount, 1, readl.section(" ", 1, 1, QString::SectionSkipEmpty) );
	   table1->setText(rowCount, 2, readl.section(" ", 6, 6, QString::SectionSkipEmpty) );
	   table1->setText(rowCount, 3, readl.section(" ", 2, 2, QString::SectionSkipEmpty) );
	   table1->setText(rowCount, 4, readl.section(" ", 3, 3, QString::SectionSkipEmpty) );
	   table1->setText(rowCount, 5, readl.section(" ", 4, 4, QString::SectionSkipEmpty) );
	   QString percent = readl.section(" ", 5, 5, QString::SectionSkipEmpty);
	   if (percent != "-") {
	      KProgress *prg = new KProgress(this, "prg", 0);
	      int percentage = percent.left(percent.length()-1).toInt();
	      prg->setProgress(percentage);
	      if (percentage > LIMIT_FULL) prg->setPalette(progressRed() );
	      if (percentage == 100 && table1->text(rowCount, 1).stripWhiteSpace() == "iso9660") prg->setPalette(progressGrey() );
	      table1->setCellWidget(rowCount, 6, prg);
	   }
 }
 bufout = "";
}

QPalette DiskUsageDlg::progressRed()
{
    QPalette pal;
    QColorGroup cg;
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 228, 228, 228) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, QColor( 241, 241, 241) );
    cg.setColor( QColorGroup::Dark, QColor( 114, 114, 114) );
    cg.setColor( QColorGroup::Mid, QColor( 152, 152, 152) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 220, 220, 220) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 255, 81, 0) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 192) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 128, 0, 128) );
    pal.setActive( cg );
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 228, 228, 228) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, white );
    cg.setColor( QColorGroup::Dark, QColor( 114, 114, 114) );
    cg.setColor( QColorGroup::Mid, QColor( 152, 152, 152) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 220, 220, 220) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 255, 81, 0) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 192) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 128, 0, 128) );
    pal.setInactive( cg );
    cg.setColor( QColorGroup::Foreground, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Button, QColor( 228, 228, 228) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, white );
    cg.setColor( QColorGroup::Dark, QColor( 114, 114, 114) );
    cg.setColor( QColorGroup::Mid, QColor( 152, 152, 152) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 220, 220, 220) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 255, 81, 0) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 192) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 128, 0, 128) );
    pal.setDisabled( cg );
    return pal;
}

QPalette DiskUsageDlg::progressGrey()
{
    QPalette pal;
    QColorGroup cg;
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 228, 228, 228) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, QColor( 241, 241, 241) );
    cg.setColor( QColorGroup::Dark, QColor( 114, 114, 114) );
    cg.setColor( QColorGroup::Mid, QColor( 152, 152, 152) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 220, 220, 220) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 190, 190, 190) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 192) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 128, 0, 128) );
    pal.setActive( cg );
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 228, 228, 228) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, white );
    cg.setColor( QColorGroup::Dark, QColor( 114, 114, 114) );
    cg.setColor( QColorGroup::Mid, QColor( 152, 152, 152) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 220, 220, 220) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 190, 190, 190) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 192) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 128, 0, 128) );
    pal.setInactive( cg );
    cg.setColor( QColorGroup::Foreground, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Button, QColor( 228, 228, 228) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, white );
    cg.setColor( QColorGroup::Dark, QColor( 114, 114, 114) );
    cg.setColor( QColorGroup::Mid, QColor( 152, 152, 152) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, white );
    cg.setColor( QColorGroup::ButtonText, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 220, 220, 220) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 190, 190, 190) );
    cg.setColor( QColorGroup::HighlightedText, white );
    cg.setColor( QColorGroup::Link, QColor( 0, 0, 192) );
    cg.setColor( QColorGroup::LinkVisited, QColor( 128, 0, 128) );
    pal.setDisabled( cg );
    return pal;
}

void DiskUsageDlg::saveToFile(QString filename, int flags)
{
   QFile f(filename);
   if (!f.open(flags) ) return;
   QTextStream stream(&f);
   stream << "<html>" << "<head>";
   stream << "<title align=\"center\">" << tr("Disk usage information") << "</title>";
   stream << "</head>";
   stream << "<body>";
   stream << "<h1 align=\"center\">" << tr("Disk usage information") << "</h1>";
   stream << "<table border=\"2\">"<< "<thead>" << "<tr>";
   for (int i = 0; i < table1->horizontalHeader()->count(); i++)
      stream << "<th scope=col>" << table1->horizontalHeader()->label(i) << "</th>";
   stream << "</tr>" << "</thead>";
   stream << "<tbody>";
   for (int i = 0; i < table1->numRows(); i++) {
      stream << "<tr>";
      for (int j = 0; j < table1->numCols() - 1; j++)
         stream << "<td>" << table1->text(i, j) << "</td>";
      if (table1->text(i, table1->numCols() - 3).left(table1->text(i, table1->numCols() - 4).length() - 1).toDouble() == 0) stream << "<td>" << "";
      else stream << "<td>" << (int)((table1->text(i, table1->numCols() - 3).left(table1->text(i, table1->numCols() - 3).length() - 1).toDouble() ) /
      (table1->text(i, table1->numCols() - 4).left(table1->text(i, table1->numCols() - 4).length() - 1).toDouble() )* 100) << "%" << "</td>";
      stream << "</tr>";
   }
   stream << "</tbody>" << "</table>";
   f.close();
}

#include "dudlg.moc"
