CONFIG -= qt

TEMPLATE = lib
CONFIG += staticlib

include(../common.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/board.cpp \
        src/game.cpp \
        src/piece.cpp

HEADERS += \
    src/board.h \
    src/game.h \
    src/observer.h \
    src/piece.h \
    src/pieces.h \
    src/position.h \
    src/state.h \
    src/subject.h \
    src/utils.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
