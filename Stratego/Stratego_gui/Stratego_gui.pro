QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../common.pri)

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gameView.cpp \
    guiPiece.cpp \
    guiUtils.cpp \
    guiboard.cpp \
    main.cpp \
    mainmenu.cpp \
    piecebox.cpp \
    widget.cpp

HEADERS += \
    gameView.h \
    guiPiece.h \
    guiUtils.h \
    guiboard.h \
    piecebox.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


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

RESOURCES += \
    res.qrc
