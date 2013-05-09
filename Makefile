#############################################################################
# Makefile for building: newcanvas1.app/Contents/MacOS/newcanvas1
# Generated by qmake (2.01a) (Qt 4.8.1) on: Wed May 8 20:52:29 2013
# Project:  newcanvas1.pro
# Template: app
# Command: /Users/john/QtSDK/Desktop/Qt/4.8.1/gcc/bin/qmake -spec ../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/macx-g++ CONFIG+=declarative_debug -o Makefile newcanvas1.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DNS3_LOG_ENABLE -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -gdwarf-2 -arch x86_64 -Xarch_x86_64 -mmacosx-version-min=10.7 -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -g -gdwarf-2 -arch x86_64 -Xarch_x86_64 -mmacosx-version-min=10.7 -Wall -W $(DEFINES)
INCPATH       = -I../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/macx-g++ -I. -I../../QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtCore.framework/Versions/4/Headers -I../../QtSDK/Desktop/Qt/4.8.1/gcc/include/QtCore -I../../QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtGui.framework/Versions/4/Headers -I../../QtSDK/Desktop/Qt/4.8.1/gcc/include/QtGui -I../../QtSDK/Desktop/Qt/4.8.1/gcc/include -I. -F/Users/john/QtSDK/Desktop/Qt/4.8.1/gcc/lib
LINK          = g++
LFLAGS        = -headerpad_max_install_names -arch x86_64 -Xarch_x86_64 -mmacosx-version-min=10.7
LIBS          = $(SUBLIBS) -F/Users/john/QtSDK/Desktop/Qt/4.8.1/gcc/lib -L/Users/john/QtSDK/Desktop/Qt/4.8.1/gcc/lib -framework QtGui -L/usr/local/pgsql/lib -L/tmp/qt-stuff-85167/source/qt-everywhere-opensource-src-4.8.1/Desktop/Qt/4.8.1/gcc/lib -F/tmp/qt-stuff-85167/source/qt-everywhere-opensource-src-4.8.1/Desktop/Qt/4.8.1/gcc/lib -framework QtCore 
AR            = ar cq
RANLIB        = ranlib -s
QMAKE         = /Users/john/QtSDK/Desktop/Qt/4.8.1/gcc/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = 
INSTALL_FILE  = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = $(COPY_FILE)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
export MACOSX_DEPLOYMENT_TARGET = 10.4

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		myview.cpp \
		myscene.cpp \
		log.cpp \
		fatal-error.cpp \
		fatal-impl.cpp moc_myview.cpp \
		moc_myscene.cpp
OBJECTS       = main.o \
		myview.o \
		myscene.o \
		log.o \
		fatal-error.o \
		fatal-impl.o \
		moc_myview.o \
		moc_myscene.o
DIST          = ../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/unix.conf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/mac.conf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base.conf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base-macx.conf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-base.conf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-macx.conf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/qconfig.pri \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/modules/qt_webkit_version.pri \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_functions.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_config.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/exclusive_builds.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_pre.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/default_pre.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/dwarf2.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/debug.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_post.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/default_post.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/x86_64.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/objective_c.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/declarative_debug.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/warn_on.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/thread.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/moc.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/rez.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/sdk.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/resources.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/uic.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/yacc.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/lex.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/include_source_dir.prf \
		newcanvas1.pro
QMAKE_TARGET  = newcanvas1
DESTDIR       = 
TARGET        = newcanvas1.app/Contents/MacOS/newcanvas1

####### Custom Compiler Variables
QMAKE_COMP_QMAKE_OBJECTIVE_CFLAGS = -pipe \
		-g \
		-arch \
		x86_64 \
		-Xarch_x86_64 \
		-mmacosx-version-min=10.7 \
		-Wall \
		-W


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

