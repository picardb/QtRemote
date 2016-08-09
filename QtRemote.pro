#-------------------------------------------------
#
# Project created by QtCreator 2016-08-03T16:52:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtRemote
TEMPLATE = app

LIBS += -L$$PWD/lib -ldnssd


SOURCES += \
    src/main.cpp \
    src/widgets/MainWindow.cpp \
    src/model/Model.cpp \
    src/model/DnsServiceRegistrar.cpp \
    src/model/Logger.cpp \
    src/widgets/LogWidget.cpp \
    src/widgets/MainWidget.cpp

HEADERS  += \
    src/widgets/MainWindow.h \
    src/model/Model.h \
    src/model/DnsServiceRegistrar.h \
    src/model/Logger.h \
    src/widgets/LogWidget.h \
    src/widgets/MainWidget.h
