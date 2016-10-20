#-------------------------------------------------
#
# Project created by QtCreator 2016-08-03T16:52:38
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtRemote
TEMPLATE = app

LIBS += -L$$PWD/lib -ldnssd -lole32

INCLUDEPATH += src/

SOURCES += \
    src/main.cpp \
    src/widgets/MainWindow.cpp \
    src/widgets/LogWidget.cpp \
    src/widgets/MainWidget.cpp \
    src/widgets/SetupWidget.cpp \
    src/model/Model.cpp \
    src/model/tcp_server/DnsServiceRegistrar.cpp \
    src/model/tcp_server/Client.cpp \
    src/widgets/SettingsDialog.cpp \
    src/model/log/FileLogger.cpp \
    src/model/tcp_server/DnsSdTcpServer.cpp \
    src/model/control/WinVistaControl.cpp \
    src/model/control/WinVistaAudioControls.cpp

HEADERS  += \
    src/widgets/MainWindow.h \
    src/widgets/LogWidget.h \
    src/widgets/MainWidget.h \
    src/widgets/SetupWidget.h \
    src/model/Model.h \
    src/model/log/Logger.h \
    src/model/control/Control.h \
    src/model/tcp_server/DnsServiceRegistrar.h \
    src/model/tcp_server/TcpServer.h \
    src/model/tcp_server/Request.h \
    src/model/tcp_server/Client.h \
    src/widgets/SettingsDialog.h \
    src/globals.h \
    src/constants.h \
    src/model/log/NullLogger.h \
    src/model/log/FileLogger.h \
    src/model/tcp_server/NullTcpServer.h \
    src/model/tcp_server/DnsSdTcpServer.h \
    src/model/control/WinVistaControl.h \
    src/model/control/WinVistaAudioControls.h \
    src/model/control/NullControl.h
