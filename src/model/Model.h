/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include "tcp_server/TcpServer.h"
#include "log/Logger.h"
#include "control/Control.h"

/*
 * Model class
 *
 * Provides access to all model components.
 */
class Model
{
private:
    static TcpServer    m_tcpServer;
    static Logger       m_logger;
    static Control      m_control;

public:
    static TcpServer& tcpServer() { return m_tcpServer; }
    static Logger& logger() { return m_logger; }
    static Control& control() { return m_control; }
};
