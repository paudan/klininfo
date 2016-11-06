/***************************************************************************
                          comdescrdlg.cpp  -  description
                             -------------------
    begin                : Pr Lie 5 15:38:46 2004
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

#include "comdescrdlg.h"


#include <qvariant.h>
#include <qlabel.h>
#include <ktextbrowser.h>
#include <qpushbutton.h>
#include <qlistbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qstringlist.h>
#include <qlineedit.h>
#include <qiodevice.h>
#include <qregexp.h>
#include <stdio.h>
#include "inputdlg.h"

/*
 *  Constructs a CommandDescrDlg as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CommandDescrDlg::CommandDescrDlg( QWidget* parent, const char* name, WFlags fl, QString filename )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "CommandDescrDlg" );
    CommandDescrDlgLayout = new QGridLayout( this, 1, 1, 11, 6, "CommandDescrDlgLayout"); 

    TextLabel1 = new QLabel( this, "TextLabel1" );

    CommandDescrDlgLayout->addWidget( TextLabel1, 1, 0 );

    textLabel3 = new QLabel( this, "textLabel3" );

    CommandDescrDlgLayout->addWidget( textLabel3, 5, 0 );

    kTextBrowser1 = new KTextBrowser( this, "kTextBrowser1" );

    CommandDescrDlgLayout->addMultiCellWidget( kTextBrowser1, 6, 6, 0, 3 );

    addButton = new QPushButton( this, "addButton" );
    addButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, addButton->sizePolicy().hasHeightForWidth() ) );

    CommandDescrDlgLayout->addWidget( addButton, 2, 3 );

    modifyButton = new QPushButton( this, "modifyButton" );
    modifyButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, modifyButton->sizePolicy().hasHeightForWidth() ) );

    CommandDescrDlgLayout->addWidget( modifyButton, 3, 3 );

    removeButton = new QPushButton( this, "removeButton" );
    removeButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)0, 0, 0, removeButton->sizePolicy().hasHeightForWidth() ) );

    CommandDescrDlgLayout->addWidget( removeButton, 4, 3 );
    QSpacerItem* spacer = new QSpacerItem( 50, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    CommandDescrDlgLayout->addItem( spacer, 3, 2 );

    listBox1 = new QListBox( this, "listBox1" );

    CommandDescrDlgLayout->addMultiCellWidget( listBox1, 2, 4, 0, 1 );
    languageChange();
    resize( QSize(600, 482).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( listBox1, SIGNAL( selected(QListBoxItem*) ), this, SLOT( listBox1_selected(QListBoxItem*) ) );
    connect( listBox1, SIGNAL( doubleClicked(QListBoxItem*) ), this, SLOT( listBox1_doubleClicked(QListBoxItem*) ) );
    connect( listBox1, SIGNAL( clicked(QListBoxItem*) ), this, SLOT( listBox1_clicked(QListBoxItem*) ) );
    connect( addButton, SIGNAL( clicked() ), this, SLOT( addButton_clicked() ) );
    connect( modifyButton, SIGNAL( clicked() ), this, SLOT( modifyButton_clicked() ) );
    connect( removeButton, SIGNAL( clicked() ), this, SLOT( removeButton_clicked() ) );

    inputdlg = new InputDlg(this, "inputdlg", true);

    connect(inputdlg, SIGNAL(apply() ), this, SLOT(addNewCommand() ) );

    descrFile = filename;
    errorMsg = "";
    if (!loadInfo(filename) ) errorMsg = tr("Could not load information");

}

/*
 *  Destroys the object and frees any allocated resources
 */
CommandDescrDlg::~CommandDescrDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CommandDescrDlg::languageChange()
{
    setCaption( tr( "Command Description Dialog" ) );
    TextLabel1->setText( tr( "Command list:" ) );
    textLabel3->setText( tr( "Description:" ) );
    addButton->setText( tr( "Add" ) );
    modifyButton->setText( tr( "Modify" ) );
    removeButton->setText( tr( "Remove" ) );
    listBox1->clear();
}

void CommandDescrDlg::listBox1_selected(QListBoxItem*)
{
    loadDescription();
}

void CommandDescrDlg::listBox1_doubleClicked(QListBoxItem*)
{
    loadDescription();
}

void CommandDescrDlg::listBox1_clicked(QListBoxItem*)
{
    loadDescription();
}

void CommandDescrDlg::addButton_clicked()
{
    editState = 0;
    inputdlg->lineEdit1->setText("");
    inputdlg->textEdit1->setText("");
    inputdlg->show();
}

