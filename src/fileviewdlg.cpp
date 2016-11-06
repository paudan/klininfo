/***************************************************************************
                          fileviewdlg.cpp  -  description
                             -------------------
    begin                : Tr Lie 7 12:49:12 2004
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

#include "fileviewdlg.h"


#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <ktextbrowser.h>
#include <ktextedit.h>
#include <qframe.h>
#include <klistbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qtextstream.h>
#include <qfile.h>
#include <qiodevice.h>
#include <kmessagebox.h>
#include <qstringlist.h>
#include <qlineedit.h>
#include <stdio.h>

#include "finputdlg.h"

/*
 *  Constructs a FilePreviewDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
FilePreviewDlg::FilePreviewDlg( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "FilePreviewDlg" );
    FilePreviewDlgLayout = new QGridLayout( this, 1, 1, 11, 6, "FilePreviewDlgLayout");

    frameLabel = new QFrame( this, "frameLabel" );
    frameLabel->setFrameShape( QFrame::GroupBoxPanel );
    frameLabel->setFrameShadow( QFrame::Raised );
    FilePreviewDlgLayout->addMultiCellWidget( frameLabel, 0, 0, 0, 1 );

    frameLabelLayout = new QVBoxLayout(frameLabel, 0, 0, "frameLabelLayout");

    dlg_title = new QLabel(frameLabel, "dlg_title");
    frameLabelLayout->addWidget(dlg_title);

    kTextBrowser2 = new KTextBrowser( this, "kTextBrowser2" );

    FilePreviewDlgLayout->addMultiCellWidget( kTextBrowser2, 4, 4, 0, 1 );

    textLabel3 = new QLabel( this, "textLabel3" );
    textLabel3->setFrameShape( QLabel::NoFrame );

    FilePreviewDlgLayout->addMultiCellWidget( textLabel3, 3, 3, 0, 1 );

    kTextEdit1 = new KTextEdit( this, "kTextEdit1" );
    kTextEdit1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, kTextEdit1->sizePolicy().hasHeightForWidth() ) );
    kTextEdit1->setReadOnly(TRUE);

    FilePreviewDlgLayout->addWidget( kTextEdit1, 2, 1 );

    textLabel2 = new QLabel( this, "textLabel2" );
    textLabel2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, textLabel2->sizePolicy().hasHeightForWidth() ) );

    FilePreviewDlgLayout->addWidget( textLabel2, 1, 1 );

    frame = new QFrame( this, "frame" );
    frame->setFrameShape( QFrame::GroupBoxPanel );
    frame->setFrameShadow( QFrame::Raised );
    frameLayout = new QGridLayout( frame, 1, 1, 11, 6, "frameLayout");

    textLabel1 = new QLabel( frame, "textLabel1" );

    frameLayout->addWidget( textLabel1, 0, 0 );
    QSpacerItem* spacer = new QSpacerItem( 20, 30, QSizePolicy::Minimum, QSizePolicy::Fixed );
    frameLayout->addItem( spacer, 4, 1 );

    addButton = new QPushButton( frame, "addButton" );

    frameLayout->addWidget( addButton, 1, 1 );

    modifyButton = new QPushButton( frame, "modifyButton" );

    frameLayout->addWidget( modifyButton, 2, 1 );

    removeButton = new QPushButton( frame, "removeButton" );

    frameLayout->addWidget( removeButton, 3, 1 );

    kListBox1 = new KListBox( frame, "kListBox1" );
    kListBox1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)7, 0, 0, kListBox1->sizePolicy().hasHeightForWidth() ) );
    kListBox1->setResizePolicy( KListBox::AutoOne );

    frameLayout->addMultiCellWidget( kListBox1, 1, 4, 0, 0 );

    FilePreviewDlgLayout->addMultiCellWidget( frame, 1, 2, 0, 0 );
    languageChange();
    resize( QSize(609, 543).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( kListBox1, SIGNAL( executed(QListBoxItem*) ), this, SLOT( kListBox1_executed(QListBoxItem*) ) );
    connect( addButton, SIGNAL( clicked() ), this, SLOT( addButton_clicked() ) );
    connect( modifyButton, SIGNAL( clicked() ), this, SLOT( modifyButton_clicked() ) );
    connect( removeButton, SIGNAL( clicked() ), this, SLOT( removeButton_clicked() ) );

    inputdlg = new FileInputDlg(this, "inputdlg", true);

    connect(inputdlg, SIGNAL(apply() ), this, SLOT(editFileDesc() ) );

    errorMsg = tr("Command and program descriptions laded successfully");
    if (!loadFileList()) errorMsg = tr("Unable to load file list");
}

/*
 *  Destroys the object and frees any allocated resources
 */
