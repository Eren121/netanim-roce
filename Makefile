#############################################################################
# Makefile for building: newcanvas1
# Generated by qmake (2.01a) (Qt 4.8.1) on: Sun Nov 17 11:24:00 2013
# Project:  newcanvas1.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile newcanvas1.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DNS3_LOG_ENABLE -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
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

SOURCES       = main.cpp \
		myview.cpp \
		log.cpp \
		fatal-error.cpp \
		fatal-impl.cpp \
		logqt.cpp \
		resizeablepixmap.cpp \
		resizeableitem.cpp \
		animnode.cpp \
		animatorscene.cpp \
		animpacket.cpp \
		netanim.cpp \
		animatormode.cpp \
		mode.cpp \
		animxmlparser.cpp \
		animatorview.cpp moc_myview.cpp \
		moc_animatorscene.cpp \
		moc_animpacket.cpp \
		moc_netanim.cpp \
		moc_animatormode.cpp \
		qrc_testrc.cpp
OBJECTS       = main.o \
		myview.o \
		log.o \
		fatal-error.o \
		fatal-impl.o \
		logqt.o \
		resizeablepixmap.o \
		resizeableitem.o \
		animnode.o \
		animatorscene.o \
		animpacket.o \
		netanim.o \
		animatormode.o \
		mode.o \
		animxmlparser.o \
		animatorview.o \
		moc_myview.o \
		moc_animatorscene.o \
		moc_animpacket.o \
		moc_netanim.o \
		moc_animatormode.o \
		qrc_testrc.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/declarative_debug.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		newcanvas1.pro
QMAKE_TARGET  = newcanvas1
DESTDIR       = 
TARGET        = newcanvas1

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
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: newcanvas1.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/declarative_debug.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile newcanvas1.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/declarative_debug.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile newcanvas1.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/newcanvas11.0.0 || $(MKDIR) .tmp/newcanvas11.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/newcanvas11.0.0/ && $(COPY_FILE) --parents myview.h log.h fatal-error.h fatal-impl.h abort.h assert.h logqt.h animatorconstants.h resizeablepixmap.h resizeableitem.h animnode.h common.h animatorscene.h timevalue.h animpacket.h netanim.h animatormode.h animatorview.h mode.h animxmlparser.h animevent.h .tmp/newcanvas11.0.0/ && $(COPY_FILE) --parents testrc.qrc .tmp/newcanvas11.0.0/ && $(COPY_FILE) --parents main.cpp myview.cpp log.cpp fatal-error.cpp fatal-impl.cpp logqt.cpp resizeablepixmap.cpp resizeableitem.cpp animnode.cpp animatorscene.cpp animpacket.cpp netanim.cpp animatormode.cpp mode.cpp animxmlparser.cpp animatorview.cpp .tmp/newcanvas11.0.0/ && (cd `dirname .tmp/newcanvas11.0.0` && $(TAR) newcanvas11.0.0.tar newcanvas11.0.0 && $(COMPRESS) newcanvas11.0.0.tar) && $(MOVE) `dirname .tmp/newcanvas11.0.0`/newcanvas11.0.0.tar.gz . && $(DEL_FILE) -r .tmp/newcanvas11.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_myview.cpp moc_animatorscene.cpp moc_animpacket.cpp moc_netanim.cpp moc_animatormode.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_myview.cpp moc_animatorscene.cpp moc_animpacket.cpp moc_netanim.cpp moc_animatormode.cpp
moc_myview.cpp: myview.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) myview.h -o moc_myview.cpp

moc_animatorscene.cpp: animnode.h \
		common.h \
		resizeableitem.h \
		resizeablepixmap.h \
		timevalue.h \
		log.h \
		animpacket.h \
		animatorconstants.h \
		animevent.h \
		animatorscene.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) animatorscene.h -o moc_animatorscene.cpp

moc_animpacket.cpp: animatorconstants.h \
		common.h \
		timevalue.h \
		log.h \
		animevent.h \
		animpacket.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) animpacket.h -o moc_animpacket.cpp

moc_netanim.cpp: mode.h \
		netanim.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) netanim.h -o moc_netanim.cpp

moc_animatormode.cpp: animatorconstants.h \
		animatorscene.h \
		animnode.h \
		common.h \
		resizeableitem.h \
		resizeablepixmap.h \
		timevalue.h \
		log.h \
		animpacket.h \
		animevent.h \
		animatorview.h \
		mode.h \
		animatormode.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) animatormode.h -o moc_animatormode.cpp

compiler_rcc_make_all: qrc_testrc.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_testrc.cpp
qrc_testrc.cpp: testrc.qrc \
		ns3logo2.png \
		animator_play.svg
	/usr/bin/rcc -name testrc testrc.qrc -o qrc_testrc.cpp

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
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

