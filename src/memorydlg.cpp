/***************************************************************************
                          memorydlg.cpp  -  description
                             -------------------
    begin                : Pr Lie 12 18:37:44 2004
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

#include "memorydlg.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qtextstream.h>
#include <qpainter.h>
#include <qtimer.h>
#include <kprocess.h>
#include <kmessagebox.h>
#include <qevent.h>


/*
 *  Constructs a MemoryDispDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
MemoryDispDlg::MemoryDispDlg( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "MemoryDispDlg" );
    MemoryDispDlgLayout = new QGridLayout( this, 1, 1, 11, 6, "MemoryDispDlgLayout"); 

    line1 = new QFrame( this, "line1" );
    line1->setFrameShape( QFrame::HLine );
    line1->setFrameShadow( QFrame::Sunken );
    line1->setFrameShape( QFrame::HLine );

    MemoryDispDlgLayout->addMultiCellWidget( line1, 2, 2, 0, 4 );
    QSpacerItem* spacer = new QSpacerItem( 30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    MemoryDispDlgLayout->addItem( spacer, 0, 3 );
    QSpacerItem* spacer_2 = new QSpacerItem( 30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    MemoryDispDlgLayout->addItem( spacer_2, 0, 1 );

    textLabel3 = new QLabel( this, "textLabel3" );
    textLabel3->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, textLabel3->sizePolicy().hasHeightForWidth() ) );
    textLabel3->setMaximumSize( QSize( 32767, 20 ) );
    QFont textLabel3_font(  textLabel3->font() );
    textLabel3_font.setPointSize( 13 );
    textLabel3_font.setBold( TRUE );
    textLabel3->setFont( textLabel3_font ); 

    MemoryDispDlgLayout->addWidget( textLabel3, 1, 4 );

    textLabel2 = new QLabel( this, "textLabel2" );
    textLabel2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, textLabel2->sizePolicy().hasHeightForWidth() ) );
    textLabel2->setMaximumSize( QSize( 32767, 20 ) );
    QFont textLabel2_font(  textLabel2->font() );
    textLabel2_font.setPointSize( 13 );
    textLabel2_font.setBold( TRUE );
    textLabel2->setFont( textLabel2_font ); 

    MemoryDispDlgLayout->addWidget( textLabel2, 1, 2 );

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, textLabel1->sizePolicy().hasHeightForWidth() ) );
    textLabel1->setMaximumSize( QSize( 32767, 20 ) );
    QFont textLabel1_font(  textLabel1->font() );
    textLabel1_font.setPointSize( 13 );
    textLabel1_font.setBold( TRUE );
    textLabel1->setFont( textLabel1_font ); 

    MemoryDispDlgLayout->addWidget( textLabel1, 1, 0 );

    table1 = new QTable( this, "table1" );
    table1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, table1->sizePolicy().hasHeightForWidth() ) );
    table1->setNumRows( 16 );
    table1->setNumCols( 4 );
    table1->setShowGrid( FALSE );
    table1->setReadOnly( TRUE );
    table1->setLeftMargin( 0 );
    table1->verticalHeader()->hide();
    table1->horizontalHeader()->resizeSection(0, 200 );
    table1->horizontalHeader()->setLabel( 0, "" );
    table1->horizontalHeader()->setLabel( 1, "B" );
    table1->horizontalHeader()->setLabel( 2, "KB" );
    table1->horizontalHeader()->setLabel( 3, "MB" );

    MemoryDispDlgLayout->addMultiCellWidget( table1, 3, 3, 0, 4 );

    frame5 = new QFrame( this, "frame5" );
    frame5->setFrameShape( QFrame::NoFrame );

    MemoryDispDlgLayout->addWidget( frame5, 0, 4 );

    frame4 = new QFrame( this, "frame4" );
    frame4->setFrameShape( QFrame::NoFrame );

    MemoryDispDlgLayout->addWidget( frame4, 0, 2 );

    frame3 = new QFrame( this, "frame3" );
    frame3->setMinimumSize( QSize( 0, 220 ) );
    frame3->setFrameShape( QFrame::NoFrame );

    MemoryDispDlgLayout->addWidget( frame3, 0, 0 );
    languageChange();
    resize( QSize(600, 484).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    QTimer * counter = new QTimer( this );
    connect( counter, SIGNAL(timeout()), this, SLOT(runFree()) );
    counter->start( 2000 );

    bufout = "";
    runFree();
}

/*
 *  Destroys the object and frees any allocated resources
 */
