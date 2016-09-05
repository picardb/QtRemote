#-------------------------------------------------
#
# Project created by QtCreator 2016-08-03T16:52:38
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtRemote
TEMPLATE = app

LIBS += -L$$PWD/lib -ldnssd

INCLUDEPATH += src/

SOURCES += \
    src/main.cpp \
    src/widgets/MainWindow.cpp \
    src/model/log/Logger.cpp \
    src/model/network/DnsServiceRegistrar.cpp \
    src/model/network/Network.cpp \
    src/widgets/LogWidget.cpp \
    src/widgets/MainWidget.cpp \
    src/widgets/SetupWidget.cpp \
    src/model/Model.cpp

HEADERS  += \
    src/widgets/MainWindow.h \
    src/model/Model.h \
    src/model/log/Logger.h \
    src/model/network/DnsServiceRegistrar.h \
    src/model/network/Network.h \
    src/widgets/LogWidget.h \
    src/widgets/MainWidget.h \
    src/widgets/SetupWidget.h
