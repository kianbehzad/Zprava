#-------------------------------------------------
#
# Project created by QtCreator 2018-05-20T14:25:59
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Zprava
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        zprava.cpp \
    zpform.cpp \
    zpcontact.cpp \
    zpexperimental.cpp \
    zpuser.cpp \
    zpcontactlist.cpp \
    zpthread.cpp \
    zpmessage.cpp \
    zptextmessage.cpp \
    zpchatview.cpp \
    zpchattype.cpp \
    zpchatwindow.cpp \
    zpnavigationbar.cpp \
    zpuserinfo.cpp \
    zpsettings.cpp

HEADERS  += zprava.h \
    zpform.h \
    zpcontact.h \
    zpexperimental.h \
    zpuser.h \
    zpcontactlist.h \
    zpthread.h \
    zpmessage.h \
    zptextmessage.h \
    zpchatview.h \
    zpchattype.h \
    zpchatwindow.h \
    zpnavigationbar.h \
    zpuserinfo.h \
    zpglobals.h \
    zpsettings.h

RESOURCES += \
    Resources/resources.qrc