all: Makefile newcanvas1.app/Contents/PkgInfo newcanvas1.app/Contents/Resources/empty.lproj newcanvas1.app/Contents/Info.plist $(TARGET)

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) newcanvas1.app/Contents/MacOS/ || $(MKDIR) newcanvas1.app/Contents/MacOS/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: newcanvas1.pro  ../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/macx-g++/qmake.conf ../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/unix.conf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/mac.conf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base.conf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base-macx.conf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-base.conf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-macx.conf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/qconfig.pri \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/modules/qt_webkit_version.pri \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_functions.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_config.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/exclusive_builds.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_pre.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/default_pre.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/dwarf2.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/debug.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_post.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/default_post.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/x86_64.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/objective_c.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/declarative_debug.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/warn_on.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/thread.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/moc.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/rez.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/sdk.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/resources.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/uic.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/yacc.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/lex.prf \
		../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/include_source_dir.prf \
		/Users/john/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtGui.framework/QtGui.prl \
		/Users/john/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtCore.framework/QtCore.prl
	$(QMAKE) -spec ../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/macx-g++ CONFIG+=declarative_debug -o Makefile newcanvas1.pro
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/unix.conf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/mac.conf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base.conf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base-macx.conf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-base.conf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-macx.conf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/qconfig.pri:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/modules/qt_webkit_version.pri:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_functions.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_config.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/exclusive_builds.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_pre.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/default_pre.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/dwarf2.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/debug.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_post.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/default_post.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/x86_64.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/objective_c.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/declarative_debug.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/warn_on.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/thread.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/moc.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/rez.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/mac/sdk.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/resources.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/uic.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/yacc.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/lex.prf:
../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/include_source_dir.prf:
/Users/john/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtGui.framework/QtGui.prl:
/Users/john/QtSDK/Desktop/Qt/4.8.1/gcc/lib/QtCore.framework/QtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec ../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/macx-g++ CONFIG+=declarative_debug -o Makefile newcanvas1.pro

newcanvas1.app/Contents/PkgInfo: 
	@$(CHK_DIR_EXISTS) newcanvas1.app/Contents || $(MKDIR) newcanvas1.app/Contents 
	@$(DEL_FILE) newcanvas1.app/Contents/PkgInfo
	@echo "APPL????" >newcanvas1.app/Contents/PkgInfo
newcanvas1.app/Contents/Resources/empty.lproj: 
	@$(CHK_DIR_EXISTS) newcanvas1.app/Contents/Resources || $(MKDIR) newcanvas1.app/Contents/Resources 
	@touch newcanvas1.app/Contents/Resources/empty.lproj
	
newcanvas1.app/Contents/Info.plist: 
	@$(CHK_DIR_EXISTS) newcanvas1.app/Contents || $(MKDIR) newcanvas1.app/Contents 
	@$(DEL_FILE) newcanvas1.app/Contents/Info.plist
	@sed -e "s,@SHORT_VERSION@,1.0,g" -e "s,@TYPEINFO@,????,g" -e "s,@ICON@,,g" -e "s,@EXECUTABLE@,newcanvas1,g" -e "s,@TYPEINFO@,????,g" ../../QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/macx-g++/Info.plist.app >newcanvas1.app/Contents/Info.plist
dist: 
	@$(CHK_DIR_EXISTS) .tmp/newcanvas11.0.0 || $(MKDIR) .tmp/newcanvas11.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/newcanvas11.0.0/ && $(COPY_FILE) --parents myview.h myscene.h log.h fatal-error.h fatal-impl.h abort.h assert.h .tmp/newcanvas11.0.0/ && $(COPY_FILE) --parents main.cpp myview.cpp myscene.cpp log.cpp fatal-error.cpp fatal-impl.cpp .tmp/newcanvas11.0.0/ && (cd `dirname .tmp/newcanvas11.0.0` && $(TAR) newcanvas11.0.0.tar newcanvas11.0.0 && $(COMPRESS) newcanvas11.0.0.tar) && $(MOVE) `dirname .tmp/newcanvas11.0.0`/newcanvas11.0.0.tar.gz . && $(DEL_FILE) -r .tmp/newcanvas11.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) -r newcanvas1.app
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_myview.cpp moc_myscene.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_myview.cpp moc_myscene.cpp
moc_myview.cpp: myview.h
	/Users/john/QtSDK/Desktop/Qt/4.8.1/gcc/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ myview.h -o moc_myview.cpp

moc_myscene.cpp: myscene.h
	/Users/john/QtSDK/Desktop/Qt/4.8.1/gcc/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ myscene.h -o moc_myscene.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
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

main.o: main.cpp myview.h \
		myscene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

myview.o: myview.cpp myview.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o myview.o myview.cpp

myscene.o: myscene.cpp myscene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o myscene.o myscene.cpp

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

moc_myview.o: moc_myview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_myview.o moc_myview.cpp

moc_myscene.o: moc_myscene.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_myscene.o moc_myscene.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