FilePreviewDlg::~FilePreviewDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void FilePreviewDlg::languageChange()
{
    setCaption( tr( "File Preview Dialog" ) );
    dlg_title->setText(tr("The most important system files"));
    textLabel3->setText( tr( "File contents:" ) );
    textLabel2->setText( tr( "File description:" ) );
    textLabel1->setText( tr( "Select file for viewing:" ) );
    addButton->setText( tr( "Add" ) );
    modifyButton->setText( tr( "Modify" ) );
    removeButton->setText( tr( "Remove" ) );
}

void FilePreviewDlg::kListBox1_executed(QListBoxItem*)
{
  QString filename = kListBox1->currentText();
  QFile f(filename);
  kTextBrowser2->setText("");
  if (!f.exists())
  KMessageBox::sorry(this, tr("File %1 doesn't exist").arg(filename));
  else {
    if (f.open(IO_ReadOnly) ) kTextBrowser2->setText(f.readAll());
    else KMessageBox::sorry(this, tr("File %1 could not be opened for reading").arg(filename));
  }
  f.close();
  for (int i = 0; i < fileList.count(); i++) {
    QStringList partList = QStringList::split(INFO_DELIMITER, QString(fileList[i]) );
    if (partList[0] == filename && partList.count() == 1) {
       kTextEdit1->setText("");
       break; }
    else if (partList[0] == filename && partList.count() == 2) {
       kTextEdit1->setText(partList[1]);
       break; }
  }
}

void FilePreviewDlg::addButton_clicked()
{
    editState = 0;
    inputdlg->lineEdit1->setText("");
    inputdlg->textEdit1->setText("");
    inputdlg->show();
}

void FilePreviewDlg::modifyButton_clicked()
{
    editState = 1;
    inputdlg->lineEdit1->setText(kListBox1->currentText());
    inputdlg->textEdit1->setText(kTextEdit1->text());
    inputdlg->show();
}

void FilePreviewDlg::removeButton_clicked()
{
  QFile f(descrFile);
  QFile ftr(FILE_TMP1);
  QString line, all_text = "";
  bool found = false;
  QString cmd = kListBox1->currentText();
  int listind = kListBox1->currentItem();
  if (listind != kListBox1->numRows() ) kListBox1->setCurrentItem(listind +  1);
  else kListBox1->setCurrentItem(0);
  loadDescription();
  kListBox1->removeItem(listind);
  if (f.open(IO_ReadWrite ) )   {
       QTextStream rd(&f);
       while (!found && !f.atEnd()) {
          line = rd.readLine();
          if (line.isEmpty() || line.left (3) == "***") all_text.append(line);
          else if (line.contains("NAME") == 1)
             if (line.section(":", -1).stripWhiteSpace() == cmd )
             {
	       found = true;
               while (rd.readLine().left(3) != "***" ) ;
	       			//We skip the description of the command being deleted
	      }
	      else all_text += line + "\n";
	   if (!found)
	      while (line.left(3) != "***")  {
	        line = rd.readLine();
	        all_text += line + "\n";  }
	}
	while (!f.atEnd() ) all_text += rd.readLine() + "\n";
        f.close();
	rename((const char*)descrFile, FILE_TMP2);
	ftr.open(IO_WriteOnly);
	QTextStream rdt(&ftr);
	rdt << all_text;
	ftr.close();
	rename(FILE_TMP1, (const char*)descrFile);
	remove(FILE_TMP2);
   }
}

bool FilePreviewDlg::loadFileList()
{
  QFile f(descrFile);
  QString line, command_info;
  QString comment;
  if (!f.exists()) {
    errorMsg = tr("File with descriptions does not exist or could not be loaded");
    return false;
  }
  else {
    if (f.open(IO_ReadOnly) )   {
       QTextStream rd(&f);
       while (!f.atEnd() ) {
         line = rd.readLine();
         comment = command_info = "";
	 if (line.isEmpty() || line.left (3) == "***" || line.left(1) == "#");
         else if (line.contains("NAME") == 1) {
	    QString fname = line.section(":", -1).stripWhiteSpace();
	    QFile k(fname);
	    if (k.exists()) {
	       kListBox1->insertItem(fname );
               command_info.append(fname + INFO_DELIMITER);
	       line = rd.readLine();
	       if (line.contains("DESCRIPTION") == 1) {
	         while (line.left(3) != "***") {
		   line = rd.readLine();
		   if (line.left(3) != "<p>" || line.left(3) != "<P>") comment.append("<p>" + line + "</p>");
		}
		comment.remove(comment.section("</p>", -2) );
	        fileList << command_info.append(comment) ;
	        comment = "";
                }
            }
          }
	  else while (rd.readLine().left(3) != "***" ) ;
       }
       f.close();
      }
    else {
      errorMsg = tr("Unable to load file with filenames");
      return false; }
  }
  return true;
}

