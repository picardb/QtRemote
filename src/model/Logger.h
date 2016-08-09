#pragma once

#include <QObject>
#include <QString>

class Logger : public QObject
{
    Q_OBJECT

public:
    Logger(QObject *parent = 0);

    void addEntry(const QString& str);

signals:
    entryAdded(const QString& );
};