/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include "log/NullLogger.h"
#include "log/Logger.h"
#include "tcp_server/NullTcpServer.h"
#include "tcp_server/TcpServer.h"
#include "control/NullControl.h"
#include "control/Control.h"

/*
 * Model class
 *
 * Provides access to all model services.
 */
class Model
{
private:
    /* Loggers */
    static NullLogger       m_nullLogger;
    static Logger*          m_pLogger;

    /* TCP servers */
    static NullTcpServer    m_nullTcpServer;
    static TcpServer*       m_pTcpServer;

    /* Controls */
    static NullControl      m_nullControl;
    static Control*         m_pControl;

public:
    static void provideLogger(Logger* pLogger);
    static void provideTcpServer(TcpServer* pServer);
    static void provideControl(Control *pControl);
    static Logger& logger() { return *m_pLogger; }
    static TcpServer& tcpServer() { return *m_pTcpServer; }
    static Control& control() { return *m_pControl; }
};