void FilePreviewDlg::editFileDesc()
{
  if (editState == 0) {
  QFile f(descrFile);
    if (f.open(IO_WriteOnly|IO_Append) )   {
       QTextStream rd(&f);
       rd << "NAME: " << inputdlg->lineEdit1->text() << "\n";
       rd << "DESCRIPTION: \n" << inputdlg->textEdit1->text()  << "\n";
       rd << "******************************************************************\n";
    }
    f.close();
    kListBox1->insertItem(inputdlg->lineEdit1->text().stripWhiteSpace() );
    fileList << inputdlg->lineEdit1->text().stripWhiteSpace() + INFO_DELIMITER + inputdlg->textEdit1->text() ;
  }
  else if (editState == 1) {
  QFile f(descrFile);
  QString line, all_text = "";
  QIODevice::Offset where;
  bool found = false;
  QString cmd =inputdlg->lineEdit1->text();
  QString desc = inputdlg->textEdit1->text();
  if (f.open(IO_ReadWrite ) )   {
       QTextStream rd(&f);
       while (!found && !f.atEnd()) {
          where = f.at();
          line = rd.readLine();
          if (line.isEmpty() || line.left (3) == "***") ;
	  if (line.contains("NAME") == 1)
             if (line.section(":", -1).stripWhiteSpace() == cmd )
             {
               found = true;
		/*skip the changed section*/
	       while (rd.readLine().left(3) != "***" ) ;
	        /*read the rest of data*/
		while (!f.atEnd() ) all_text += rd.readLine() + "\n";
		/*Move to the beginning of the deleted section*/
		f.at(where);
	       /*Write in the new section*/
	       rd << "NAME: " << cmd << "\n";
               rd << "DESCRIPTION: \n" << desc  << "\n";
               rd << "******************************************************************\n" << all_text;
	      }
	      else  while (rd.readLine().left(3) != "***") ;
	 }
   f.close();
   }
   	/*If the edited command name isn't in the list*/
   if (!found) {
       kListBox1->insertItem(cmd);
       if (f.open(IO_WriteOnly|IO_Append ) )   {
       QTextStream rd(&f);
        /*We append it to the end of the file*/
       rd << "NAME: " << cmd << "\n";
       rd << "DESCRIPTION: \n" << desc  << "\n";
       rd << "******************************************************************\n";
       f.close();
       }
   }
	     //We also change the data list
   bool is_in_list = false;
   for (int i = 0; i < fileList.count(); i++) {
     QStringList partList = QStringList::split(INFO_DELIMITER, QString(fileList[i]) );
     if (partList[0] == cmd) {
        is_in_list = true;
        fileList[i] = cmd + INFO_DELIMITER + desc;
        break;
     }
   }
   if (!is_in_list) fileList << cmd + INFO_DELIMITER + desc;
   kTextBrowser2->setText(desc);
  }
}

void FilePreviewDlg::loadDescription()
{
  QString current = kListBox1->currentText();
  kTextBrowser2->clear();
  for (int i = 0; i < fileList.count(); i++) {
    QStringList partList = QStringList::split(INFO_DELIMITER, QString(fileList[i]) );
    if (partList[0] == current && partList.count() == 1) {
       kTextBrowser2->setText("");
       break; }
    else if (partList[0] == current && partList.count() == 2) {
       kTextBrowser2->setText(partList[1]);
       break; }
  }
}

void FilePreviewDlg::saveToFile(QString filename, int flags)
{
  QFile file(filename);
  if (!file.open(flags)) return;
  else {
    QTextStream stream(&file);
    stream << "<html>" << "<head>";
    stream << "<title align=\"center\">" << tr("File information") << "</title>";
    stream << "</head>";
    stream << "<body>";
    stream << "<h1 align=\"center\">" << tr("File information") << "</h1>";
    for (int i = 0; i < fileList.count(); i++) {
    QStringList partList = QStringList::split(INFO_DELIMITER, QString(fileList[i]) );
    stream << "\n" << "<h3>" << partList[0] << "</h3>";
    stream << tr("DESCRIPTION: \n") << partList[1]  << "\n";
    }
   file.close();
  }
}

#include "fileviewdlg.moc"
