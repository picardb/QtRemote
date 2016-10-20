/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include "TcpServer.h"

class NullTcpServer : public TcpServer
{
public:
    NullTcpServer(QObject *parent = 0) : TcpServer(parent) { /* Do nothing */ }

    virtual void startServer(const QHostAddress &, quint16 ) { /* Do nothing */ }
    virtual void stopServer() { /* Do nothing */ }
};

