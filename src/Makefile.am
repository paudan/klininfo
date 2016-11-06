# set the include path for X, qt and KDE
INCLUDES = $(all_includes)

# these are the headers for your project


# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/klininfo.pot

KDE_ICON = klininfo

#########################################################################
# APPLICATION SECTION
#########################################################################
# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = klininfo

# the application source, library search path, and link libraries

klininfo_LDFLAGS = $(KDE_RPATH) $(all_libraries)
klininfo_LDADD = $(LIB_KDEUI)

# this is where the desktop file will go 
shelldesktopdir   = $(kde_appsdir)/Utilities
shelldesktop_DATA = klininfo.desktop

# this is where the shell's XML-GUI resource file goes
shellrcdir   = $(kde_datadir)/klininfo
shellrc_DATA = klininfoui.rc

klininfo_SOURCES =  comdescrdlg.cpp comdescrdlg.h config_files.cpp config_files.h config_font.cpp config_font.h config_misc.cpp config_misc.h configdlg.cpp configdlg.h dudlg.cpp dudlg.h fileviewdlg.cpp fileviewdlg.h finputdlg.cpp finputdlg.h fontdlg.cpp fontdlg.h inputdlg.cpp inputdlg.h klininfodialog.cpp klininfodialog.h main.cpp memorydlg.cpp memorydlg.h modldispdlg.cpp modldispdlg.h partitiondlg.cpp partitiondlg.h pkginfodlg.cpp pkginfodlg.h printenvdlg.cpp printenvdlg.h processlistdlg.cpp processlistdlg.h rpmsearchdlg.cpp rpmsearchdlg.h scriptinfodlg.cpp scriptinfodlg.h selsavedlg.cpp selsavedlg.h simpltabledlg.cpp simpltabledlg.h splashscreen.cpp splashscreen.h
SUBDIRS =  templates
bin_SCRIPTS =  all_info