MemoryDispDlg::~MemoryDispDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void MemoryDispDlg::languageChange()
{
    setCaption( tr( "Memory Display Dialog" ) );
    textLabel3->setText( tr( "All memory" ) );
    textLabel2->setText( tr( "Swap memory" ) );
    textLabel1->setText( tr( "Physical memory" ) );
    table1->setText(0, 0, tr("Total physical memory") );
    table1->setText(1, 0, tr("Used physical memory") );
    table1->setText(2, 0, tr("Free physical memory") );
    table1->setText(3, 0, tr("Buffers(-)") );
    table1->setText(4, 0, tr("Cache:") );
    table1->setText(5, 0, tr("\tShared memory") );
    table1->setText(6, 0, tr("\tDisk buffers") );
    table1->setText(7, 0, tr("\tCached memory") );
    table1->setText(9, 0, tr("Total swap memory") );
    table1->setText(10, 0, tr("Used swap memory ") );
    table1->setText(11, 0, tr("Free swap memory") );
    table1->setText(13, 0, tr("Total memory") );
    table1->setText(14, 0, tr("Total memory used") );
    table1->setText(15, 0, tr("Total memory free") );
}

void MemoryDispDlg::runFree()
{
KProcess *process = new KProcess();
process->clearArguments();
  (*process) << FREE_CMD << FREE_ARGS;
  connect(process, SIGNAL(receivedStdout(KProcess*, char*, int) ), this, SLOT(receivedOutput(KProcess *, char *, int)) );
  if ( !process->start(KProcess::NotifyOnExit, KProcess::AllOutput) )
        KMessageBox::error( this, tr("Fatal error. Memory usage information could not be retrieved") , QString("KLinInfo v0.2"), KMessageBox::Notify);
}

void MemoryDispDlg::receivedOutput(KProcess *, char buffer[], int length)
{
  bufout.append(QCString(buffer, length + 1));
  displayData();
  drawGraphs();
}

void MemoryDispDlg::displayData()
{
  QTextStream rdf(&bufout, IO_ReadOnly);
  QString readl;
  readl = rdf.readLine();	//Skip the first row (the header of du command)
  readl = rdf.readLine();
  dispKBMBSizes(readl.section(" ", 1, 1, QString::SectionSkipEmpty), 0);
  dispKBMBSizes(readl.section(" ", 2, 2, QString::SectionSkipEmpty), 1);
  dispKBMBSizes(readl.section(" ", 3, 3, QString::SectionSkipEmpty), 2);
  dispKBMBSizes(readl.section(" ", 4, 4, QString::SectionSkipEmpty), 5);
  dispKBMBSizes(readl.section(" ", 5, 5, QString::SectionSkipEmpty), 6);
  dispKBMBSizes(readl.section(" ", 6, 6, QString::SectionSkipEmpty), 7);
  readl = rdf.readLine();
  dispKBMBSizes(readl.section(" ", 2, 2, QString::SectionSkipEmpty), 3);
  dispKBMBSizes(readl.section(" ", 3, 3, QString::SectionSkipEmpty), 4);
  readl = rdf.readLine();
  dispKBMBSizes(readl.section(" ", 1, 1, QString::SectionSkipEmpty), 9);
  dispKBMBSizes(readl.section(" ", 2, 2, QString::SectionSkipEmpty), 10);
  dispKBMBSizes(readl.section(" ", 3, 3, QString::SectionSkipEmpty), 11);
  readl = rdf.readLine();
  dispKBMBSizes(readl.section(" ", 1, 1, QString::SectionSkipEmpty), 13);
  dispKBMBSizes(readl.section(" ", 2, 2, QString::SectionSkipEmpty), 14);
  dispKBMBSizes(readl.section(" ", 3, 3, QString::SectionSkipEmpty), 15);
  bufout = "";
}

void MemoryDispDlg::dispKBMBSizes(QString line, int whichRow)
{
  QString linecp = line, szval;
  table1->setText(whichRow, 1, line);
  table1->setText(whichRow, 2, szval.setNum( line.toLongLong() /1024) );
  table1->setText(whichRow, 3, szval.sprintf("%5.2f", (double)line.toLongLong() /1024 /1024));
}

