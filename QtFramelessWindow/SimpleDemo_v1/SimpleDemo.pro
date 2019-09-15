#-------------------------------------------------
#
# Project created by QtCreator 2016-08-22T10:57:17
#
#-------------------------------------------------

QT       += widgets network

TARGET = SimpleDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    settinglistwidget.cpp \
    bannerwidget.cpp \
    mainapplication.cpp

HEADERS  += mainwidget.h \
    settinglistwidget.h \
    bannerwidget.h \
    mainapplication.h

include(frameless/frameless.pri)

FORMS    +=

RESOURCES += \
    resources.qrc

TRANSLATIONS += zh_CN.ts

RC_ICONS = icon.ico

LIBS += -luser32