void CommandDescrDlg::modifyButton_clicked()
{
    editState = 1;
    inputdlg->lineEdit1->setText(listBox1->currentText());
    inputdlg->textEdit1->setText(kTextBrowser1->text());
    inputdlg->show();
}

void CommandDescrDlg::removeButton_clicked()
{
  QFile f(descrFile);
  QFile ftr("comm0045.tmp");
  QString line, all_text = "";
  bool found = false;
  QString cmd = listBox1->currentText();
  int listind = listBox1->currentItem();
  if (listind != listBox1->numRows() ) listBox1->setCurrentItem(listind +  1);
  else listBox1->setCurrentItem(0);
  loadDescription();
  listBox1->removeItem(listind);
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
	rename((const char*)descrFile, "comm0012.tmp");
	ftr.open(IO_WriteOnly);
	QTextStream rdt(&ftr);
	rdt << all_text;
	ftr.close();
	rename("comm0045.tmp", (const char*)descrFile);
	remove("comm0012.tmp");
   }
}

bool CommandDescrDlg::loadInfo(QString filename)
{
  QFile f(filename);
  QString line, command_info;
  QString comment;
  bool errorLoad = false;
  if (!f.exists()) {
    errorLoad = true;
    errorMsg = tr("File with descriptions does not exist or could not be loaded");
  }
  else {
    if (f.open(IO_ReadOnly) )   {
       QTextStream rd(&f);
       while (!rd.atEnd() ) {
         line = rd.readLine();
         comment = command_info = "";
	 if (line.left (3) == "***" || line.isEmpty()) ;
         else if (line.contains("NAME") == 1) {
	    listBox1->insertItem(line.section(":", -1).stripWhiteSpace() );
            command_info.append(line.section(":", -1).stripWhiteSpace() + INFO_DELIMITER);
	    line = rd.readLine();
	    if (line.contains("DESCRIPTION") == 1) {
	         while (line.left(3) != "***") {
		   line = rd.readLine();
		   if (line.left(3) != "<p>" || line.left(3) != "<P>") comment.append("<p>" + line + "</p>");
		}
		comment.remove(comment.section("</p>", -2) );
	        commandlist << command_info.append(comment) ;
	        comment = "";
            }
         }
       }
    }
    else {
      errorLoad = true;
      errorMsg = tr("Unable to load file with filenames");  }
  }
  f.close();
  return errorLoad;
}

void CommandDescrDlg::loadDescription()
{
  QString current = listBox1->currentText();
  kTextBrowser1->clear();
  for (int i = 0; i < commandlist.count(); i++) {
    QStringList partList = QStringList::split(INFO_DELIMITER, QString(commandlist[i]) );
    if (partList[0] == current && partList.count() == 1) {
       kTextBrowser1->setText("");
       break; }
    else if (partList[0] == current && partList.count() == 2) {
       kTextBrowser1->setText(partList[1]);
       break; }
  }
}

void CommandDescrDlg::addNewCommand()
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
    listBox1->insertItem(inputdlg->lineEdit1->text().stripWhiteSpace() );
    commandlist << inputdlg->lineEdit1->text().stripWhiteSpace() + INFO_DELIMITER + inputdlg->textEdit1->text() ;
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
       listBox1->insertItem(cmd);
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
   for (int i = 0; i < commandlist.count(); i++) {
     QStringList partList = QStringList::split(INFO_DELIMITER, QString(commandlist[i]) );
     if (partList[0] == cmd) {
        is_in_list = true;
        commandlist[i] = cmd + INFO_DELIMITER + desc;
        break;
     }
   }
   if (!is_in_list) commandlist << cmd + INFO_DELIMITER + desc;
   kTextBrowser1->setText(desc);
  }
}

void CommandDescrDlg::saveToFile(QString filename, int flags)
{
  QFile file(filename);
  if (!file.open(flags)) return;
  else {
    QTextStream stream(&file);
    stream << "<html>" << "<head>";
    stream << "<title align=\"center\">" << tr("Command and program information") << "</title>";
    stream << "</head>";
    stream << "<body>";
    stream << "<h1 align=\"center\">" << tr("Command and program information") << "</h1>";
    for (int i = 0; i < commandlist.count(); i++) {
    QStringList partList = QStringList::split(INFO_DELIMITER, QString(commandlist[i]) );
    stream << "\n" << "<h3>" << partList[0] << "</h3>";
    stream << tr("DESCRIPTION: \n") << partList[1]  << "\n";
    }
   file.close();
  }
}

#include "comdescrdlg.moc"