void MemoryDispDlg::drawGraphs()
{
		/*paint All memory graph*/
  QPainter p(frame5);
  QPen pen;
  pen.setWidth(1);
  p.setPen(pen);
  p.setBrush(Qt::white);
  p.drawRect(frame5->frameRect() );
  p.setBrush(Qt::red);
  double percent = (table1->text(0, 2).toDouble() - table1->text(2, 2).toDouble() ) / table1->text(13, 2).toDouble() * 100;
  QRect pblock( frame5->frameRect().bottomLeft().x(), (int)(frame5->frameRect().bottomLeft().y() - frame5->frameRect().bottomLeft().y() / 100 * percent), frame5->frameRect().bottomRight().x(), frame5->frameRect().bottomRight().y());
  p.drawRect(pblock );
  p.drawText(pblock, Qt::AlignCenter|Qt::WordBreak, tr("Used physical memory: %1%").arg(percent) );
  p.setBrush(Qt::darkGray);
  double percent_sw = (table1->text(9, 2).toDouble() - table1->text(10, 2).toDouble() ) / table1->text(13, 2).toDouble() * 100;
  QRect pblocks( QPoint(pblock.topLeft().x(), (int)(pblock.topLeft().y() - frame5->frameRect().bottomLeft().y() / 100 * percent_sw)), QSize( frame5->width(),  (int)frame5->frameRect().bottomLeft().y() / 100 * percent_sw));
  p.drawRect(pblocks );
  p.drawText(pblocks, Qt::AlignCenter|Qt::WordBreak, tr("Used swap memory: %1%").arg(percent_sw) );
  p.drawText(frame5->frameRect(), Qt::AlignTop|Qt::AlignHCenter|Qt::WordBreak, tr("Free memory: %1%").arg(100 - percent - percent_sw));

  		/*Paint Physical Memory graph */
  QPainter p3(frame3);
  pen.setWidth(1);
  p3.setPen(pen);
  p3.setBrush(Qt::white);
  p3.drawRect(frame3->frameRect() );
  p3.setBrush(Qt::red);
  double dpercent = (table1->text(0, 2).toDouble() - table1->text(2, 2).toDouble() - table1->text(4, 2).toDouble() ) / table1->text(0, 2).toDouble() * 100;
  QRect pdatablock( frame3->frameRect().bottomLeft().x(), (int)(frame3->frameRect().bottomLeft().y() - frame3->frameRect().bottomLeft().y() / 100 * dpercent), frame3->frameRect().bottomRight().x(), frame3->frameRect().bottomRight().y());
  p3.drawRect(pdatablock );
  p3.drawText(pdatablock, Qt::AlignCenter|Qt::WordBreak, tr("Program data: %1%").arg(dpercent) );
  p3.setBrush(Qt::darkYellow);
  double percentdb = table1->text(6, 2).toDouble() / table1->text(0, 2).toDouble() * 100;
  QRect buffblock( QPoint(pdatablock.topLeft().x(), (int)(pdatablock.topLeft().y() - frame3->frameRect().bottomLeft().y() / 100 * percentdb)), QSize( frame3->width(),  (int)frame3->frameRect().bottomLeft().y() / 100 * percentdb));
  p3.drawRect(buffblock );
  p3.drawText(buffblock, Qt::AlignCenter|Qt::WordBreak, tr("Disk buffer: %1%").arg(percentdb) );
  p3.setBrush(Qt::darkCyan);
  double percentsm = table1->text(5, 2).toDouble() / table1->text(0, 2).toDouble() * 100;
  QRect smblock( QPoint(buffblock.topLeft().x(), (int)(buffblock.topLeft().y() - frame3->frameRect().bottomLeft().y() / 100 * percentsm)), QSize( frame3->width(),  (int)frame3->frameRect().bottomLeft().y() / 100 * percentsm));
  p3.drawRect(smblock );
  p3.drawText(smblock, Qt::AlignCenter|Qt::WordBreak, tr("Shared memory: %1%").arg(percentsm) );
  p3.setBrush(Qt::green);
  double percentch = table1->text(7, 2).toDouble() / table1->text(0, 2).toDouble() * 100;
  QRect cacheblock( QPoint(smblock.topLeft().x(), (int)(smblock.topLeft().y() - frame3->frameRect().bottomLeft().y() / 100 * percentch)), QSize( frame3->width(),  (int)frame3->frameRect().bottomLeft().y() / 100 * percentch));
  p3.drawRect(cacheblock );
  p3.drawText(cacheblock, Qt::AlignCenter|Qt::WordBreak, tr("Shared memory: %1%").arg(percentch) );
  p3.drawText(frame3->frameRect(), Qt::AlignTop|Qt::AlignHCenter|Qt::WordBreak, tr("Free physical memory: %1%").arg(table1->text(2, 2).toDouble() / table1->text(0, 2).toDouble()*100));

  			/**Paint Swap Memory Graph*/
  QPainter p4(frame4);
  pen.setWidth(1);
  p4.setPen(pen);
  p4.setBrush(Qt::white);
  p4.drawRect(frame4->frameRect() );
  p4.setBrush(Qt::red);
  double swappr = table1->text(10, 2).toDouble() / table1->text(9, 2).toDouble() * 100;
  QRect swapblock( frame4->frameRect().bottomLeft().x(), (int)(frame4->frameRect().bottomLeft().y() - frame4->frameRect().bottomLeft().y() / 100 * swappr), frame4->frameRect().bottomRight().x(), frame4->frameRect().bottomRight().y());
  p4.drawRect(swapblock );
  p4.drawText(swapblock, Qt::AlignCenter|Qt::WordBreak, tr("Used swap memory: %1%").arg(dpercent) );
  p4.drawText(frame4->frameRect(), Qt::AlignCenter|Qt::WordBreak, tr("Free swap memory: %1%").arg(table1->text(11, 2).toDouble() / table1->text(9, 2).toDouble()*100));
}

void MemoryDispDlg::resizeEvent(QResizeEvent *e)
{
  repaint(frame3->frameRect());
  repaint(frame4->frameRect());
  repaint(frame5->frameRect());
  drawGraphs();
}

#include "memorydlg.moc"
