/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#include "Model.h"

/*
 * Static components definitions
 */
NullLogger      Model::m_nullLogger;
Logger*         Model::m_pLogger(&m_nullLogger);
NullTcpServer   Model::m_nullTcpServer;
TcpServer*      Model::m_pTcpServer(&m_nullTcpServer);
NullControl     Model::m_nullControl;
Control*        Model::m_pControl(&m_nullControl);


/*
 * Model::provideLogger
 *
 * Provides a logger service to the model.
 *
 * Parameters:
 *  - pLogger: pointer to the logger service instance
 *
 * Return value: none
 */
void Model::provideLogger(Logger *pLogger) {
    if (pLogger == NULL) {
        m_pLogger = &m_nullLogger;
    }
    else {
        m_pLogger = pLogger;
    }
}


/*
 * Model::provideTcpServer
 *
 * Provides a TCP server to the model.
 *
 * Parameters:
 *  - pTcpServer: pointer to the TCP server instance
 *
 * Return value: none
 */
void Model::provideTcpServer(TcpServer *pTcpServer) {
    if (pTcpServer == NULL) {
        m_pTcpServer = &m_nullTcpServer;
    }
    else {
        m_pTcpServer = pTcpServer;
    }
}


/*
 * Model::provideControl
 *
 * Provides a control service to the model.
 *
 * Parameters:
 *  - pControl: pointer to the control service instance
 *
 * Return value: none
 */
void Model::provideControl(Control *pControl) {
    if (pControl == NULL) {
        m_pControl = &m_nullControl;
    }
    else {
        m_pControl = pControl;
    }
}
