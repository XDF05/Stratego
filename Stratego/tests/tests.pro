TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

include(../common.pri)

HEADERS += \
    catch.h

SOURCES += \
    test_gamemodel.cpp \
    main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Gamemodel/release/ -lGamemodel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Gamemodel/debug/ -lGamemodel
else:unix: LIBS += -L$$OUT_PWD/../Gamemodel/ -lGamemodel

INCLUDEPATH += $$PWD/../Gamemodel/src
DEPENDPATH += $$PWD/../Gamemodel/src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Gamemodel/release/libGamemodel.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Gamemodel/debug/libGamemodel.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Gamemodel/release/Gamemodel.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Gamemodel/debug/Gamemodel.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Gamemodel/libGamemodel.a
