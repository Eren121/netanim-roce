QT += gui widgets
SOURCES += \
    main.cpp \
    myview.cpp \
    myscene.cpp \
    log.cpp \
    fatal-error.cpp \
    fatal-impl.cpp \
    logqt.cpp

HEADERS += \
    myview.h \
    myscene.h \
    log.h \
    fatal-error.h \
    fatal-impl.h \
    abort.h \
    assert.h \
    logqt.h

DEFINES += NS3_LOG_ENABLE
