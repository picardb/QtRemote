/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QHostInfo>
#include <QTimer>

/*
 * Client class
 *
 * Manages a TCP client.
 */
class Client : public QObject
{
    Q_OBJECT

private:
    /* Constants */
    static const int    REQUEST_TIMEOUT_MSEC = 500;

    /* Members */
    QTcpSocket  *m_pSocket;
    QByteArray  m_requestBuffer;
    QTimer      m_timeoutTimer;

    /* Methods */
    bool isRequestComplete();
    void processRequest();

public:
    Client(QTcpSocket *pSocket);
    ~Client();

    QString ipAddress() { return m_pSocket->peerAddress().toString(); }

private slots:
    void onTcpReadyRead();
    void onRequestTimeout();

signals:
    disconnected();
};
