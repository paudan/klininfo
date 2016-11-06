/***************************************************************************
 *   Copyright (C) 2004 by Paulius Danenas                                 *
 *   paulius.dan@takas.lt                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/*
 * Copyright (C) 2004 Paulius Danenas <paulius.dan@takas.lt>
 */

#include "klininfodialog.h"
#include "splashscreen.h"

#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <kstandarddirs.h>
#include <qobject.h>
#include <qfileinfo.h>
#include <stdlib.h>
#include <string.h>
#include <qtranslator.h>
#include <qtextcodec.h>

static const char description[] =
    I18N_NOOP("A KDE KPart Application");

static const char version[] = "0.2b";

static KCmdLineOptions options[] =
{
//    { "-V", I18N_NOOP( "Program version." ), 0 },
    KCmdLineLastOption
};

int main(int argc, char **argv)
{
    KAboutData about("klininfo", I18N_NOOP("KLinInfo"), version, description,
                     KAboutData::License_GPL, "(C) 2004 Paulius Danenas", 0, 0, "paulius.dan@takas.lt");
    about.addAuthor( "Paulius Danenas", 0, "paulius.dan@takas.lt" );
    KCmdLineArgs::init(argc, argv, &about);
    KCmdLineArgs::addCmdLineOptions( options );
    KApplication app;
    KLinInfoDialog *mainWin = 0;

    // no session.. just start up normally
    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
	
  //  if (args->isSet("-V") ) { printf("This is KLinInfo %s", version);  app.quit(); }
    
    QString langfile = locate("appdata", QString("translations/") + QTextCodec::locale() + QString(".qm"));
    QFileInfo f(langfile);
    if (f.exists() ) {			
		QTranslator *translator = new QTranslator(0);
		if (!translator->load(f.absFilePath(), ".")) fprintf(stderr, "Translation could not be loaded");
		app.installTranslator(translator); }
    //}
	
    mainWin = new KLinInfoDialog();
    app.setMainWidget( mainWin );
    
    SplashScreen *splash = new SplashScreen();
    app.processEvents();
    
    splash->showMessage(QObject::tr("Loading GUI..."));
    mainWin->initGUI();
    
    splash->showMessage(QObject::tr("Loading widgets..."));
    mainWin->loadWidgets();
    
    splash->showMessage(QObject::tr("Getting user settings..."));
    mainWin->initSettings();
    mainWin->applySettings();
    
    splash->showMessage(QObject::tr("Finished loading, starting application..."));
    delete splash;
    
    QRect rect = QApplication::desktop()->geometry();
    mainWin->move(rect.x() + (rect.width() -  mainWin->sizeHint().width()) / 2,
	rect.y() + (rect.height() -  mainWin->sizeHint().height()) / 2);
    
    mainWin->show();
	
    args->clear();   

    // mainWin has WDestructiveClose flag by default, so it will delete itself.
    return app.exec();
}

