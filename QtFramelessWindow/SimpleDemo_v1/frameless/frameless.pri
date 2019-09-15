SOURCES += $$PWD/framelesswidget.cpp \  
    $$PWD/framelessdialog.cpp \
    $$PWD/windowsizer.cpp

HEADERS += $$PWD/framelesswidget.h \ 
    $$PWD/framelessdialog.h \
    $$PWD/windowsizer.h

win32 {
QT += winextras
LIBS += -luser32 -ldwmapi
}

INCLUDEPATH += $$PWD

