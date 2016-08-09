#pragma once

#include <QWidget>
#include <QTextEdit>
#include "../model/Model.h"

class LogWidget : public QWidget
{
    Q_OBJECT

private:
    Model       *m_pModel;

    QTextEdit   *m_pLogEdit;

public:
    LogWidget(Model *pModel, QWidget *parent = 0);

private slots:
    void onLogEntryAdded(const QString& msg);
};