main.o: main.cpp myview.h \
		animatorscene.h \
		animnode.h \
		common.h \
		resizeableitem.h \
		resizeablepixmap.h \
		timevalue.h \
		log.h \
		animpacket.h \
		animatorconstants.h \
		animevent.h \
		netanim.h \
		mode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

myview.o: myview.cpp log.h \
		logqt.h \
		animpacket.h \
		animatorconstants.h \
		common.h \
		timevalue.h \
		animevent.h \
		myview.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o myview.o myview.cpp

log.o: log.cpp log.h \
		assert.h \
		fatal-error.h \
		fatal-impl.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o log.o log.cpp

fatal-error.o: fatal-error.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fatal-error.o fatal-error.cpp

fatal-impl.o: fatal-impl.cpp fatal-impl.h \
		log.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fatal-impl.o fatal-impl.cpp

logqt.o: logqt.cpp logqt.h \
		animpacket.h \
		animatorconstants.h \
		common.h \
		timevalue.h \
		log.h \
		animevent.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o logqt.o logqt.cpp

resizeablepixmap.o: resizeablepixmap.cpp resizeablepixmap.h \
		logqt.h \
		animpacket.h \
		animatorconstants.h \
		common.h \
		timevalue.h \
		log.h \
		animevent.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o resizeablepixmap.o resizeablepixmap.cpp

resizeableitem.o: resizeableitem.cpp resizeableitem.h \
		logqt.h \
		animpacket.h \
		animatorconstants.h \
		common.h \
		timevalue.h \
		log.h \
		animevent.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o resizeableitem.o resizeableitem.cpp

animnode.o: animnode.cpp animnode.h \
		common.h \
		resizeableitem.h \
		animatorview.h \
		animatorscene.h \
		resizeablepixmap.h \
		timevalue.h \
		log.h \
		animpacket.h \
		animatorconstants.h \
		animevent.h \
		logqt.h \
		fatal-error.h \
		fatal-impl.h \
		assert.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o animnode.o animnode.cpp

animatorscene.o: animatorscene.cpp log.h \
		logqt.h \
		animpacket.h \
		animatorconstants.h \
		common.h \
		timevalue.h \
		animevent.h \
		animatorscene.h \
		animnode.h \
		resizeableitem.h \
		resizeablepixmap.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o animatorscene.o animatorscene.cpp

animpacket.o: animpacket.cpp animpacket.h \
		animatorconstants.h \
		common.h \
		timevalue.h \
		log.h \
		animevent.h \
		animnode.h \
		resizeableitem.h \
		animatorview.h \
		animatorscene.h \
		resizeablepixmap.h \
		logqt.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o animpacket.o animpacket.cpp

netanim.o: netanim.cpp netanim.h \
		mode.h \
		animatormode.h \
		animatorconstants.h \
		animatorscene.h \
		animnode.h \
		common.h \
		resizeableitem.h \
		resizeablepixmap.h \
		timevalue.h \
		log.h \
		animpacket.h \
		animevent.h \
		animatorview.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o netanim.o netanim.cpp

animatormode.o: animatormode.cpp animatormode.h \
		animatorconstants.h \
		animatorscene.h \
		animnode.h \
		common.h \
		resizeableitem.h \
		resizeablepixmap.h \
		timevalue.h \
		log.h \
		animpacket.h \
		animevent.h \
		animatorview.h \
		mode.h \
		animxmlparser.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o animatormode.o animatormode.cpp

mode.o: mode.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mode.o mode.cpp

animxmlparser.o: animxmlparser.cpp animxmlparser.h \
		animatormode.h \
		animatorconstants.h \
		animatorscene.h \
		animnode.h \
		common.h \
		resizeableitem.h \
		resizeablepixmap.h \
		timevalue.h \
		log.h \
		animpacket.h \
		animevent.h \
		animatorview.h \
		mode.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o animxmlparser.o animxmlparser.cpp

animatorview.o: animatorview.cpp animatorview.h \
		animatorscene.h \
		animnode.h \
		common.h \
		resizeableitem.h \
		resizeablepixmap.h \
		timevalue.h \
		log.h \
		animpacket.h \
		animatorconstants.h \
		animevent.h \
		logqt.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o animatorview.o animatorview.cpp

moc_myview.o: moc_myview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_myview.o moc_myview.cpp

moc_animatorscene.o: moc_animatorscene.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_animatorscene.o moc_animatorscene.cpp

moc_animpacket.o: moc_animpacket.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_animpacket.o moc_animpacket.cpp

moc_netanim.o: moc_netanim.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_netanim.o moc_netanim.cpp

moc_animatormode.o: moc_animatormode.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_animatormode.o moc_animatormode.cpp

qrc_testrc.o: qrc_testrc.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_testrc.o qrc_testrc.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

