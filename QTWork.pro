QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    asrthread.cpp \
    calculator.cpp \
    clockwindow.cpp \
    dayweather.cpp \
    dialogwindow.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    playvideowindow.cpp \
    ttsthread.cpp \
    weatherwindow.cpp

HEADERS += \
    asrthread.h \
    calculator.h \
    clockwindow.h \
    dayweather.h \
    dialogwindow.h \
    loginwindow.h \
    mainwindow.h \
    playvideowindow.h \
    ttsthread.h \
    weatherwindow.h

FORMS += \
    calculator.ui \
    clockwindow.ui \
    dialogwindow.ui \
    loginwindow.ui \
    mainwindow.ui \
    playvideowindow.ui \
    weatherwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
