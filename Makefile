#############################################################################
# Makefile for building: lucidBeaver
# Generated by qmake (2.01a) (Qt 4.6.2) on: wt. gru 21 18:24:39 2010
# Project:  lucidBeaver.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/share/qt4/mkspecs/linux-g++ -unix -o Makefile lucidBeaver.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -Wno-ignored-qualifiers -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4 -I/usr/X11R6/include -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -L/usr/X11R6/lib `sdl-config --libs --cflags` -lSDL -lSDL_image -I/usr/X11R6/include -L/usr/X11R6/lib -lQtOpenGL -lQtGui -lQtCore -lGLU -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = glwidget.cpp \
		paintwidget.cpp \
		mainwindow.cpp \
		main.cpp \
		welcomewindow.cpp \
		field.cpp \
		world.cpp \
		texture.cpp \
		object.cpp \
		node.cpp \
		md2.cpp \
		hero.cpp \
		error.cpp \
		engine.cpp \
		clock.cpp \
		camera.cpp \
		being.cpp \
		lucidbeaver.cpp \
		globalcontainer.cpp \
		floor.cpp \
		lbstairs.cpp \
		lbpassage.cpp \
		lbwallhelper.cpp \
		lbmathhelper.cpp \
		lbstairshelper.cpp \
		lbhelpersbase.cpp \
		lbwindow.cpp \
		designwidgetmini.cpp moc_glwidget.cpp \
		moc_paintwidget.cpp \
		moc_mainwindow.cpp \
		moc_welcomewindow.cpp
OBJECTS       = glwidget.o \
		paintwidget.o \
		mainwindow.o \
		main.o \
		welcomewindow.o \
		field.o \
		world.o \
		texture.o \
		object.o \
		node.o \
		md2.o \
		hero.o \
		error.o \
		engine.o \
		clock.o \
		camera.o \
		being.o \
		lucidbeaver.o \
		globalcontainer.o \
		floor.o \
		lbstairs.o \
		lbpassage.o \
		lbwallhelper.o \
		lbmathhelper.o \
		lbstairshelper.o \
		lbhelpersbase.o \
		lbwindow.o \
		designwidgetmini.o \
		moc_glwidget.o \
		moc_paintwidget.o \
		moc_mainwindow.o \
		moc_welcomewindow.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		lucidBeaver.pro
QMAKE_TARGET  = lucidBeaver
DESTDIR       = 
TARGET        = lucidBeaver

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: lucidBeaver.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtOpenGL.prl \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix -o Makefile lucidBeaver.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/opengl.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtOpenGL.prl:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix -o Makefile lucidBeaver.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/lucidBeaver1.0.0 || $(MKDIR) .tmp/lucidBeaver1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/lucidBeaver1.0.0/ && $(COPY_FILE) --parents glwidget.h paintwidget.h mainwindow.h welcomewindow.h field.h vector.h vector2.h world.h texture.h object.h node.h md2.h hero.h error.h engine.h clock.h camera.h being.h lucidbeaver.h globalcontainer.h floor.h lbstairs.h lbpassage.h lbwallhelper.h lbmathhelper.h counter.h lbstairshelper.h lbhelpersbase.h lbwindow.h designwidgetmini.h .tmp/lucidBeaver1.0.0/ && $(COPY_FILE) --parents glwidget.cpp paintwidget.cpp mainwindow.cpp main.cpp welcomewindow.cpp field.cpp world.cpp texture.cpp object.cpp node.cpp md2.cpp hero.cpp error.cpp engine.cpp clock.cpp camera.cpp being.cpp lucidbeaver.cpp globalcontainer.cpp floor.cpp lbstairs.cpp lbpassage.cpp lbwallhelper.cpp lbmathhelper.cpp lbstairshelper.cpp lbhelpersbase.cpp lbwindow.cpp designwidgetmini.cpp .tmp/lucidBeaver1.0.0/ && (cd `dirname .tmp/lucidBeaver1.0.0` && $(TAR) lucidBeaver1.0.0.tar lucidBeaver1.0.0 && $(COMPRESS) lucidBeaver1.0.0.tar) && $(MOVE) `dirname .tmp/lucidBeaver1.0.0`/lucidBeaver1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/lucidBeaver1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_glwidget.cpp moc_paintwidget.cpp moc_mainwindow.cpp moc_welcomewindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_glwidget.cpp moc_paintwidget.cpp moc_mainwindow.cpp moc_welcomewindow.cpp
moc_glwidget.cpp: clock.h \
		camera.h \
		vector.h \
		error.h \
		world.h \
		object.h \
		node.h \
		floor.h \
		counter.h \
		lbstairs.h \
		field.h \
		md2.h \
		texture.h \
		lbpassage.h \
		lbwindow.h \
		lbmathhelper.h \
		being.h \
		hero.h \
		lucidbeaver.h \
		globalcontainer.h \
		glwidget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) glwidget.h -o moc_glwidget.cpp

