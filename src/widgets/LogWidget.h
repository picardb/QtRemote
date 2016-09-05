/* This source file is distributed under the MIT license
 * (see attached LICENSE.txt file for details)
 */

#pragma once

#include <QWidget>
#include <QTextEdit>


/*
 * LogWidget class
 *
 * Prints the application log.
 */
class LogWidget : public QWidget
{
    Q_OBJECT

private:
    static const QString FONT;
    static const int FONT_SIZE;

    QTextEdit   *m_pLogEdit;

public:
    LogWidget(QWidget *parent = 0);

private slots:
    void onLogEntryAdded(const QString& msg);
};
