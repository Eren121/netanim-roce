SOURCES += \
    main.cpp \
    log.cpp \
    fatal-error.cpp \
    fatal-impl.cpp \
    logqt.cpp \
    resizeableitem.cpp \
    animnode.cpp \
    animatorscene.cpp \
    animpacket.cpp \
    netanim.cpp \
    animatormode.cpp \
    mode.cpp \
    animxmlparser.cpp \
    animatorview.cpp \
    animlink.cpp \
    animresource.cpp \
    statsview.cpp \
    statsmode.cpp \
    routingxmlparser.cpp \
    routingstatsscene.cpp \
    interfacestatsscene.cpp \
    flowmonxmlparser.cpp \
    flowmonstatsscene.cpp \
    textbubble.cpp
HEADERS += \
    log.h \
    fatal-error.h \
    fatal-impl.h \
    abort.h \
    assert.h \
    logqt.h \
    animatorconstants.h \
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
    animlink.h \
    animresource.h \
    statsview.h \
    statsmode.h \
    statisticsconstants.h \
    routingxmlparser.h \
    routingstatsscene.h \
    interfacestatsscene.h \
    flowmonxmlparser.h \
    flowmonstatsscene.h \
    textbubble.h

DEFINES += NS3_LOG_ENABLE

RESOURCES += \
    testrc.qrc