moc_paintwidget.cpp: lucidbeaver.h \
		field.h \
		camera.h \
		vector.h \
		error.h \
		md2.h \
		object.h \
		node.h \
		texture.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h \
		globalcontainer.h \
		floor.h \
		lbwallhelper.h \
		lbhelpersbase.h \
		lbstairshelper.h \
		designwidgetmini.h \
		paintwidget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) paintwidget.h -o moc_paintwidget.cpp

moc_mainwindow.cpp: field.h \
		camera.h \
		vector.h \
		error.h \
		md2.h \
		object.h \
		node.h \
		texture.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h \
		globalcontainer.h \
		floor.h \
		mainwindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_welcomewindow.cpp: welcomewindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) welcomewindow.h -o moc_welcomewindow.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

glwidget.o: glwidget.cpp glwidget.h \
		clock.h \
		camera.h \
		vector.h \
		error.h \
		world.h \
		object.h \
		node.h \
		floor.h \
		counter.h \
		lbstairs.h \
		field.h \
		md2.h \
		texture.h \
		lbpassage.h \
		lbwindow.h \
		lbmathhelper.h \
		being.h \
		hero.h \
		lucidbeaver.h \
		globalcontainer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glwidget.o glwidget.cpp

paintwidget.o: paintwidget.cpp paintwidget.h \
		lucidbeaver.h \
		field.h \
		camera.h \
		vector.h \
		error.h \
		md2.h \
		object.h \
		node.h \
		texture.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h \
		globalcontainer.h \
		floor.h \
		lbwallhelper.h \
		lbhelpersbase.h \
		lbstairshelper.h \
		designwidgetmini.h \
		lbstairs.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o paintwidget.o paintwidget.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		field.h \
		camera.h \
		vector.h \
		error.h \
		md2.h \
		object.h \
		node.h \
		texture.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h \
		globalcontainer.h \
		floor.h \
		paintwidget.h \
		lucidbeaver.h \
		lbwallhelper.h \
		lbhelpersbase.h \
		lbstairshelper.h \
		designwidgetmini.h \
		glwidget.h \
		clock.h \
		world.h \
		lbstairs.h \
		being.h \
		hero.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

main.o: main.cpp mainwindow.h \
		field.h \
		camera.h \
		vector.h \
		error.h \
		md2.h \
		object.h \
		node.h \
		texture.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h \
		globalcontainer.h \
		floor.h \
		welcomewindow.h \
		lucidbeaver.h \
		lbstairs.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

welcomewindow.o: welcomewindow.cpp welcomewindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o welcomewindow.o welcomewindow.cpp

field.o: field.cpp field.h \
		camera.h \
		vector.h \
		error.h \
		md2.h \
		object.h \
		node.h \
		texture.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h \
		floor.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o field.o field.cpp

world.o: world.cpp world.h \
		camera.h \
		vector.h \
		error.h \
		object.h \
		node.h \
		floor.h \
		counter.h \
		lbstairs.h \
		field.h \
		md2.h \
		texture.h \
		lbpassage.h \
		lbwindow.h \
		lbmathhelper.h \
		being.h \
		hero.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o world.o world.cpp

texture.o: texture.cpp texture.h \
		error.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o texture.o texture.cpp

object.o: object.cpp object.h \
		camera.h \
		vector.h \
		error.h \
		node.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o object.o object.cpp

node.o: node.cpp node.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o node.o node.cpp

md2.o: md2.cpp md2.h \
		object.h \
		camera.h \
		vector.h \
		error.h \
		node.h \
		texture.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o md2.o md2.cpp

