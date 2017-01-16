#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T19:49:50
#
#-------------------------------------------------

QT += core
QT += widgets multimedia winextras
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MazeV1
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    room.cpp \
    agent.cpp \
    player.cpp \
    monster.cpp \
    object.cpp \
    treasure.cpp \
    prop.cpp \
    fixedprop.cpp \
    myclickableqlabel.cpp \
    winningdialog.cpp \
    entringdialog.cpp \
    smartmonster.cpp \
    gameover.cpp

HEADERS  += mainwindow.h \
    room.h \
    agent.h \
    player.h \
    monster.h \
    object.h \
    treasure.h \
    prop.h \
    fixedprop.h \
    myclickableqlabel.h \
    winningdialog.h \
    entringdialog.h \
    smartmonster.h \
    gameover.h

FORMS    += mainwindow.ui \
    winningdialog.ui \
    entringdialog.ui \
    gameover.ui

RESOURCES += \
    pics.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/winextras/musicplayer
INSTALLS += target

DISTFILES += \
    D:/new comers/Taylor Davis/01 - Dr. Wily's Castle (From Mega Man 2).mp3 \
    D:/new comers/Taylor Davis/David Garrett - He's A Pirate By Hans Zimmer Feat Klaus Badelt.mp3 \
    D:/new comers/Taylor Davis/sonng.mp3
