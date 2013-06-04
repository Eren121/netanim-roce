QT += gui widgets
SOURCES += \
    main.cpp \
    myview.cpp \
    myscene.cpp \
    log.cpp \
    fatal-error.cpp \
    fatal-impl.cpp \
    logqt.cpp \
    resizeablepixmap.cpp \
    resizeableitem.cpp

HEADERS += \
    myview.h \
    myscene.h \
    log.h \
    fatal-error.h \
    fatal-impl.h \
    abort.h \
    assert.h \
    logqt.h \
    animatorconstants.h \
    resizeablepixmap.h \
    resizeableitem.h

DEFINES += NS3_LOG_ENABLE

RESOURCES += \
    testrc.qrc