hero.o: hero.cpp hero.h \
		being.h \
		md2.h \
		object.h \
		camera.h \
		vector.h \
		error.h \
		node.h \
		texture.h \
		field.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o hero.o hero.cpp

error.o: error.cpp error.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o error.o error.cpp

engine.o: engine.cpp engine.h \
		clock.h \
		camera.h \
		vector.h \
		error.h \
		world.h \
		object.h \
		node.h \
		floor.h \
		counter.h \
		lbstairs.h \
		field.h \
		md2.h \
		texture.h \
		lbpassage.h \
		lbwindow.h \
		lbmathhelper.h \
		being.h \
		hero.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o engine.o engine.cpp

clock.o: clock.cpp clock.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o clock.o clock.cpp

camera.o: camera.cpp camera.h \
		vector.h \
		error.h \
		object.h \
		node.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o camera.o camera.cpp

being.o: being.cpp being.h \
		md2.h \
		object.h \
		camera.h \
		vector.h \
		error.h \
		node.h \
		texture.h \
		field.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o being.o being.cpp

lucidbeaver.o: lucidbeaver.cpp lucidbeaver.h \
		field.h \
		camera.h \
		vector.h \
		error.h \
		md2.h \
		object.h \
		node.h \
		texture.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lucidbeaver.o lucidbeaver.cpp

globalcontainer.o: globalcontainer.cpp globalcontainer.h \
		object.h \
		camera.h \
		vector.h \
		error.h \
		node.h \
		field.h \
		md2.h \
		texture.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h \
		floor.h \
		lbstairs.h \
		paintwidget.h \
		lucidbeaver.h \
		lbwallhelper.h \
		lbhelpersbase.h \
		lbstairshelper.h \
		designwidgetmini.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o globalcontainer.o globalcontainer.cpp

floor.o: floor.cpp floor.h \
		object.h \
		camera.h \
		vector.h \
		error.h \
		node.h \
		counter.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o floor.o floor.cpp

lbstairs.o: lbstairs.cpp lbstairs.h \
		object.h \
		camera.h \
		vector.h \
		error.h \
		node.h \
		field.h \
		md2.h \
		texture.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lbstairs.o lbstairs.cpp

lbpassage.o: lbpassage.cpp lbpassage.h \
		field.h \
		camera.h \
		vector.h \
		error.h \
		md2.h \
		object.h \
		node.h \
		texture.h \
		lbwindow.h \
		counter.h \
		lbmathhelper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lbpassage.o lbpassage.cpp

lbwallhelper.o: lbwallhelper.cpp lbwallhelper.h \
		vector.h \
		field.h \
		camera.h \
		error.h \
		md2.h \
		object.h \
		node.h \
		texture.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h \
		lbhelpersbase.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lbwallhelper.o lbwallhelper.cpp

lbmathhelper.o: lbmathhelper.cpp lbmathhelper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lbmathhelper.o lbmathhelper.cpp

lbstairshelper.o: lbstairshelper.cpp lbstairshelper.h \
		globalcontainer.h \
		object.h \
		camera.h \
		vector.h \
		error.h \
		node.h \
		field.h \
		md2.h \
		texture.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h \
		floor.h \
		lbhelpersbase.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lbstairshelper.o lbstairshelper.cpp

lbhelpersbase.o: lbhelpersbase.cpp lbhelpersbase.h \
		vector.h \
		field.h \
		camera.h \
		error.h \
		md2.h \
		object.h \
		node.h \
		texture.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lbhelpersbase.o lbhelpersbase.cpp

lbwindow.o: lbwindow.cpp lbwindow.h \
		vector.h \
		object.h \
		camera.h \
		error.h \
		node.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lbwindow.o lbwindow.cpp

designwidgetmini.o: designwidgetmini.cpp designwidgetmini.h \
		globalcontainer.h \
		object.h \
		camera.h \
		vector.h \
		error.h \
		node.h \
		field.h \
		md2.h \
		texture.h \
		lbpassage.h \
		counter.h \
		lbwindow.h \
		lbmathhelper.h \
		floor.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o designwidgetmini.o designwidgetmini.cpp

moc_glwidget.o: moc_glwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_glwidget.o moc_glwidget.cpp

moc_paintwidget.o: moc_paintwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_paintwidget.o moc_paintwidget.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_welcomewindow.o: moc_welcomewindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_welcomewindow.o moc_welcomewindow.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

