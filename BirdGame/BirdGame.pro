#-------------------------------------------------
#
# Project created by QtCreator 2014-01-01T15:44:02
#
#-------------------------------------------------

QT       += core gui
lessThan(QT_MAJOR_VERSION, 5): QT   += phonon #QT4中的音乐模块
greaterThan(QT_MAJOR_VERSION, 4):QT +=multimedia #QT5中的音乐模块
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = BirdGame
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    dlg_hitgame.cpp \
    cballhit.cpp \
    dlg_recognums.cpp \
    crecognums.cpp \
    Sound.cpp

HEADERS  += widget.h \
    dlg_hitgame.h \
    cballhit.h \
    dlg_recognums.h \
    crecognums.h \
    global.h \
    Sound.h \
    CGridNums.h \
    CTarget.h

FORMS    += widget.ui \
    dlg_hitgame.ui \
    dlg_recognums.ui

OTHER_FILES += \
    readme.txt

RESOURCES += \
    resource.qrc
