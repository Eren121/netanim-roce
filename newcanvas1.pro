SOURCES += \
    main.cpp \
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
    animatorview.cpp \
    animlink.cpp

HEADERS += \
    myview.h \
    log.h \
    fatal-error.h \
    fatal-impl.h \
    abort.h \
    assert.h \
    logqt.h \
    animatorconstants.h \
    resizeablepixmap.h \
    resizeableitem.h \
    animnode.h \
    common.h \
    animatorscene.h \
    timevalue.h \
    animpacket.h \
    netanim.h \
    animatormode.h \
    animatorview.h \
    mode.h \
    animxmlparser.h \
    animevent.h \
    animlink.h

DEFINES += NS3_LOG_ENABLE

RESOURCES += \
    testrc.qrc
