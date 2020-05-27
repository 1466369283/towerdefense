#-------------------------------------------------
#
# Project created by QtCreator 2020-05-23T20:44:04
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LiuXi_gogogo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    chooselevelscene.cpp \
    easymode.cpp \
    hardmode.cpp \
    enemy.cpp \
    towerposition.cpp \
    tower.cpp \
    waypoint.cpp \
    utility.cpp \
    bullet.cpp \
    audioplayer.cpp \
    plistreader.cpp

HEADERS += \
        mainwindow.h \
    chooselevelscene.h \
    easymode.h \
    hardmode.h \
    enemy.h \
    towerposition.h \
    tower.h \
    waypoint.h \
    utility.h \
    bullet.h \
    audioplayer.h \
    plistreader.h

FORMS += \
        mainwindow.ui \
    chooselevelscene.ui \
    easymode.ui \
    hardmode.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    images/normaltower.png \
    images/normaltower.png \
    images/enemy.png \
    images/enemy.png
