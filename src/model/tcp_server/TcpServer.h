/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QObject>
#include <QHostAddress>


/*
 * TcpServer class
 *
 * Interface for the TCP server.
 */
class TcpServer : public QObject
{
    Q_OBJECT

public:
    TcpServer(QObject *parent = 0) : QObject(parent) { /* Do nothing */ }

    virtual void startServer(const QHostAddress &address, quint16 port) = 0;
    virtual void stopServer() = 0;

signals:
    serverStarted();
    serverStopped();
};
